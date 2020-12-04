#include "hal_Loader.h"
#include "Arduino.h"

// For now we will be using Serial object from arduino
void hal_Init() {
  Serial.begin(9600);
}

typedef struct{
  // Don't really know the use of the adress, but we will keep it for now
  u32 adress;
  u32 sizee;
  u32 index;
  // Not sure of its use too, probably won't use it
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
  Serial.print(ack);
  Serial.print(0x03);
  Serial.print(*status);
  Serial.print(*status);
}

void downloadCommand(u8* packet, Program* program) {
  // Should always be 32 bit number so we can harcode the indexes
  program->adress = (packet[3] << 24) | (packet[4] << 16) | (packet[5] << 8) | (packet[6] << 0);
  program->sizee = (packet[7] << 24) | (packet[8] << 16) | (packet[9] << 8) | (packet[10] << 0);
  Serial.print(ack);
}

void sendDataCommand(u8* packet, Program* program, u8* mem) {
  for(int i = 3; i < packet[0]; i++) {
    mem[program->index++] = packet[i];
    program->sizee += 8;
  }
  Serial.print(ack);
}

void runCommand(u8* packet,Program* program) { 
  program->runAdress = (packet[3] << 24) | (packet[4] << 16) | (packet[5] << 8) | (packet[6] << 0);
  Serial.print(ack);
}

// executeCommand returns 1 when it reads a run command
u8 executeCommand(u8* packet, u8* mem,Program* program, u8* status) {
   u8 err = verifyChecksum(packet);
   if(err != 0) {
    Serial.print(nak);
    return 0;
   }
   if(packet[2] == PingCommand) {
      Serial.print(ack);
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
      *program = Program{0,0,0,0};
      return 0;
   }
   Serial.print(nak);
   return 0;
}


// Synchronous method that reads and executes all the neccessary commands before returning
u8 hal_Loader(u8* mem) {
  u8 parsingInProgress = 0;
  u8 packet[15];
  u8 index = 0;

  Program program{0,0,0,0};
  u8 status = 0;

  // Will have to replace with a function that read byte from nano UART buffer
  while(u8 d = Serial.read()){
    if(parsingInProgress){
      packet[index++] = d;
      if(index == packet[0]) {
        if(executeCommand(packet, mem, &program, &status)){
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
