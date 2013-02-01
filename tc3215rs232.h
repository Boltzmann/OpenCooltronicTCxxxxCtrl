// tc3215rs232.h

#ifndef __TC3125RS232_H__ 
#define __TC3125RS232_H__ 

#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<math.h>

// the definitions of the names given here are token
// from 20100530_TC3215_Manual_109D.pdf p. 24
// (the manual of TC3215).
#define STARTDEBUG "d_1_0"
#define ENDDEBUG "d_0_0"

// I think everything gets clearer, when you have a look
// into the files or test.c
HANDLE openport(char portname[4]);
int recognEndOfLastMessage(HANDLE port);
int sendCharacter(HANDLE hSerial, char *ch);
int receiveCharacter(HANDLE hSerial);
int errorcode();
int sendReceiveCharacter(HANDLE hSerial, char *ch);
int sendOrder(HANDLE hSerial, char order[20]);
int ssendOrder(HANDLE hSerial, char order[20]);
int ssendReceiveCharacter(HANDLE hSerial, char *ch);
int ssendCharacter(HANDLE hSerial, char *ch);
int getTemp(HANDLE hSerial);
void receiveDebugInfos(HANDLE hSerial);
void printCharacter(int ch);
void getAnswer(HANDLE hSerial);
void printFile(char filename[30]);
#endif
