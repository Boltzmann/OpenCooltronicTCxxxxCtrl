#include<stdio.h>
#include<windows.h>

int send2rs232(FILE *port, char ch)
{
  int k=0;
  fprintf(stdout,"\n %c wird gesendet.\n",ch);
  fputc(ch,stdout);
  fputc(ch,port);
  fprintf(port,"\r\nTestaoi_dfja\r\n");
  fflush(port);
  if(ch!='*'){
    //    Sleep(50);
    k=fgetc(port);
    //fflush(port);
    fprintf(stdout,"->%c\n" ,k);
  }
  return k;
}
/*
int e=fputc(ch,port);
  int feofi = feof(port);
  int ferr = ferror(port);
  fprintf(stdout, "\n%i %i\n",feofi,ferr);
  char lastError[1024];
  FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		lastError,
		1024,
		NULL);
  fprintf(stdout,"%s",lastError);
*/
