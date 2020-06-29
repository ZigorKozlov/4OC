#include "print.h"
#include <stdio.h>

void printFilesList(FileSystem* system) {
	printf("ID\tНаименование\n");
	for (int i = 0; i < system->superblock.rootSize; ++i) {
		printf("%d\t%s\n", system->root[i].numberOfFirstFileBlock, system->root[i].nameOfFile);
	}
}