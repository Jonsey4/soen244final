#ifndef anotherone
#define anotherone

void _Interrupt_Enable();
void _Interrupt_Disable();
u16 _Interrupt_SaveAndDisable();
void _Interrupt_Restore();
u16 _GetStatusReg();

#endif 