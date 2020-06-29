//
//  readingFile.h
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once
#include "FileSystem.h"
#include <stdio.h>

FileSystem* readingFile();
long int fileSize(FILE *fp);