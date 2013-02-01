
CC = i586-mingw32msvc-gcc

all :  OpenCooltroniCtrl.exe
clean :
	rm -f OpenCooltroniCtrl.exe



OpenCooltroniCtrl.exe : OpenCooltroniCtrl.c tc3215rs232.h recognEndOfLastMessage.c openport.c send2rs232.c sendCharacter.c ssendCharacter.c getTemp.c receiveCharacter.c errorcode.c sendReceiveCharacter.c ssendReceiveCharacter.c printCharacter.c sendOrder.c ssendOrder.c receiveDebugInfos.c getAnswer.c printFile.c
	$(CC) -Wall -o $@ $^
