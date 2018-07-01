# washer
Projeto de um sistema embarcado para lavadora de roupas.

## Documentação padrão
http://asf.atmel.com/docs/latest/

https://www.microchip.com/development-tools

# https://www.microchip.com/webdoc/samd21xplainedpro/index.html

+ http://asf.atmel.com/docs/3.35.1/samd21/html/index.html
+ PORT_IO  ==> http://asf.atmel.com/docs/3.35.1/samd21/html/asfdoc_sam0_port_basic_use_case.html
+ GFX_SPIN ==> http://asf.atmel.com/docs/latest/samd21/html/group__asfdoc__common2__gfx__mono__spinctrl.html#ga1fa0758397ad46035695689b03b00bbf
+ ADC      ==> http://asf.atmel.com/docs/3.35.1/samd21/html/group__asfdoc__sam0__adc__group.html
+ DMA      ==> http://asf.atmel.com/docs/3.35.1/samd21/html/group__asfdoc__sam0__dma__group.html
+ EXT_INT  ==> http://asf.atmel.com/docs/3.35.1/samd21/html/group__asfdoc__sam0__extint__group.html
+ TIMER    ==> http://asf.atmel.com/docs/3.35.1/samd21/html/group__asfdoc__sam0__rtc__count__group.html
+ DAC      ==> http://asf.atmel.com/docs/3.35.1/samd21/html/group__asfdoc__sam0__dac__group.html

# Referências
https://eewiki.net/display/microcontroller/Getting+Started+with+the+SAM+D21+Xplained+Pro+without+ASF
https://electronics.stackexchange.com/questions/139117/atmels-arm-programming-without-asf
http://ww1.microchip.com/downloads/en/DeviceDoc/40001882A.pdf
https://community.atmel.com/sites/default/files/forum_attachments/PIN-IO-SAMD21-SAMR21_RevA_0.pdf
https://www.zippyrobotics.com/samd21-intro/
http://asf.atmel.com/docs/latest/sam.drivers.usart.usart_synchronous_example.sam3u_ek/html/files.html  

# _TODOS_

- Open the index.html file to access CMSIS documentation __NOTE__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\CMSIS\README.txt](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\CMSIS\README.txt)
- : Definido o pino do adc. EXT1[3] - PB00_AIN8 - ADC+ __CHANGED__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h)
- : Fazer fun��es abaixo. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h)
- : Tirar o negado para funcionar corretamente, pegando o valor do btn conectado na placa. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c)
- :Definir os pinos corretos dos btns e dos led conectados na placa. Definir os pinos deles. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\pin_lib\btn_e_led.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\pin_lib\btn_e_led.h)
- :Definir valores que devem vir do pot. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.h)
- //Aqui dentro tem um if, ela s� retorna os defines. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.c)
- //Inicializar tudo, mede e tals. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\adc_lib\adc_lib.c)
- //Inicializar tudo, mede e tals. __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\Debug\TRABALHO_FINAL_EMBARCADOS.lss](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\Debug\TRABALHO_FINAL_EMBARCADOS.lss)
- can this value be deduced from properties field ? __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\wireless\ble_sdk\inc\at_ble_api.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\wireless\ble_sdk\inc\at_ble_api.h)
- can this value be deduced from properties field ? __TODO__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\wireless\ble_sdk\inc\at_ble_api.h](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\thirdparty\wireless\ble_sdk\inc\at_ble_api.h)
- Fica no estado de encher infinito quando configurado: pesado, medio, vapor __BUG__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c)
- Modificar a sequencia para encher, bater, molho, bater, esvaziar, encher, molho, esvaziar, enxaguar, centrifugar, secar __REVIEW__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c)
- variavel OK_pressed nao resetada ao finalizar cada estado __FIXME__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\main.c)
- you need to adjust according to your application. __NOTE__ [Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\sam0\utils\linker_scripts\samd21\gcc\samd21j18a_flash.ld](Printf&ProtoThread&Display&BLE\TRABALHO_FINAL_EMBARCADOS\src\ASF\sam0\utils\linker_scripts\samd21\gcc\samd21j18a_flash.ld)
