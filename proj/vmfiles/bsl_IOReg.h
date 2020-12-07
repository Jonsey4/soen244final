/* bsl_IOReg.h - IO Register Interface
//
// Copyright (C) 2020 by Michel de Champlain
//
*/

#ifndef __bsl_IOReg_h
#define __bsl_IOReg_h

#include "_stdtype.h"

u32  _IOReg_Read (u32 ioreg);
void _IOReg_Write(u32 ioreg, u32 value);

#endif
