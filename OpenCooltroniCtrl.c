/*!
 * @file
 * @author Stefan Bollmann <stefan.bollmann@rwth-aachen.de>
 * @deputy author ;-): Felix Ruedinger
 * @version 1.0 
 * Written at and for www.super-resolution.de at 
 * biozentrum.uni-wuerzburg.de.
 * 
 * This file produces a menu for Communication of TC3215rs232 with 
 * serial port of a windows PC. Sending orders, reading settings 
 * and starting/stopping debug mode is implemented.
 * 
 */



#include"tc3215rs232.h"
#include <conio.h>
#include <math.h>
#include <string.h>
#include <time.h>


int APIENTRY WinMain(HINSTANCE hInstance,
		     HINSTANCE hPrevInstance,
		     LPTSTR lpCmdLine,
		     int nCmdShow)
/*!
 * This is the main part of the program. 
 */
{
#ifdef _DEBUG
  RedirectIOToConsole();
#endif
  
      /*!
       * A command line user-interface is made.
       * 
       * For help using COM-ports I refer to 
       * http://www.robbayer.com/serial.php
       * 
       * For help relating orders and meanings of
       * send/received characters, have a look
       * at 20100530_TC3215_Manual_109D.pdf 
       * (The manual of TC3215)
      */

  time_t rawtime; //Initializing Time
  time_t lasttime;
  struct tm * timeinfo;
  char buffer [20];
  char buffer2[9];
  
  char selection[3];
  selection[0]='0';
  
  HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 7); // 7 = std color, 10 = green, 12 = red

  
  while(selection[0]!='q'){
    selection[0]='0';

    fprintf(stdout,"\nWhat do you like me to do?\n");
    fprintf(stdout,"a - start debug\t\t b - end debug\t g - get debug output\n");
    fprintf(stdout,"r - read value\t\t w - write value\n");
    fprintf(stdout,"m - monitor temp\t t - read temp continuously\n");
    fprintf(stdout,"p - change port\t\t q - Quit\n");

    scanf("%1s",selection);

    HANDLE hSerial=openport("COM7");
    int rep, maxrep=1000; // Debug lines are read maxrep times.
    switch( selection[0] )
      {
      case 'g':
	    for(rep=0; rep<maxrep; rep++){
	    receiveDebugInfos(hSerial);
		}
		break;
      case 'p':
		// Serial port is closed.
		CloseHandle(hSerial);
		fprintf(stdout,"\nWhat port shall I use? \n 1 or 5\n");
		// portnumber selection
		scanf("%1s",selection);
		char whichport[]="COM";
		strcat(whichport,selection);
		// e.g. ->"COM5" with selection="5"
		fprintf(stdout,whichport);
		hSerial=openport(whichport);
		break;
      case 'a':
		sendOrder(hSerial, STARTDEBUG);
		break;
      case 'b':
		FlushFileBuffers(hSerial);
		sendOrder(hSerial, ENDDEBUG);
		break;
      case 'r':
		printf("Type the number of the command.");
		printFile("instructionSet.asc"); 
		// 4 knowing what order what number is.
		char readOrder[]="r_";
		scanf("%3s",selection);			
		// Felix: I changed max. digits to 3.
		// Reading orders have the structure
		// r_xx_0 with xx a number relating 
		// to what user wants to know 
		// (see TCOM pdf or instructionSet.asc)
		strcat(readOrder,selection);
		strcat(readOrder,"_0");
		// The order that will be sent:
		printf("%s",readOrder);
		FlushFileBuffers(hSerial);
		sendOrder(hSerial,readOrder);
		getAnswer(hSerial);
		printf("\n");
		break;
      case 'w':
		printf("Type the number of the command.\n");
		printFile("instructionSet.asc"); // 4 knowing what order what number is.
		char writeOrder[20]="w_";
		char value[5]="0";
		scanf("%2s",selection);
		// Writing orders have the structure
		// w_xx_yy with xx and yy depicting numbers 
		// to what user wants to set and
		// yy the value to set.
		// (see TCOM pdf or instructionSet.asc)
		strcat(writeOrder,selection);
		strcat(writeOrder,"_");
		printf("What value do you want to send?\n");
		scanf("%5s",value);
		strcat(writeOrder,value);
		printf("%s",writeOrder);	
		// Felix: Not necessary, comment out?
		// Stefan: Maybe... ;-)
		FlushFileBuffers(hSerial);
		sendOrder(hSerial,writeOrder);
		printf("\n");
		break;
	  case 't':
		printf("\nReading Temperature...\nPress any key to stop.\n\n");
		
		FILE *tFile;
		tFile = fopen("templog.txt", "a");
		int temp=0;
		
		while(1)
		{
			FlushFileBuffers(hSerial);
			ssendOrder(hSerial,"r_120_0");
			temp = getTemp(hSerial);
			
			//Writing time to a buffer
			
			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			strftime (buffer,20,"%Y-%m-%d;%H:%M:%S",timeinfo);
			
			fprintf(tFile, "%s;%4.1f\n",buffer,temp/10.0);
			printf("%s\t%4.1fC\n",buffer,temp/10.0);
			if (kbhit()) 
			{
				_getch(); 
				// Intercepting key that is pressed to stop the loop
				break;
			}
			Sleep(5000);
		}
		fclose(tFile);
	  break;
	  case 'm':
		printf("Please type the temperature you would like to set for the specimen. \n Valid arguments: 7.0 - 45.0.\n");
		char tempinput[4];
		char temporder[20] = "w_0_";
		char kporder[20] = "w_6_3";
		char kiorder[20] = "w_7_1";
		char kdorder[20] = "w_8_0";
		char ilorder[20] = "w_9_999";
		char pwmlimitorder[20] = "w_10_127";
		char filterorder[20] = "w_4_4";
		char setValRamporder[20] = "w_12_30"; 
		//Set temperature ramp to 3.0°C/min max
		char tolRangeorder[20] = "w_2_1"; //Set tolerated range to +/- 0.1°C
		char alarmRangeorder[20] = "w_3_1"; //Set alarm range to +/- 0.1°C
		int targettemp;
		
		scanf("%4s",tempinput);
		if(atof(tempinput) == 0.0 || atof(tempinput) < 7.0 || atof(tempinput) > 45.0)
			targettemp = 200;
		else
			targettemp =(int) floor(((10*atof(tempinput)-29)/0.833)+0.5);  //taken from calibration fit parameters
		sprintf(tempinput,"%d",targettemp);
		strcat(temporder,tempinput);
		ssendOrder(hSerial,temporder);
		printf("\n\n=================================================================\nTarget temperature set to %4.1fC so the \nspecimen will have the specified temperature.  \n",targettemp/10.0);
		ssendOrder(hSerial,kporder);
		ssendOrder(hSerial,kiorder);
		ssendOrder(hSerial,kdorder);
		ssendOrder(hSerial,ilorder);
		ssendOrder(hSerial,pwmlimitorder);
		ssendOrder(hSerial,filterorder);
		ssendOrder(hSerial,setValRamporder);
		ssendOrder(hSerial,tolRangeorder);
		ssendOrder(hSerial,alarmRangeorder);
		printf("With KP=3, KI=1, KD=0, IL=999, PWNLimit=127, Filter=10s\n setValRamp=30, tolRange=1, alarmRange=1.\n\n Monitoring temperature...\n=================================================================\n\n");
		long int tcount=0; // tcount is increased every time the temperature is within +/- 0.3K of targettemp
		int tempatm=0; // Temperature at the moment as read from the sensor
		FILE *tlFile;
		tlFile = fopen("templog2.txt", "a");
		time( &lasttime );
		BOOL startmeasurement = FALSE;
		
		while(1) // 300s = 5min
		{
			ssendOrder(hSerial,"r_120_0");
			FlushFileBuffers(hSerial);
			tempatm = getTemp(hSerial);
			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			strftime (buffer,20,"%Y-%m-%d;%H:%M:%S",timeinfo);
			strftime (buffer2,9,"%H:%M:%S",timeinfo);
			if(tempatm <= targettemp+3 && tempatm >= targettemp-3)
			{
				tcount += (int)difftime(rawtime,lasttime);
				printf("%s - Temperature ok at %.1fC since %lds.\n",buffer2,tempatm/10.0, tcount);
				fprintf(tlFile, "%s;%4.1f;OK\n",buffer,tempatm/10.0);
			}
			else
			{
				printf("%s - Temperature out of boundaries: %.1fC\n",buffer2,tempatm/10.0);
				fprintf(tlFile, "%s;%4.1f;OOB\n",buffer,tempatm/10.0);
				tcount = 0;
			}
			
			lasttime=rawtime;
			/*
			if (tempatm <= lasttemp+1 && tempatm >= lasttemp-1) 
				ecount++;
			else
			{
				ecount=0;
				lasttemp = tempatm;
			}
			if (ecount >= 15)
			{
				ssendOrder(hSerial,"w_10_0"); // Set PWNLimit to 0
				printf("\n\n=================================================================\n\n");
				printf("FATAL ERROR: Temperature was within +/- 0.1K in the last 30s!");
				printf("\n\n=================================================================\n\n");
				break;
			}
			*/
			if (kbhit()) 
			{
				_getch(); // Intercepting key that is pressed to stop the loop
				break;
			}
			Sleep(5000);
			if ((tcount >=300) && !startmeasurement)
			{
				SetConsoleTextAttribute(hConsole, 10);
				printf("\n === Temperature stable for 5min now, measurement can be started. === \n === Press any key to stop monitoring. === \n");
				SetConsoleTextAttribute(hConsole, 7);
				Beep(1000,500);
				startmeasurement = TRUE;
			}
		}
		fclose(tlFile);
	  break;
	  default:
		printf("\n Please type one of the characters above.\n");
	  break;
	  }
    CloseHandle(hSerial);
  }

  // When quitting I'd like to see the output.
  _getch();
  
  return 0;
}

//End of File
