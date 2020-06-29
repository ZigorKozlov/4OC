#include "print.h"
#include <stdio.h>

void printSuperblockInfo(FileSystem* system) {
	printf("Информация о файловой системе:\nРазмер блока: %u байт\nРазмер FAT: %u байт\nРазмер Root: %u байт\nСдвиг шифрования: %u байт\n", system->superblock.sizeOFBlock, system->superblock.FATsize, system->superblock.rootSize, system->superblock.cypherShift);
}