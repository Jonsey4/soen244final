#include "hal_Loader.h"
#include "Arduino.h"

// For now we will be using Serial object from arduino
void hal_Init() {
  Serial.begin(9600);
}

typedef struct{
  u32 programAdress;
  u32 programSize;
} Program;

u8 verifyChecksum(u8 packet[10]) {
  u8 cs = 0;
  for(int i = 2; i < packet[0]; i++) {
     cs += packet[i];
  }
  if(cs != packet[1]) {
    return CommandReturn_InvalidCmd;
  }
  return 0; 
}

void GetStatus(u8* status) {
  Serial.print(ack);
  Serial.print(0x03);
  Serial.print(*status);
  Serial.print(*status);
}

// executeCommand returns 1 when it reads a run command
u8 executeCommand(u8 packet[10], u8* mem,Program* program, u8* status) {
   u8 err = verifyChecksum(packet);
   if(err != 0) {
    Serial.print(nak);
    return 0;
   }
   if(packet[2] == PingCommand) {
      Serial.print(ack);
      return 0;
   } else if(packet[2] == GetStatusCommand) {
      GetStatus(status);
      return 0;
   }// else if(packet[2] == DownloadCommand) {
//      DownloadCommand(
//   } else if(packet[2] == SendDataCommand) {
//    
//   } else if(packet[2] == RunCommand) {
//    
//   } else if(packet[2] == ResetCommand) {
//    
//   }
   Serial.print(nak);
   return 0;
}


// Synchronous method that reads and executes all the neccessary commands before returning
u8 hal_Loader(u8* mem) {
  u8 parsingInProgress = 0;
  u8 packet[15];
  u8 index = 0;

  Program program{0,0};
  u8 status = 0;

  // Will have to replace with a function that read byte from nano UART buffer
  while(u8 d = Serial.read()){
    if(parsingInProgress){
      packet[index++] = d;
      if(index == packet[0]) {
        if(executeCommand(packet, mem, &programAdress, &status)){
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
