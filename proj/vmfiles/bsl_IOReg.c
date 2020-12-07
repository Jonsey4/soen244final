#ifndef bsl_IOReg_h
#define bsl_IOReg_h
#include "_stdtype.h"
#include <avr/io.h>

u32  _IOReg_Read (u32 ioreg) {
    // We need to remove 0x20 because the test is shifted + 0x20
    return((u32)_SFR_IO8(ioreg - 0x20));
}
void _IOReg_Write(u32 ioreg, u32 value) {
    _SFR_IO8(ioreg - 0x20) = value;
}

#endif