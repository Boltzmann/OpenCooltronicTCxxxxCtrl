#include"tc3215rs232.h"

// This code is self-explanatory.

void getAnswer(HANDLE hSerial){
  char ch[1];
  printf("-> ");
  while(ch[0]!='\x15'){
    ch[0]=receiveCharacter(hSerial);
    if(ch[0]!='\x15') 
      // '\x15' is character for end-of-message.
      printf("%c",ch[0]);
  }
  printf(" <-\n");
  return;
}
