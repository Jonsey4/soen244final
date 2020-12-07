#include "_interman.h"

#ifndef __hal_Interrupt_h
#define __hal_Interrupt_h
#include "_stdtype.h"

void Interrupt_Enable(){                Interrupt_Enable();                 }
void Interrupt_Disable(){               Interrupt_Disable();                }

u16 Interrupt_SaveAndDisable(){         return Interrupt_SaveAndDisable();  }

void Interrupt_Restore(u16 flags){      Interrupt_Restore(flags);           }

#endif