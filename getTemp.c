#include"tc3215rs232.h"

// Like getAnswer, but giving the answer as a return value.

int getTemp(HANDLE hSerial){
  char num[5];
  __int16 i,n =0;
  for(n=0;n<5;n++)
  {

    num[n]=receiveCharacter(hSerial);
	  //printf("%c\n",num[n]);
	  if(num[n]==21) //temperature string is terminated ascii char 21
	  {
		//printf("break\n");
		break;
	}
  }
  i= atoi(num);
  //printf("%s \n",num);
  //printf("%d \n",-i);
     
  return i;
}
