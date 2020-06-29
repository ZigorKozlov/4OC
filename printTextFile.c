#pragma once
#include <stdio.h>
#include "print.h"

#define _true 1

void printTextFile(FileSystem* system, int numberOfFirstFileBlock) {
	int i = 0;
	for (int j = 0; j < system->superblock.FATsize / 8; ++j) {
		if (system->FAT[i][0] == numberOfFirstFileBlock) {
			i = j;
			break;
		}
	}
	while (_true) {
		printf("%s", system->data[system->FAT[i][0]]);
		if (system->FAT[i][1] != EOC)
			i = system->FAT[i][1];
		else
			break;
	}
}