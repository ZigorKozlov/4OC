#include "Task4Lab.h"

void task4OC(FileSystem* Fsystem)
{
	system("cls");

	int countArray[2000][2];//0 - countBlock 1 - countFiles
	for (int i = 0; i < 2000; i++) {
		countArray[i][0] = -1;
		countArray[i][1] = 0;
	}

	int countF = 0;
	const int sizeRoot = Fsystem->superblock.rootSize;
	const File* rootPtr = Fsystem->root;
	
	for (int i = 0; i < sizeRoot; i++) {

		//Приходится ставить костыли, т.к. представление Fat нужно было в виде одномерного массива, где номер в таблице - номер индекса массива 
		int countBlock = 0;
		unsigned int nBlock = rootPtr[i].numberOfFirstFileBlock;

		while (1) {		

			if (nBlock == 255)
				break;

			countBlock++;

			nBlock = Fsystem->FAT[nBlock][1];//Номер блока

		}

		
		int flag = -1;
		for (int j = 0; j < countF; j++) {

			if (countArray[j][0] == countBlock) {
				countArray[j][1]++;
				flag = 0;
				break;
			}

		}

		if (flag == -1) {
			countArray[countF][0] = countBlock;
			countArray[countF][1]++;
			countF++;
		}

	}

	//ВЫвод итогов

	for (int i = 0; i < countF; i++) {
		
		float dat = 100 * (((float)countArray[i][1]) / sizeRoot);
	
		printf("%d-блоковых файлов %f процентов.\n", countArray[i][0], dat);
	}
	system("pause");
	system("cls");

}
