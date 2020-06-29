//
//  Superblock.h
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once

typedef struct Superblock {
	unsigned sizeOFBlock;
	unsigned FATsize;
	unsigned rootSize;
	unsigned cypherShift;
} Superblock;