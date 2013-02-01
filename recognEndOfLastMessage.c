#include<stdio.h>

int recognEndOfLastMessage(FILE **port)
{
  int k=0,j=0;
  while(k!=21){
    j++;
    fprintf(stdout, "Nicht da");
    k=fgetc(*port);
    fprintf(stdout,"%i\n",k);
    if(k==42) fprintf(stdout,"The character '*' is found!");
    else{ 
      if(j>=30) return -1;
    }
  }
  return 0;
}
