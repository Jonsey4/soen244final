avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p vmfiles\hal_TestInterman0.c vmfiles\_interman.c vmfiles\hal.c vmfiles\out.c vmfiles\_cout.c vmfiles\_xtoa.c -o test_o_hex\hal_TestInterman0.o
avr-objcopy -O ihex -j .text -j .data test_o_hex\hal_TestInterman0.o  test_o_hex\hal_TestInterman0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM3 -D -Uflash:w:test_o_hex\hal_TestInterman0.hex:i
pause
