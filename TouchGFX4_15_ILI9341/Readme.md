# TouchGFX Test

Welcome to my github repository. This repository is designed to explore the capabilities of the TouchGFX framework
## Hardware 
 * A NUCLEO-F429ZI board with STM32F429ZI (180 MHz SYSCLK)
 * A TFT-LCD with ILI9341 driver and XPT2046 touchscreen controller from [AliExpress](https://www.aliexpress.com/item/32815224002.html?spm=a2g0s.9042311.0.0.6f9d4c4dv0T4OV), with SPI (90 MHz SCK)

### Wiring

|LCD Board|Nucleo   |STM32F411RE| Description       |
| ------- |:-----:  | ---------:|	--------------:	|
|VCC      |CN8-9    | -         | 5 V               |
|GND      |CN6-11   | -         | GND	            |
|CS       |CN10-13  | PB6       | D26, Chip Select  |
|RESET    |CN7-13   | PB5       | D22,  LCD Reset   |
|DC       |CN7-2    | PB8       | Data control      |
|MOSI     |CN7-14   | PA7       | D11, MOSI         |
|SCK      |CN7-10   | PA5       | D13, SCK          |
|LED      |CN7-1    | PC6       | D16               |
|MISO     |CN7-12   | PA6       | D12, MISO         |
|T_CLK    |CN10-32  | PB10      | D36, Touch CLK    |
|T_CS     |CN7-4    | PB9       | Touch Chip Select |
|T_DIN    |CN9-5    | PC3       | Touch Data In     |
|T_DO     |CN10-9   | PC2       | Touch Data OUt    |
|T_IRQ    |CN10-7   | PB1       | Touch Interrupt   |

## To-Do

 - [x] Partial framebuffer 
 - [x] Touchscreen
 - [] Graphs
 - [] FreeRTOS 

## Resources

 - [Official documentation](https://support.touchgfx.com/docs/introduction/welcome)

 Demakov Nikita, 2021