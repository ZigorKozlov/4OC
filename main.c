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
	printf("�������� � ���������� ��������� ��������:\n");
	printRootInfo(system);
	//
	printf("\n\n\n");
	for (int i = 0; i < system->superblock.FATsize / 8; i++) {
		printf("%d    %d\n", system->FAT[i][0], system->FAT[i][1]);
	}
	//
	int flag = _true;
	while (flag == _true) {
		printf("1 - ������� �� ����� ������� ���������� ������ (FAT)\n2 - ������� ���������� ��������� ������ �� �����\n3 - ������� �� ����� ���������� � ���������� �����/�����\n4 - ������� �� ����� ������ �������� ������\n5 - �������(4 ����)\n6 - ����� �� ���������\n");
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
					printf("ID �����: %d �������� �����: %s\n", i, system->root[i].nameOfFile);
			}
			printf("����������, ������� ID �����\n");
			scanf("%d", &file_id);
			printTextFile(system, system->root[file_id].numberOfFirstFileBlock);
			getchar();
			break;
		}
		case '3': {
			int file_id = 0;
			for (int i = 0; i < system->superblock.rootSize; ++i) {
				printf("ID �����: %d �������� �����: %s\n", system->root[i].numberOfFirstFileBlock, system->root[i].nameOfFile);
			}
			printf("����������, ������� ID �����\n");
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