#include "avr/interrupt.h"
#include "_interman.h"

void EnableInterrupts(){sei();}
void DisableInterrupts(){cli();}

