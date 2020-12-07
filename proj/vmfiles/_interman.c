#include "avr/interrupt.h"
#include "avr/io.h"
#include "_interman.h"
#include "_stdtype.h"



void EnableInterrupts(){sei();}
void DisableInterrupts(){cli();}

u16 Interrupt_SaveAndDisable(){
    //return the SREG & disable interrupts
    u16 reg = SREG;
    cli();
    
    return reg;
}

void Interrupt_Restore(u16 flags){
    //take sreg as input
    //change the interrupt enable bit with
    SREG = flags;
}


