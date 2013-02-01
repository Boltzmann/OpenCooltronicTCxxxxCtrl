#include"tc3215rs232.h"
// Like sendReceiveCharacter(HANDLE hSerial, char *ch) but silent

int ssendReceiveCharacter(HANDLE hSerial, char *ch)
{
  int rec;
  ssendCharacter(hSerial, ch);
  rec=receiveCharacter(hSerial);
  return rec;
}
