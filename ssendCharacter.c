#include<windows.h>
#include<stdio.h>
// Like sendCharacter(HANDLE hSerial, char *ch) but silent

int ssendCharacter(HANDLE hSerial, char *ch)
{
  DWORD dwBytesWritten;
  // windows.h provides the function WriteFile for writing
  // to a file handle e.g. the serial port file handle.
  WriteFile(hSerial,ch,1,&dwBytesWritten,NULL);
  return 0;
}
