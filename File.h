//
//  File.h
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//
#pragma once

typedef struct File {
	char nameOfFile[12];
	unsigned numberOfFirstFileBlock;
	char attributes;
	int dateTime;
	unsigned size;
} File;