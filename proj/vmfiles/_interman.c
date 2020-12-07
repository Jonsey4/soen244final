#include "avr/interrupt.h"
#include "avr/io.h"
#include "_stdtype.h"
#include "_interman.h"




void _Interrupt_Enable(){sei();}
void _Interrupt_Disable(){cli();}

u16 _Interrupt_SaveAndDisable(){
    //return the SREG & disable interrupts
    u16 reg = SREG;
    cli();
    
    return reg;
}

void _Interrupt_Restore(u16 flags){
    //take sreg as input
    //change the interrupt enable bit with
    SREG = flags;
}


