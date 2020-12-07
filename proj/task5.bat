avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p vmfiles\hal_Loader.c vmfiles\_cout.c vmfiles\_xtoa.c vmfiles\admin0.c vmfiles\hal.c vmfiles\ioreg.c vmfiles\out.c vmfiles\vm.c vmfiles\vmstack.c -o test_o_hex\vm5.o
avr-objcopy -O ihex -j .text -j .data test_o_hex\vm5.o  test_o_hex\vm5.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM3 -D -Uflash:w:test_o_hex\vm5.hex:i
pause
