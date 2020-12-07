#include "_uart.h"  //<-- change this to .h??
#include "hal_Loader.h"


void hal_Init_Loader() {
//   COut_Init();
}

typedef struct{
  u32 adress;
  u32 sizee;
  u32 index;
  u32 runAdress;
} Program;

u8 verifyChecksum(u8* packet) {
  u8 cs = 0;
  for(int i = 2; i < packet[0]; i++) {
     cs += packet[i];
  }
  if(cs != packet[1]) {
    return CommandReturn_InvalidCmd;
  }
  return 0; 
}

void getStatusCommand(u8* status) {
  TxChar(ack);
  TxChar(0x03);
  TxChar(*status);
  TxChar(*status);
  TxChar(0x00);
}

void downloadCommand(u8* packet, Program* program) {
  // Should always be 32 bit number so we can harcode the indexes
  program->adress = ((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8) | ((u32)packet[6] << 0);
  program->sizee = ((u32)packet[7] << 24) | ((u32)packet[8] << 16) | ((u32)packet[9] << 8) | ((u32)packet[10] << 0);
  TxChar(ack);
  TxChar(0x00);
}

void sendDataCommand(u8* packet, Program* program, u8* mem) {
  for(int i = 3; i < packet[0]; i++) {
    mem[program->index++] = packet[i];
    program->sizee += 8;
  }
  TxChar(ack);
  TxChar(0x00);
}

void runCommand(u8* packet,Program* program) { 
  program->runAdress = ((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8) | (u32)(packet[6] << 0);
  TxChar(ack);
  TxChar(0x00);
}

// executeCommand returns 1 when it reads a run command
u8 executeCommand(u8* packet, u8* mem,Program* program, u8* status) {
//    u8 err = verifyChecksum(packet);
//    if(err != 0) {
//     TxChar(nak);
//     TxChar(0x00);
//     return 0;
//    }
   if(packet[2] == PingCommand) {
      TxChar(ack);
      TxChar(0x00);
      return 0;
   } else if(packet[2] == GetStatusCommand) {
      getStatusCommand(status);
      return 0;
   } else if(packet[2] == DownloadCommand) {
      downloadCommand(packet, program);
      return 0;
   } else if(packet[2] == SendDataCommand) {
      sendDataCommand(packet, program, mem);
      return 0;
   } else if(packet[2] == RunCommand) {
      runCommand(packet, program);
      return 1;
   } else if(packet[2] == ResetCommand) {
      // No really know the protocol meant be reset 
      program->adress = 0;
      program->index = 0;
      program->runAdress = 0;
      program->sizee = 0;
      return 0;
   }
   TxChar(nak);
   TxChar(0x00);
   return 0;
}


// Synchronous method that reads and executes all the neccessary commands before returning
u8 hal_Loader(u8* mem) {
  u8 parsingInProgress = 0;
  u8 packet[15];
  u8 index = 0;

  Program program = {.adress=0,.sizee = 0,.index = 0,.runAdress = 0};
  u8 status = 0;

  while(1){
    u8 d = RxChar();
    if(parsingInProgress > 0){
      packet[index++] = d;
      if(index == (packet[0] + 1)) {
        if(executeCommand(packet, mem, &program, &status)){
            status = CommandReturn_Success;
            parsingInProgress = 0;
            return 0;  
        }
        status = CommandReturn_Success;
        parsingInProgress = 0;
        index = 0;
      }
    } else {
      packet[index++] = d; 
      parsingInProgress = 1;     
    }
  }   
}