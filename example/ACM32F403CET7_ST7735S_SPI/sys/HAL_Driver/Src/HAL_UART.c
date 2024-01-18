/*
  ******************************************************************************
  * @file    HAL_Uart.c
  * @version V1.0.0
  * @date    2020
  * @brief   UART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"


/* If Use 'UART_MODE_TX_RX_DEBUG', Point to Debug Uart */
UART_TypeDef    *Uart_Debug = NULL;

/* Private function prototypes -----------------------------------------------*/
static void UART_Config_BaudRate(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef HAL_UART_Wait_Tx_Done(UART_HandleTypeDef *huart);
__weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
__weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

/*********************************************************************************
* Function    : HAL_UART_IRQHandler
* Description : Handle UART interrupt request.
* Input       : huart: UART handle.
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/ 
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    uint32_t read_bytes_number;
    uint32_t isrflags;
    uint32_t errorflags;
    
    
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return;
#endif

    isrflags = READ_REG(huart->Instance->MIS);

    errorflags = (READ_REG(huart->Instance->RIS) & (UART_RIS_ERROR_BITS));  

    if (isrflags & UART_MIS_TXI) 
    {
        /* Clear TXI Status */
        WRITE_REG(huart->Instance->ICR , UART_ICR_TXI);

        for(;;)
        {
            if(huart->lu32_TxCount == huart->lu32_TxSize) 
            {                             
                huart->lu8_TxBusy = false;
         
                /* Disable TX interrupt & clear error interrupt*/
                CLEAR_BIT(huart->Instance->IE, UART_IE_TXI |
                                               UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI); 
         
                HAL_UART_TxCpltCallback(huart);
                return;
            }

            if (READ_BIT(huart->Instance->FR, UART_FR_TXFF))
            {
                break;
            }
            
            huart->Instance->DR = huart->lu8_TxData[huart->lu32_TxCount++];
        }
    }


    /* RXI */ 
    if (isrflags & UART_MIS_RXI) 
    {
        read_bytes_number = 0;   
        /* Clear RXI Status */
        WRITE_REG(huart->Instance->ICR, UART_ICR_RXI);
                                
        /* Receive end */
        while(huart->lu32_RxCount < huart->lu32_RxSize )  
        {
            if(!READ_BIT(huart->Instance->FR, UART_FR_RXFE))// fifo not empty 
            {
                 /* Store Data in buffer */
                 huart->lu8_RxData[huart->lu32_RxCount++] = huart->Instance->DR;		
                 read_bytes_number++;  
            }  
            else
            {
                break; 
            }  
            
            if (read_bytes_number == huart->lu32_fifo_level_minus1)   
            {
                break;   
            }
        }
        if(huart->lu32_RxCount == huart->lu32_RxSize )
        {
            huart->lu8_RxBusy = false;
        
            /* Disable RX and RTI interrupt & clear error interrupt*/
            CLEAR_BIT(huart->Instance->IE, (UART_IE_RXI | UART_IE_RTI |
                                            UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI));
            
            HAL_UART_RxCpltCallback(huart);
       }
    }
    else if(isrflags & UART_MIS_RTI)
    {
        /*clear RTI Status */
        WRITE_REG(huart->Instance->ICR ,UART_ICR_RTI);

        while(!READ_BIT(huart->Instance->FR, UART_FR_RXFE))
        {
            huart->lu8_RxData[huart->lu32_RxCount++] = huart->Instance->DR; 
            
            if(READ_BIT(huart->Instance->RSR, UART_RSR_FRAME_ERR | UART_RSR_PARITY_ERR | UART_RSR_OVERRUN_ERR)) 
            {
                huart->lu32_RxCount--; 
            }     
        }

        huart->lu8_RxBusy = false;

        /* Disable RX and RTI interrupt &  clear error interrupt*/
        CLEAR_BIT(huart->Instance->IE, (UART_IE_RXI | UART_IE_RTI | 
                                        UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI ));
        
        HAL_UART_RxCpltCallback(huart);
    }	
	
	/* if some errors occurred */
    if(errorflags != 0)
    {
		/* UART parity error interrupt occurred */
        if ( (errorflags & UART_RIS_PEI) != 0)
        {
	    	/* Clear parity error status */
            WRITE_REG(huart->Instance->ICR, UART_ICR_PEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_PE; 
	    }

	    /* UART break error interrupt occurred */
        if ( (errorflags & UART_RIS_BEI) != 0) 
	    {
	    	WRITE_REG(huart->Instance->ICR, UART_ICR_BEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_NE;
	    }

	    /* UART frame error interrupt occurred */
	    if ( (errorflags & UART_RIS_FEI) != 0) 
	    {
	    	WRITE_REG(huart->Instance->ICR, UART_ICR_FEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_FE;
	    }

	    /* UART Over-Run interrupt occurred */
	    if ( (errorflags & UART_RIS_OEI) != 0) 
	    {
	    	WRITE_REG(huart->Instance->ICR, UART_ICR_OEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_ORE;
	    }

		HAL_UART_ErrorCallback(huart); 
	}
}

/*********************************************************************************
* Function    : HAL_UART_Wait_Tx_Done
* Description : wait Tx FIFO empty
* Input       : huart: UART handle.
* Output      : 
**********************************************************************************/
static HAL_StatusTypeDef HAL_UART_Wait_Tx_Done(UART_HandleTypeDef *huart)
{	
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))         return HAL_ERROR;
#endif
	/* wait FIFO empty */
	while(READ_BIT(huart->Instance->FR, UART_FR_BUSY)); 

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_MspInit
* Description : Initialize the UART MSP.
* Input       : huart: UART handle.
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
__weak void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function should be modified, when the callback is needed,
      the HAL_UART_MspInit can be implemented in the user file.
    */

    /* For Example */
    GPIO_InitTypeDef    GPIO_Uart1; 
    GPIO_InitTypeDef    GPIO_Uart2;
    
    if (huart->Instance == UART1) 
    {
        /* Enable Clock */
        System_Module_Enable(EN_UART1);
        System_Module_Enable(EN_GPIOAB);   
        
        /* Initialization GPIO */
        /* A9:Tx  A10:Rx */
        GPIO_Uart1.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_Uart1.Mode      = GPIO_MODE_AF_PP;
        GPIO_Uart1.Pull      = GPIO_PULLUP;
        GPIO_Uart1.Alternate = GPIO_FUNCTION_2;
        
        HAL_GPIO_Init(GPIOA, &GPIO_Uart1);
        
        if (huart->Init.HwFlowCtl & UART_HWCONTROL_CTS) 
        {
            /* A11:CTS */
            GPIO_Uart1.Pin = GPIO_PIN_11;
            
            HAL_GPIO_Init(GPIOA, &GPIO_Uart1);
        }

        if (huart->Init.HwFlowCtl & UART_HWCONTROL_RTS) 
        {
            /* A12:RTS */
            GPIO_Uart1.Pin = GPIO_PIN_12;
            
            HAL_GPIO_Init(GPIOA, &GPIO_Uart1);
        }

        /* NVIC Config */
        NVIC_ClearPendingIRQ(UART1_IRQn);
        NVIC_SetPriority(UART1_IRQn, (1U << __NVIC_PRIO_BITS) - 2);  
        NVIC_EnableIRQ(UART1_IRQn);
    }
    else if (huart->Instance == UART2) 
    {
        /* Enable Clock */
        System_Module_Enable(EN_UART2);  
        System_Module_Enable(EN_GPIOAB);      
        /* Initialization GPIO */
        GPIO_Uart2.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_Uart2.Mode      = GPIO_MODE_AF_PP;
        GPIO_Uart2.Pull      = GPIO_PULLUP;
        GPIO_Uart2.Alternate = GPIO_FUNCTION_2;
        
        HAL_GPIO_Init(GPIOA, &GPIO_Uart2);   
        
        NVIC_ClearPendingIRQ(UART2_IRQn);
        NVIC_SetPriority(UART2_IRQn, (1U << __NVIC_PRIO_BITS) - 2);  
        NVIC_EnableIRQ(UART2_IRQn);  
    }
}

/*********************************************************************************
* Function    : HAL_UART_Init
* Description : Initialize the UART mode according to the specified parameters 
*               in the UART_InitTypeDef
* Input       : huart: UART handle.
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{

#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))                   return HAL_ERROR;
    if (!IS_UART_WORDLENGTH(huart->Init.WordLength))              return HAL_ERROR;
    if (!IS_UART_STOPBITS(huart->Init.StopBits))                  return HAL_ERROR;
    if (!IS_UART_PARITY(huart->Init.Parity))                      return HAL_ERROR;
    if (!IS_UART_MODE(huart->Init.Mode))                          return HAL_ERROR;
    if (!IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl))    return HAL_ERROR;
#endif

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_UART_MspInit(huart);
    
    /* Config BaudRate */
    UART_Config_BaudRate(huart);
    
    /* Set the UART Communication parameters */
    huart->Instance->LCRH = huart->Init.WordLength | huart->Init.StopBits | huart->Init.Parity;
    huart->Instance->CR = huart->Init.HwFlowCtl | huart->Init.Mode | UART_CR_UARTEN;
    
    if (huart->Init.Mode == UART_MODE_TX_RX_DEBUG) 
    {
        Uart_Debug = huart->Instance;
    }
    else if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        huart->Instance->CR2 = UART_CR2_TXOE_SEL;
    }
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_MspDeInit
* Description : DeInitialize the UART MSP.
* Input       : huart: UART handle.
* Output      : 
**********************************************************************************/
__weak void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function should be modified, when the callback is needed,
      the HAL_UART_MspDeInit can be implemented in the user file.
    */    
    if (huart->Instance == UART1) 
    {
        /* Disable Clock */
        System_Module_Disable(EN_UART1); 
        System_Module_Reset(RST_UART1);       

        /* DeInitialization GPIO */
        /* A9:Tx  A10:Rx */
        HAL_GPIO_DeInit(GPIOA,GPIO_PIN_9 | GPIO_PIN_10);
		
		if (huart->Init.HwFlowCtl & UART_HWCONTROL_CTS) 
        {
            /* A11:CTS */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11);
        }

        if (huart->Init.HwFlowCtl & UART_HWCONTROL_RTS) 
        {
            /* A12:RTS */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
        }
		
        /* NVIC DeInit */
        NVIC_DisableIRQ(UART1_IRQn);  
        NVIC_ClearPendingIRQ(UART1_IRQn);            
		
    }
	else if(huart->Instance == UART2)
	{
        System_Module_Disable(EN_UART2);  
        System_Module_Reset(RST_UART2);  
        NVIC_DisableIRQ(UART2_IRQn); 
        NVIC_ClearPendingIRQ(UART2_IRQn);   
	}
}

/*********************************************************************************
* Function    : HAL_UART_Init
* Description : Initialize the UART mode according to the specified parameters 
*               in the UART_InitTypeDef
* Input       : huart: UART handle.
* Output      : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)
{

#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))         return HAL_ERROR;
#endif

    /* DeInit the low level hardware : GPIO, CLOCK, NVIC */
    HAL_UART_MspDeInit(huart);  
    
    huart->lu32_RxCount = 0;
    huart->lu32_RxSize = 0; 
    huart->lu8_RxBusy = false;  
    huart->lu8_TxBusy = false;     
    huart->lu32_TxCount = 0;
    huart->lu32_TxSize = 0;  
    huart->ErrorCode = HAL_UART_ERROR_NONE;    

	return HAL_OK;
    
}


/*********************************************************************************
* Function    : HAL_UART_Transmit
* Description : Send an amount of data in blocking mode.
* Input       : huart:        UART handle.
* Input       : fu8_Data:     Pointer to data buffer.
* Input       : fu32_Size:    Amount of data elements to be sent.
* Input       : fu32_Timeout: Timeout duration.
* Output      : HAL status
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size, uint32_t fu32_Timeout)
{
    uint32_t lu32_Timeout;
    
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

    huart->lu32_TxCount = 0;
    
    while (fu32_Size--) 
    {
        huart->Instance->DR = *fu8_Data++;

        huart->lu32_TxCount++;
        
        /* have no timeout */
        if (fu32_Timeout == 0) 
        {
            while (huart->Instance->FR & UART_FR_TXFF);
        }
        else 
        {
            lu32_Timeout = fu32_Timeout *256;
            
            while (huart->Instance->FR & UART_FR_TXFF)
            {
                if (lu32_Timeout-- == 0) 
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    }
    
    while ((huart->Instance->FR & UART_FR_BUSY));      
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_Receive
* Description : Receive an amount of data in blocking mode.
* Input       : huart:        UART handle.
* Input       : fu8_Data:     Pointer to data buffer.
* Input       : fu32_Size:    Amount of data elements to be receive.
* Input       : fu32_Timeout: Timeout duration.
* Output      : HAL status
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size, uint32_t fu32_Timeout)
{
    uint32_t lu32_Timeout;
    
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

    huart->lu32_RxCount = 0;
    
    /* Half duplex Use Tx GPIO Receive Data */
    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        huart->Instance->CR2 |= UART_CR2_RX_SEL;
    }

    while (fu32_Size--) 
    {
        if (fu32_Timeout == 0) 
        {
            while(huart->Instance->FR & UART_FR_RXFE);
            
            *fu8_Data++ = huart->Instance->DR;
            
            huart->lu32_RxCount++;
        }
        else 
        {
            lu32_Timeout = fu32_Timeout * 256;
            
            while(huart->Instance->FR & UART_FR_RXFE)
            {
                if (lu32_Timeout-- == 0) 
                {
                    /* Clear Half duplex */
                    huart->Instance->CR2 &= ~UART_CR2_RX_SEL;
                    
                    return HAL_TIMEOUT;
                }
            }

            *fu8_Data++ = huart->Instance->DR;

            huart->lu32_RxCount++;
        }
    }
    
    /* Clear Half duplex */
    huart->Instance->CR2 &= ~UART_CR2_RX_SEL;
    
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_Transmit_IT
* Description : Send an amount of data in interrupt mode.
* Input       : huart:        UART handle.
* Input       : fu8_Data:     Pointer to data buffer.
* Input       : fu32_Size:    Amount of data elements to be receive.
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size, uint32_t fifo_level)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif
    
    if (huart->lu8_TxBusy == true) 
    {
        return HAL_BUSY;
    }
    
    if (fu32_Size == 0 || fu8_Data == NULL) 
    {
        return HAL_ERROR;
    }
    
    if ( (fifo_level >> UART_TX_FIFO_LEVEL_INDEX) > UART_FIFO_LEVEL_NUM)   
    {
        return HAL_ERROR;  
    } 
    
    huart->lu32_TxSize  = fu32_Size;
    huart->lu32_TxCount = 0;
    huart->lu8_TxData   = fu8_Data;
    huart->lu8_TxBusy   = true;
    
    /* Clear TXI Status */
    huart->Instance->ICR = UART_ICR_TXI;
    /* FIFO Enable */
    SET_BIT(huart->Instance->LCRH, UART_LCRH_FEN);
	/*FIFO Select*/
    MODIFY_REG(huart->Instance->IFLS, UART_IFLS_TXIFLSEL, fifo_level); 
	
    for(;;) 
    {	
        /*Data Size less than 16Byte */
	    if(fu32_Size == huart->lu32_TxCount) 
	    {
	        huart->lu8_TxBusy = false;
			
			while ((huart->Instance->FR & UART_FR_BUSY)){}
			
	        HAL_UART_TxCpltCallback(huart);
			
	        return HAL_OK;  
	    }
	    if(READ_BIT(huart->Instance->FR, UART_FR_TXFF)) 
	    {				
	         break;
	    }
	    huart->Instance->DR = huart->lu8_TxData[huart->lu32_TxCount++];
    }
	
    /* Enable TX interrupt */
    huart->Instance->IE |= UART_IE_TXI;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_Receive_IT
* Description : Receive an amount of data in interrupt mode.
* Input       : 
* Output      : 
* Author      : Chris_Kyle                         Date : 2021   
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size, uint32_t fifo_level)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif
    
    if (huart->lu8_RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (fu32_Size == 0 || fu8_Data == NULL) 
    {
        return HAL_ERROR;
    }
    
    if ( (fifo_level >> UART_RX_FIFO_LEVEL_INDEX) > UART_FIFO_LEVEL_NUM)
    {
        return HAL_ERROR;  
    } 
      
    huart->lu32_RxSize  = fu32_Size;
    huart->lu32_RxCount = 0;
    huart->lu8_RxData   = fu8_Data;
    huart->lu8_RxBusy   = true; 
    huart->ErrorCode = HAL_UART_ERROR_NONE;  

    /* Clear RXI Status */
    huart->Instance->ICR = UART_ICR_RXI | UART_ICR_ERROR_BITS;
    /* FIFO Enable */
    SET_BIT(huart->Instance->LCRH, UART_LCRH_FEN);
	/*FIFO Select*/
	MODIFY_REG(huart->Instance->IFLS, UART_IFLS_RXIFLSEL, fifo_level);   
    
    switch(fifo_level)
    {
        case UART_RX_FIFO_1_8: 
        huart->lu32_fifo_level_minus1  = 1; 
        break;
        
        case UART_RX_FIFO_1_4:
        huart->lu32_fifo_level_minus1  = 3; 
        break;  
        
        case UART_RX_FIFO_1_2: 
        huart->lu32_fifo_level_minus1  = 7;  
        break; 
        
        case UART_RX_FIFO_3_4: 
        huart->lu32_fifo_level_minus1  = 11;  
        break;  
        
        case UART_RX_FIFO_7_8: 
        huart->lu32_fifo_level_minus1  = 13;    
        break; 

        default: 
        huart->lu32_fifo_level_minus1 = 0;       
        break;  
    }   
	/* Enable the UART Errors interrupt */
	SET_BIT(huart->Instance->IE,UART_IE_OEI|UART_IE_BEI|UART_IE_PEI|UART_IE_FEI);
    /* Enable RX and RTI interrupt */
    SET_BIT(huart->Instance->IE,UART_IE_RXI|UART_IE_RTI); 

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_Transmit_DMA
* Description : Send an amount of data in DMA mode.
* Input       : huart:        UART handle.
* Input       : fu8_Data:     Pointer to data buffer.
* Input       : fu32_Size:    Amount of data elements to be Send.
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

    if (huart->lu8_TxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (fu32_Size == 0 || fu8_Data == NULL) 
    {
        return HAL_ERROR;
    }

    huart->Instance->DMACR |= UART_DMACR_TXDMAE;

    if (HAL_DMA_Start_IT(huart->HDMA_Tx, (uint32_t)fu8_Data, (uint32_t)(&huart->Instance->DR), fu32_Size))
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/*********************************************************************************
<<<<<<< .mine
* Function    : HAL_UART_Receive_DMA
* Description : Receive an amount of data in DMA mode.
* Input       : huart:        UART handle.
* Input       : fu8_Data:     Pointer to data buffer.
* Input       : fu32_Size:    Amount of data elements to be receive.
* Output      : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *fu8_Data, uint32_t fu32_Size)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

    if (huart->lu8_RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (fu32_Size == 0 || fu8_Data == NULL) 
    {
        return HAL_ERROR;
    }

    huart->Instance->DMACR |= UART_DMACR_RXDMAE;

    if (HAL_DMA_Start_IT(huart->HDMA_Rx, (uint32_t)(&huart->Instance->DR), (uint32_t)fu8_Data, fu32_Size))
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}



/*********************************************************************************
* Function    : HAL_UART_TxCpltCallback
* Description : Tx Transfer completed callbacks.
* Input       : 
* Output       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
__weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_TxCpltCallback could be implemented in the user file.
    */
}

/*********************************************************************************
* Function    : HAL_UART_RxCpltCallback
* Description : Rx Transfer completed callbacks.
* Input       : 
* Output       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_RxCpltCallback could be implemented in the user file.
    */
}

/*********************************************************************************
* Function    : HAL_UART_ErrorCallback
* Description : Recv Error callbacks.
* Input       : 
* Output      : 
**********************************************************************************/
__weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)   
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_ErrorCallback could be implemented in the user file.
    */
}

/*********************************************************************************
* Function    : UART_Config_BaudRate
* Description : Config BaudRate
* Input       : 
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
static void UART_Config_BaudRate(UART_HandleTypeDef *huart)
{
    uint32_t lu32_PCLK;
    uint32_t lu32_IBAUD, lu32_FBAUD;
    uint64_t lu64_TempValue;

    if (CLK_SRC_RCH == System_Get_Clk_Source() )  
    {
        uint32_t  RCH_Real= *((uint32_t *)0x8022c);
        uint32_t  RCH_Ratio= (RCH_Real*16)/64;      // RCH_Ratio = RCH_Real/64   
        lu32_PCLK = (System_Get_APBClock()/1000)*RCH_Ratio;    
    }
    else
    {
        lu32_PCLK = System_Get_APBClock();    
    } 
    
    /* Integral part */
    lu32_IBAUD = lu32_PCLK / (huart->Init.BaudRate * 16);

    /* Fractional part */
    lu64_TempValue = lu32_PCLK % (huart->Init.BaudRate * 16);
    lu64_TempValue = (lu64_TempValue * 1000000) / (huart->Init.BaudRate * 16);
    lu32_FBAUD     = (lu64_TempValue * 64 + 500000) / 1000000;

    if (lu32_FBAUD >= 64) 
    {
        huart->Instance->IBRD = lu32_IBAUD + 1;
        huart->Instance->FBRD = 0;
    }
    else 
    {
        huart->Instance->IBRD = lu32_IBAUD;
        huart->Instance->FBRD = lu32_FBAUD;
    }
}

/*********************************************************************************
* Function    : HAL_UART_GetState
* Description : Return the uart State
* Input       : 
* Output      : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart)
{

#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

	if(huart->lu8_TxBusy || huart->lu8_RxBusy)
	{
		return HAL_BUSY;		
	}

	return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_UART_GetError
* Description : Return the uart Error 
* Input       : 
* Output      : 
**********************************************************************************/
uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart)
{
  	return huart->ErrorCode;
}

/*********************************************************************************
* Function    : HAL_UART_Abort
* Description : Abort ongoing transfers(blocking mode)
* Input       : UART handle
* Output      : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart)
{
#if (USE_FULL_ASSERT == 1)
	if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

	/*disble all interrupt*/
	huart->Instance->IE  =0x00;

	/* Disable the UART DMA Tx request if enable */
	if(READ_BIT(huart->Instance->DMACR, UART_DMACR_TXDMAE))
	{
		CLEAR_BIT(huart->Instance->DMACR, UART_DMACR_TXDMAE);

		/* Abort the UART Tx Channel   */
		if(huart->HDMA_Tx)
		{
			/*Set the UART DMA Abort callback to Null */
			huart->HDMA_Tx->DMA_ITC_Callback =NULL;

			if(HAL_DMA_Abort(huart->HDMA_Tx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/* Disable the UART DMA Rx request if enable */
	if(READ_BIT(huart->Instance->DMACR, UART_DMACR_RXDMAE))
	{
		CLEAR_BIT(huart->Instance->DMACR, UART_DMACR_RXDMAE);
		
		/* Abort the UART Rx Channel   */
		if(huart->HDMA_Rx)
		{
			/*Set the UART DMA Abort callback to Null */
			huart->HDMA_Rx->DMA_ITC_Callback =NULL;

			if(HAL_DMA_Abort(huart->HDMA_Rx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/*Reset Tx and Rx Transfer size*/
	huart->lu32_TxSize = 0;
	huart->lu32_RxSize = 0;

	/* Restore huart->lu8_TxBusy and huart->lu8_RxBusy to Ready */
	huart->lu8_TxBusy = false;
	huart->lu8_RxBusy = false;
		
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_DMAPause
* Description : Pause the DMA Transfer
* Input       : UART handle
* Output      : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart)
{
#if (USE_FULL_ASSERT == 1)
		if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

  if(READ_BIT(huart->Instance->DMACR, UART_DMACR_TXDMAE))
  {
    /* Disable the UART DMA Tx request */
    CLEAR_BIT(huart->Instance->DMACR, UART_DMACR_TXDMAE);
  }

  if (READ_BIT(huart->Instance->DMACR, UART_DMACR_RXDMAE))
  {
    /* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts */
    CLEAR_BIT(huart->Instance->IE, UART_IE_OEI|UART_IE_BEI|UART_IE_FEI);

    /* Disable the UART DMA Rx request */
    CLEAR_BIT(huart->Instance->DMACR, UART_DMACR_RXDMAE);
  }

  return HAL_OK;
}


/*********************************************************************************
* Function	  : HAL_UART_DMAResume
* Description : Resume the DMA Transfer
* Input 	  : UART handle
* Output	  : 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart)
{
#if (USE_FULL_ASSERT == 1)
		if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif

  if (huart->lu8_TxBusy == false)
  {
	/* Enable the UART DMA Tx request */
	SET_BIT(huart->Instance->DMACR, UART_DMACR_TXDMAE);
  }

  if (huart->lu8_RxBusy == false)
  {
	/* Reenable PE and ERR (Frame error, noise error, overrun error) interrupts */
	SET_BIT(huart->Instance->IE, UART_IE_OEI|UART_IE_BEI|UART_IE_FEI);

	/* Enable the UART DMA Rx request */
	SET_BIT(huart->Instance->DMACR, UART_DMACR_RXDMAE);
  }

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_UART_Enable_Disable_FIFO
* Description : Enable or Disable  FIFO.
* Input       : huart: UART handle.
* Input       : FUNC_ENABLE or  FUNC_DISABLE  
* Output      : HAL_OK or HAL_ERROR
* Author      : LWQ                         Data : 2022 
**********************************************************************************/
HAL_StatusTypeDef HAL_UART_Enable_Disable_FIFO(UART_HandleTypeDef *huart, FUNC_DISABLE_ENABLE enable_disable)  
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_UART_ALL_INSTANCE(huart->Instance))    return HAL_ERROR;
#endif
    if (FUNC_DISABLE == enable_disable)
    {
        huart->Instance->LCRH  &= (~UART_LCRH_FEN);
    }
    else
    {
        huart->Instance->LCRH  |= UART_LCRH_FEN;  
    }
    return HAL_OK;
}

/*********************************************************************************
* Function    : fputc
* Description : 
* Input       : 
* Output      : 
* Author      : Chris_Kyle                         Data : 2020 
**********************************************************************************/
int fputc(int ch, FILE *f)
{
    if (Uart_Debug == NULL) 
    {
        return 0;
    }

    Uart_Debug->DR = ch;
    
    while ((Uart_Debug->FR & UART_FR_BUSY));
    
    return ch;
}

