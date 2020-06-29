#include "print.h"
#include <stdio.h>

#define READ_ONLY 0x20
#define HIDDEN 0x10
#define SYSTEM 0x8
#define MARK 0x4
#define SUBDIRECTORY 0x2
#define ARCHIVE 0x1

void printRootInfo(FileSystem* system) {
	for (int i = 0; i < system->superblock.rootSize; ++i) {
		if ((system->root[i].attributes & READ_ONLY) == READ_ONLY) {

			printf("����: %s (������ ��� ������)\n", system->root[i].nameOfFile);
		}
		else {
			if ((system->root[i].attributes & HIDDEN) == HIDDEN) {
				//�� ���������� ������� �����
				continue;
			}
			else {
				if ((system->root[i].attributes & SYSTEM) == SYSTEM) {
					printf("����: %s (���������)\n", system->root[i].nameOfFile);
				}
				else {
					if ((system->root[i].attributes & MARK) == MARK) {
						printf("����: %s (����� ����)\n", system->root[i].nameOfFile);
					}
					else {
						if ((system->root[i].attributes & SUBDIRECTORY) == SUBDIRECTORY) {
							printf("����������: %s\n", system->root[i].nameOfFile);
						}
						else {
							if ((system->root[i].attributes & ARCHIVE) == ARCHIVE) {
								printf("����: %s (��������)\n", system->root[i].nameOfFile);
							}
						}
					}
				}
			}
		}
	}
}