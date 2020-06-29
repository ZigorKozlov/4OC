#include "print.h"
#include <stdio.h>

void printFAT(FileSystem* system) {
	for (int i = 0; i < system->superblock.FATsize / 8; ++i) {
		printf("����� �����: %d ", system->FAT[i][0]);
		if (system->FAT[i][1] == 0) {
			printf("���������: ���� ��������\n");
		}
		else {
			if (system->FAT[i][1] != EOC && system->FAT[i][1] != BROKEN) {
				printf("���������: ���� ����� ������ � �� �������� ��������� ������ �����\n");
			}
			else {
				if (system->FAT[i][1] == EOC) {
					printf("���������: ���� �������� ��������� ������ �����\n");
				}
				else {
					if (system->FAT[i][1] == BROKEN) {
						printf("���������: ���� ��������� \n");
					}
					else {
						printf("������������ �������� ��������� �����\n");
						return;
					}
				}
			}
		}
	}
}