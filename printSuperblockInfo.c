#include "print.h"
#include <stdio.h>

void printSuperblockInfo(FileSystem* system) {
	printf("���������� � �������� �������:\n������ �����: %u ����\n������ FAT: %u ����\n������ Root: %u ����\n����� ����������: %u ����\n", system->superblock.sizeOFBlock, system->superblock.FATsize, system->superblock.rootSize, system->superblock.cypherShift);
}