/* _cout.c - Implementation of a Console for Cm Hardware Abstract Layer for Output Interface.
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#include "_outdesc.h"

#if ConsoleOutputWithPrintf

#include <stdio.h>

static void COut_PutB(bool b)        { printf("%s", b ? "true" : "false"); }
static void COut_PutC(char c)        { printf("%c", c); }
static void COut_PutS(const char* s) { printf("%s", s); }
static void COut_PutI(i32  i)        { printf("%ld", i); }
static void COut_PutU(u32  u)        { printf("%lu", u); }
static void COut_PutX(u32  u)        { printf("%08lX", u); } // To make hex output always aligned to 8 hex digits.
static void COut_PutN(void)          { printf("\n"); }

#else
#include "_xtoa.h"
#include <avr/io.h>
//#include <avr/interrupt>

#define BAUD 103

// Transmit a character to UART. Actual Transmission
static void TxChar(char c) {
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

//Reception
static char RxChar(void){
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

static void COut_Init(void) {
    // your code...
    //Enable TX pin for output
    DDRD |= (1 << PD1);

    //Hardcoding the baud 
    UBRR0 = BAUD;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    //8 data bits, 1 Stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    
    
    UDR0;
}


// External refs to 'console.c' without
void  Console_Putchar(char  c){ TxChar(c);};

static char  buf[12];                /* to cover max size (12) "i32" (10+sign+null) */

static void COut_PutB(bool b)        { Console_Putchar(b ? 'T' : 'F'); }
static void COut_PutC(char c)        { Console_Putchar(c); }
static void COut_PutS(const char* s) { while (*s) Console_Putchar(*s++); }
static void COut_PutI(i32  i)        { System_itoa(i, buf); COut_PutS(buf); }
static void COut_PutU(u32  u)        { System_utoa(u, buf, 10); COut_PutS(buf); }
static void COut_PutX(u32  x)        { System_utoa(x, buf, 16); COut_PutS(buf); } // Same behavior as Dos16 VM: 
                                                                                   // Hex alpha in upppercase
static void COut_PutN(void)          { Console_Putchar('\n'); }
#endif

static IVMOutDesc cout = {
    COut_PutB,
    COut_PutC,
    COut_PutI,
    COut_PutU,
    COut_PutS,
    COut_PutX,
    COut_PutN
};

static bool init = 0;

IOut Out_GetFactory(const char* whichOne) {
    if (!init){
        whichOne = 0; // To avoid the warning on the unreferenced formal parameter
        COut_Init();
        init = true;
    }
    return &cout;
    
}
