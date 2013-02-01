#include"tc3215rs232.h"
// Like sendOrder(HANDLE hSerial, char order[20]) but silent

int ssendOrder(HANDLE hSerial, char order[20])
{
  int ch[2], nr=0;
  // Sometimes - e.g. in debug mode - the PID
  // doesn't get the request for communication.
  // Therefore this loop:
  while(ch[0]!='A'){
    ssendCharacter(hSerial,"*");
    ch[0]=ssendReceiveCharacter(hSerial,"A");
    nr++;
  }
  ch[0]=ssendReceiveCharacter(hSerial,"_");
  // Usually the PID echoes the sent character. 
  // If the while loop ahead runs often, there seems 
  // to be some kind of queue of 'A's somewhere - 
  // maybe the PID is still echoing or there is 
  // is some buffer related stuff I don't understand.
  //
  // Here comes my workaround:
  int tmp=0;
  while(tmp<=nr && ch[0]!='_'){
    ch[0]=receiveCharacter(hSerial);
    tmp++;
  }
  // Now the rest of the order is normally understood.
  for (nr = 0; nr < strlen(order); nr++){
    // Sending is character by character. At the end 
    // sending is done by WriteFile, therefore
    // strings have to be sent.
    char orderCharacter[2];
    orderCharacter[0]=order[nr]; // orderCharacter is only a character.
    orderCharacter[1]='\0'; // now it is a string.
    ssendReceiveCharacter(hSerial,orderCharacter);
  }
  ch[0]=ssendReceiveCharacter(hSerial,"\x15");
  // This character is the confirmation for PID that 
  // order is complete.
  ch[0]=receiveCharacter(hSerial);
  // '.' is TC3215 ACK character.
  if(ch[0]!='.')
    fprintf(stderr,"Somethings wrong with Sending order.\n");
  return 0;
}
