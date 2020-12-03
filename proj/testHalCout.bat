avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p vmfiles\tout.c vmfiles\hal.c vmfiles\out.c vmfiles\_cout.c vmfiles\_xtoa.c -o test_o_hex\tout.o
avr-objcopy -O ihex -j .text -j .data test_o_hex\tout.o  test_o_hex\tout.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM4 -D -Uflash:w:test_o_hex\tout.hex:i
pause
