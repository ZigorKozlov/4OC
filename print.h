#pragma once
#include "FileSystem.h"

#define EOC 0xFF
#define BROKEN 0x0FE

void printFAT(FileSystem* system); //Displays a content of FAT
void printSuperblockInfo(FileSystem* system); //Displays an information from supeblock
void printRootInfo(FileSystem* system); //Displays a content of Root
void printTextFile(FileSystem* system, int numberOfFirstFileBlock); //Display selected .txt file
void printFilesList(FileSystem* system);
void printFileInfo(FileSystem* system, int fileId);
void printFileTree(FileSystem* system);
void printCatalog(File dir, FileSystem* system, File* directories, File* files, int *countFiles, int *countDirectories);
int* getNum();