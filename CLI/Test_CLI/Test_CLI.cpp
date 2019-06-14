// Test_CLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CLI.h"
#include "Windows.h"

void hexDump(char *desc, void *addr, int len) {
	int i;
	unsigned char buff[17];
	unsigned char *pc = (unsigned char*)addr;

	// Output description if given.
	if (desc != NULL)
		printf("%s:\n", desc);

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).

		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0)
				printf("  %s\n", buff);

			// Output the offset.
			printf("  %04x ", i);
		}

		// Now the hex code for the specific character.
		printf(" %02x", pc[i]);

		// And store a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buff[i % 16] = '.';
		else
			buff[i % 16] = pc[i];
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		printf("   ");
		i++;
	}

	// And print the final ASCII bit.
	printf("  %s\n", buff);
}

#define SENDSIZE 1024*100

int _tmain(int argc, _TCHAR* argv[])
{

	int fd = 0;
	int fd_data = 0;
	int cnt = 10;
	int result = 0;
	int i = 0;
	BYTE* val = (BYTE*)malloc(SENDSIZE);
	val[0] = 0xab;

//	fd_data = NetCon("192.168.1.50", "5556");

	for (i = 0; i < cnt; i++){
		printf("ROUND:%d\n", i);
//	fd = NetCon("192.168.0.186", "5556");
//	fd_data = NetCon("192.168.0.186", "5556");
//	fd = NetCon("192.168.1.50", "5556");
		fd_data = NetCon("192.168.0.199", "5556");

//		result = getImagefromRemote(fd, 10);
		
//		result = setDataFromRemote(fd_data, 0x08000000, SENDSIZE, WBCOM, val);
		result = getDataFromRemote(fd_data, 0x04000000, 4, WB0, val );
//	hexDump("READ", val, 1024);
		if (result < 0) break;

//		deleteList_ALL();
		
//		NetClo(fd);
		
//		result = setDataFromRemote(fd_data, 0x08000000, SENDSIZE, WBCOM, val);
		NetClo(fd_data);
	}
	
	printf("Finish!");
	while (1){
		Sleep(1000);
	}
	return 0;
}

