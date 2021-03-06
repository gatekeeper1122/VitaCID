#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"

#define printf psvDebugScreenPrintf

int _vshSblAimgrGetConsoleId(char CID[32]);

int WriteFile(char *file, void *buf, int size) {
	SceUID fd = sceIoOpen(file, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
	if (fd < 0)
		return fd;

	int written = sceIoWrite(fd, buf, size);

	sceIoClose(fd);
	return written;
}

int main(int argc, char *argv[]) {
	int i;
	char CID[32];

	// Init screen
	psvDebugScreenInit();

	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);

	printf("ConsoleID:\n");

	for (i = 0; i < 32; i++) {
		printf("%02X", CID[i]);
	}

	WriteFile("ux0:ConsoleID.bin", CID, 0x20);
	printf("\nSaved ConsoleID in ux0:CID.bin.\n");

	printf("\n\nAuto-exiting in 5 seconds...");

	sceKernelDelayThread(5 * 1000 * 1000);
	sceKernelExitProcess(0);

	return 0;
}
