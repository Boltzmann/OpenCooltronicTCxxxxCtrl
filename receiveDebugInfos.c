#include"tc3215rs232.h"

void receiveDebugInfos(HANDLE hSerial){
  int ch[2];
  double temperature=0;
  int kp=0, ki=0, kd=0, i;
  int temp[10], j=0;
  ch[0]=123, ch[1]=123;
  // I wanted to be sure, that temp has some
  // starting value..
  for(i=0;i<6;i++)
    temp[j]='*';
  // The input from the PIC controller has
  // to have some point, where \x15 is followed
  // by '*'. This is the starting point for 
  // reading debug output.
  while(ch[0]!=21 || ch[1]!='*') {
    ch[0]=receiveCharacter(hSerial);
    if(ch[0]==21){
      ch[1]=receiveCharacter(hSerial);
    }
  }
  // At first there is temperature information
  // until '_' is sent by PIC.
  while(temp[j]!='_' && j<6){
  j++;
  temp[j]=receiveCharacter(hSerial);
  }
  for (i=1;i<j;i++) {
    // temp[]-48 is conversion from character to value.
    // temp has j-1 digits. The last one is a decimal place
    // therefore the subtraction j-2 in pow.
    temperature+=(double)(temp[i]-48)*pow(10,j-i-2);
  }
  printf("Temperature %.3f ", temperature);
  j=0;
  // Then the output is Kp until next '_' is sent.
 while(temp[j]!='_' && j<6){
   j++;
   temp[j]=receiveCharacter(hSerial);
 }
 for (i=1;i<j;i++) {
   // See temperatur for explanation. this time, there
   // is j-i-1, because the value is integer.
   kp+=(int)(temp[i]-48)*pow(10,j-i-1);
 }
 if(kp>1000) kp-=65536;
 printf("Kp %i ", kp);
 j=0;
 while(temp[j]!='_' && j<6){
   j++;
   temp[j]=receiveCharacter(hSerial);
 }
for (i=1;i<j;i++) {
  ki+=(int)(temp[i]-48)*pow(10,j-i-1);
 }
 if(ki>1000) ki-=65536;
 printf("Ki %i ", ki);
 j=0;
 while(temp[j]!=21 && j<6){
   j++;
   temp[j]=receiveCharacter(hSerial);
 }
 for (i=1;i<j;i++) {
   kd+=(int)(temp[i]-48)*pow(10,j-i-1);
 }
 if(kd>1000) kd-=65536;
 printf("Kd %i\n", kd);
 return;
}

  
