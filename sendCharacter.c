#include<windows.h>
#include<stdio.h>

int sendCharacter(HANDLE hSerial, char *ch)
{
  DWORD dwBytesWritten;
  fprintf(stdout,"Sending %s ...\n",ch);
  // windows.h provides the function WriteFile for writing
  // to a file handle e.g. the serial port file handle.
  WriteFile(hSerial,ch,1,&dwBytesWritten,NULL);
  return 0;
}
