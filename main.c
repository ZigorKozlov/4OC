#include <stdio.h>
#include "readingFile.h"
#include "print.h"
#include "memoryDealloc.h"
#include "Task4Lab.h"
#include <stdlib.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS

#define DIR 0x2

#define _true 1
#define _false 0
int main(int argc, const char * argv[]) {

	setlocale(LC_ALL, "Russian");

	char func;

	FileSystem* system = readingFile();
	printSuperblockInfo(system);
	printf("Сведения о содержании корневого каталога:\n");
	printRootInfo(system);
	//
	printf("\n\n\n");
	for (int i = 0; i < system->superblock.FATsize / 8; i++) {
		printf("%d    %d\n", system->FAT[i][0], system->FAT[i][1]);
	}
	//
	int flag = _true;
	while (flag == _true) {
		printf("1 - вывести на экран таблицу размещения файлов (FAT)\n2 - вывести содержимое текстовых файлов на экран\n3 - вывести на экран информацию о конкретном файле/папке\n4 - вывести на экран полное файловое дерево\n5 - Задание(4 Лаба)\n6 - выход из программы\n");
		func = fgetc(stdin);
		switch (func) {
		case '1': {
			printFAT(system);
			getchar();
			break;
		}
		case '2': {
			int file_id = 0;
			for (int i = 0; i < system->superblock.rootSize; ++i) {
				if (system->root[i].attributes != DIR)
					printf("ID файла: %d Название файла: %s\n", i, system->root[i].nameOfFile);
			}
			printf("Пожалуйста, введите ID файла\n");
			scanf("%d", &file_id);
			printTextFile(system, system->root[file_id].numberOfFirstFileBlock);
			getchar();
			break;
		}
		case '3': {
			int file_id = 0;
			for (int i = 0; i < system->superblock.rootSize; ++i) {
				printf("ID файла: %d Название файла: %s\n", system->root[i].numberOfFirstFileBlock, system->root[i].nameOfFile);
			}
			printf("Пожалуйста, введите ID файла\n");
			scanf("%d", &file_id);
			printFileInfo(system, file_id);
			getchar();
			break;
		}
		case '4': {
			printFileTree(system);
			getchar();
			break;
		}
		case '5': {
			task4OC(system);
			
			break;
		}
		case '6': {
			flag = _false;
			break;
		}
		default:
			break;
		}
	}
	memory_dealloc(system);
	system = NULL;


	return 0;
}