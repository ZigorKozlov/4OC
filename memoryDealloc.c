#include "memoryDealloc.h"
#include <stdlib.h>
#include "readingFile.h"

void memory_dealloc(FileSystem* system) {
	free(system->root);
	for (int i = 0; i < system->superblock.FATsize / 8; ++i) {
		free(system->FAT[i]);
	}
	free(system->FAT);
	for (int i = 0; system->data[i] != NULL; ++i) {
		if (system->data[i] == NULL)
			break;
		free(system->data[i]);
	}
	free(system->data);
	free(system);
}
