#include"tc3215rs232.h"


int sendReceiveCharacter(HANDLE hSerial, char *ch)
{
  int rec;
  sendCharacter(hSerial, ch);
  rec=receiveCharacter(hSerial);
  printf("-> %c \n",rec);
  return rec;
}
