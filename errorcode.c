#include<stdio.h>
#include<windows.h>
#include"tc3215rs232.h"

int errorcode()
{
  char lastError[1024];
  // All error codes fit into lastError. 
  FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(), // a windows.h provided function with non 
		// understandable error code.
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		lastError, // this is a string with understandable error code.
		1024, // size of lastError.
		NULL);
  fprintf(stderr, "%s\n",lastError); // error message is written to error output.
  return 0;
}
