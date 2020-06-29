#include "print.h"
#include <stdio.h>

#define GET_LEFT_BYTE 0xFFFF0000
#define GET_RIGHT_BYTE 0x0000FFFF
#define GET_DAY 0xF000
#define GET_MOUNTH 0x780
#define GET_YEAR 0x7F
#define GET_SECS 0x1F
#define GET_MINS 0x7E0
#define GET_HOURS 0xF800
#define MINIMAL_YEAR_ALLOWED 1980
//����������� ������ ����:
//���� 0�4 � ���� ������, ����������� �������� 1�31;
//���� 5�8 � ����� ����, ����������� �������� 1�12;
//���� 9�15 � ���, ������ �� 1980 ���� (������ MS-DOS�), �������� �������� �� 0 �� 127 ������������, �� ���� 1980�2107 ����.

//����������� ������ �������:
//���� 0�4 � ������� ������ (�� ���), ��������� �������� 0�29, �� ���� 0�58 ������;
//���� 5�10 � ������, ��������� �������� 0�59;
//���� 11�15 � ����, ��������� �������� 0�23.

typedef struct Date {
	unsigned day : 5;
	unsigned mounth : 4;
	unsigned year : 7;
} Date;

typedef struct Time {
	unsigned seconds : 5;
	unsigned minutes : 6;
	unsigned hours : 5;
} Time;

void printFileInfo(FileSystem* system, int fileId) {
	int leftByte, rightByte;
	Date date;
	Time time;
	leftByte = rightByte = 0;
	for (int i = 0; i < system->superblock.rootSize; ++i) {
		if (system->root[i].numberOfFirstFileBlock == fileId) {
			//���������� ���� � �������
			leftByte = system->root[i].dateTime & GET_LEFT_BYTE;
			rightByte = system->root[i].dateTime & GET_RIGHT_BYTE;
			leftByte = leftByte >> 16;
			date.day = (leftByte & GET_DAY) >> 11;
			date.mounth = (leftByte & GET_MOUNTH) >> 7;
			date.year = (leftByte & GET_YEAR);
			time.seconds = rightByte & GET_SECS;
			time.minutes = (rightByte & GET_MINS) >> 5;
			time.hours = (rightByte & GET_HOURS) >> 11;

			/* if ((date.day < 1 || date.day > 31) || (date.mounth < 1 || date.mounth > 12) || (date.year < 0 || date.year > 127) ||
				 (time.seconds < 0 || time.seconds > 29) || (time.minutes < 0 || time.minutes > 59) || (time.hours < 0 || time.hours > 23)) {
				 printf("������ - ����������� ������� ���� ��������\n");
				 return;
			 }*/

			printf("�������� �����: %s\n���� ��������: %u.%u.%u\n����� ��������: %u:%u:%u\n����� ������� �����: %d\n��������: %c\n������: %u\n",
				system->root[i].nameOfFile, date.day, date.mounth, MINIMAL_YEAR_ALLOWED + date.year, time.hours, time.minutes, time.seconds * 2, fileId, system->root[i].attributes, system->root[i].size);
			return;
		}
	}
	printf("���� � �������� ID �� ������\n");
}