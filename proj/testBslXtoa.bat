avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -DDebugXtoa vmfiles\bsl_COut.c vmfiles\_xtoa.c -o test_o_hex\bsl_COut.o
avr-objcopy -O ihex -j .text -j .data test_o_hex\bsl_COut.o  test_o_hex\bsl_COut.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM4 -D -Uflash:w:test_o_hex\bsl_COut.hex:i
pause
