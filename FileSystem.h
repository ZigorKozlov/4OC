//
//  Header.h
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once
#include "Superblock.h"
#include "File.h"

typedef struct FileSystem {
	Superblock superblock;
	int **FAT; // numOfRows = sizeOfFAT / 8
	File *root;
	char **data; //sizeOfBlock x 512 (FAT12,FAT16)
}
FileSystem;