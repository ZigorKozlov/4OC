#include "print.h"
#include <stdlib.h>
#include <stdio.h>
#define SUBDIRECTORY 0x2
#define _true 1

int *num;

int* getNum() {
	return num;
}
int haveSubdir(File dir, FileSystem* system, File* directories, int countDirectories) {
	int numberInFAT = 0;
	for (int i = 0; i < system->superblock.FATsize / 8; i++) {
		if (system->FAT[i][0] == dir.numberOfFirstFileBlock) {
			numberInFAT = i;
			break;
		}
	}
	int i = numberInFAT;
	while (system->FAT[i][1] != EOC) {
		for (int j = 0; j < countDirectories; ++j) {
			if (directories[j].numberOfFirstFileBlock == system->FAT[i][0]) {
				return 1;
			}
		}
		i++;
	}
	return 0;
}

void printCatalog(File dir, FileSystem* system, File* directories, File* files, int *countFiles, int *countDirectories) {
	if (num == NULL) {
		num = (int*)malloc(*countFiles * 4);
	}
	for (int i = 0; i < *countFiles; ++i)
		num[i] = files[i].numberOfFirstFileBlock;
	int numberInFAT = 0;
	for (int i = 0; i < system->superblock.FATsize / 8; i++) {
		if (system->FAT[i][0] == dir.numberOfFirstFileBlock) {
			numberInFAT = i;
			break;
		}
	}
	for (int i = numberInFAT; i < system->superblock.FATsize / 8; ++i) {
		for (int j = 0; j < *countFiles; ++j) {
			if (files[j].numberOfFirstFileBlock == system->FAT[i][0]) {
				printf("Файл: %s\tРасположение: %s\n", files[j].nameOfFile, dir.nameOfFile);
				num[j] = -1;
			}
			if (system->FAT[i][1] == EOC) {
				return;
			}
		}
		for (int j = 0; j < *countDirectories; ++j) {
			if (directories[j].numberOfFirstFileBlock == system->FAT[i][0] && directories[j].numberOfFirstFileBlock != dir.numberOfFirstFileBlock) {
				printCatalog(directories[j], system, directories, files, countFiles, countDirectories);
			}
			if (system->FAT[i][1] == EOC) {
				return;
			}
		}
	}
}

void printFileTree(FileSystem* system) {
	File *files, *directories;
	int countFiles, countDirectories;
	files = directories = NULL;
	countFiles = countDirectories = 0;
	int iFiles, iDir;
	iFiles = iDir = 0;
	for (int i = 0; i < system->superblock.rootSize; ++i) {
		if (system->root[i].attributes == SUBDIRECTORY)
			countDirectories++;
		else
			countFiles++;
	}
	files = (File*)malloc(countFiles * sizeof(File));
	directories = (File*)malloc(countDirectories * sizeof(File));
	for (int i = 0; i < system->superblock.rootSize; ++i) {
		if ((system->root[i].attributes & SUBDIRECTORY) == SUBDIRECTORY) {
			directories[iDir] = system->root[i];
			iDir++;
		}
		else {
			files[iFiles] = system->root[i];
			iFiles++;
		}
	}
	if (countDirectories == 0) {
		for (int i = 0; i < countFiles; ++i) {
			if (files[i].nameOfFile[strlen(files[i].nameOfFile) - 1] == '\n')
				files[i].nameOfFile[strlen(files[i].nameOfFile) - 1] = '\0';
			printf("Имя файла: %s\tРасположение Root\n", files[i].nameOfFile);
		}
	}
	else {
		for (int i = 0; i < countDirectories; ++i) {
			printf("Подкаталог: %s\n", directories[i].nameOfFile);
		}
		for (int i = 0; i < countDirectories; ++i) {
			printCatalog(directories[i], system, directories, files, &countFiles, &countDirectories);
		}
		for (int i = 0; i < countFiles; ++i) {
			if (num[i] != -1) {
				for (int k = 0; k < countFiles; k++) {
					if (files[k].numberOfFirstFileBlock == num[i]) {
						printf("Файл: %s\t Расположение Root\n", files[k].nameOfFile);
					}
				}
			}
		}
	}
}