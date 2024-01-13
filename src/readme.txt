# 驱动的使用方法

1. 选择一个相应驱动(ST7735,GC9A01等)添加到项目

2. 按实际修改config/gpio_config.h中gpio的配置

3. 初始化时钟,GPIO,SPI等

4. 在应用层(main.c)调用display