avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p vmfiles\TestInterman0.c vmfiles\interman.c vmfiles\hal.c vmfiles\out.c bsl_Uart.c bsl_COut.c bsl_xtoa.c -o hal_TestInterman0.o
avr-objcopy -O ihex -j .text -j .data hal_TestInterman0.o  hal_TestInterman0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -Uflash:w:hal_TestInterman0.hex:i
pause
