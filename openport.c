#include<stdio.h>
#include<io.h>
#include<windows.h>
#include"tc3215rs232.h"

HANDLE openport(char portname[4])
{
  // Port is opened for reading and writing. 
  HANDLE hSerial = CreateFile(portname, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
		       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  // If something went wrong, here is error handling:
  if(hSerial==INVALID_HANDLE_VALUE){
    if(GetLastError()==ERROR_FILE_NOT_FOUND){
      fprintf(stderr, "Serial port is not initializable (does not exist)");
    }
    fprintf(stderr, "An error - whatever it is - ocurred");
    errorcode();
  }
  else{
    fprintf(stdout, "%s is initialized\n", portname);
  }

  // Parameters for communication with serial port are set here.
  DCB dcbSerialParams = {0};

  if(!GetCommState(hSerial, &dcbSerialParams)){
    fprintf(stderr, "Can't get parameters of the serial port.\n");
  }

  // For these values have a look at the instructions for your controller.
  dcbSerialParams.BaudRate=CBR_9600;
  dcbSerialParams.ByteSize=8;
  dcbSerialParams.StopBits=TWOSTOPBITS;
  dcbSerialParams.Parity=NOPARITY;
  
  // error handling:
  if(!SetCommState(hSerial, &dcbSerialParams)){
    fprintf(stderr, "Am not able to set port state.\n");
  }

 return hSerial;
}
