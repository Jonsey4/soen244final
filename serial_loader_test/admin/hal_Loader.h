#ifndef __hal_Loader_h
#define __hal_Loader_h

#include "_out.h"

#define ack  0xCC
#define nak  0x33

#define PingCommand 0x20
#define GetStatusCommand 0x23
#define DownloadCommand 0x21
#define SendDataCommand 0x24
#define RunCommand 0x22
#define ResetCommand 0x25


#define CommandReturn_Success 0x40
#define CommandReturn_UnknownCmd 0x41
#define CommandReturn_InvalidCmd 0x42
#define CommandReturn_InvalidAddr 0x43
#define CommandReturn_MemoryFail 0x44


void hal_Init(void);
u8 hal_Loader(u8* mem);

#endif
