avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p vmfiles\_cout.c vmfiles\_xtoa.c vmfiles\admin0.c vmfiles\hal.c vmfiles\ioreg.c vmfiles\out.c vmfiles\vm.c vmfiles\vmstack.c -o test_o_hex\vm.o
avr-objcopy -O ihex -j .text -j .data test_o_hex\vm.o  test_o_hex\vm.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM4 -D -Uflash:w:test_o_hex\vm.hex:i
pause
