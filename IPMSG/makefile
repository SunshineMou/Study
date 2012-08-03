OBJ=common.o ipmsgMain.o sysInfo.o userManager.o userInterface.o fileManager.o 
CFLAGS=-lpthread
CC=gcc

IPMSG:$(OBJ)
	$(CC) -o $@ -g -rdynamic $^ $(CFLAGS)
%o:%c	
	$(CC) -c -o $@ $^

clean:
	-rm *.o main
	-echo Cleanning...
