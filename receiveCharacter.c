#include<windows.h>
#include<stdio.h>
#include"tc3215rs232.h"

int receiveCharacter(HANDLE hSerial)
{
  char ch[2];
  DWORD dwBytesRead=0;
  // The next if request reads data from serial port (hSerial)
  // stores the data (one character) in ch and if
  // the port was unreadable an error is given to 
  // error output.
  if(!ReadFile(hSerial, ch, 1, &dwBytesRead, NULL)){ 
    fprintf(stderr,"receiveCharacter:\n");
    errorcode();
  }
  // At the end the result of the reading process is returned.
  return ch[0];
}
