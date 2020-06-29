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

			printf("Файл: %s (только для чтения)\n", system->root[i].nameOfFile);
		}
		else {
			if ((system->root[i].attributes & HIDDEN) == HIDDEN) {
				//Не отображать скрытые файлы
				continue;
			}
			else {
				if ((system->root[i].attributes & SYSTEM) == SYSTEM) {
					printf("Файл: %s (системный)\n", system->root[i].nameOfFile);
				}
				else {
					if ((system->root[i].attributes & MARK) == MARK) {
						printf("Файл: %s (метка тома)\n", system->root[i].nameOfFile);
					}
					else {
						if ((system->root[i].attributes & SUBDIRECTORY) == SUBDIRECTORY) {
							printf("Подкаталог: %s\n", system->root[i].nameOfFile);
						}
						else {
							if ((system->root[i].attributes & ARCHIVE) == ARCHIVE) {
								printf("Файл: %s (архивный)\n", system->root[i].nameOfFile);
							}
						}
					}
				}
			}
		}
	}
}