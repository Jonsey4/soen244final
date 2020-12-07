#ifndef __hal_Interrupt_h
#define __hal_Interrupt_h
#include "_interman.h"
#include "_stdtype.h"

void Interrupt_Enable(){                _Interrupt_Enable();                 }
void Interrupt_Disable(){               _Interrupt_Disable();                }

u16 Interrupt_SaveAndDisable(){         return _Interrupt_SaveAndDisable();  }

void Interrupt_Restore(u16 flags){      _Interrupt_Restore(flags);           }

u16 GetStatusReg(){                     return _GetStatusReg();      }

#endif