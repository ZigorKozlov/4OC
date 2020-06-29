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
//ƒвубайтовый формат даты:
//биты 0Ц4 Ч день мес€ца, допускаютс€ значени€ 1Ц31;
//биты 5Ц8 Ч мес€ц года, допускаютс€ значени€ 1Ц12;
//биты 9Ц15 Ч год, счита€ от 1980 года (Ђэпоха MS-DOSї), возможны значени€ от 0 до 127 включительно, то есть 1980Ц2107 годы.

//ƒвубайтовый формат времени:
//биты 0Ц4 Ч счЄтчик секунд (по две), допустимы значени€ 0Ц29, то есть 0Ц58 секунд;
//биты 5Ц10 Ч минуты, допустимы значени€ 0Ц59;
//биты 11Ц15 Ч часы, допустимы значени€ 0Ц23.

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
			//»звлечение даты и времени
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
				 printf("ќшибка - некорректно указана дата создани€\n");
				 return;
			 }*/

			printf("Ќазвание файла: %s\nƒата создани€: %u.%u.%u\n¬рем€ создани€: %u:%u:%u\nЌомер первого блока: %d\nјтрибуты: %c\n–азмер: %u\n",
				system->root[i].nameOfFile, date.day, date.mounth, MINIMAL_YEAR_ALLOWED + date.year, time.hours, time.minutes, time.seconds * 2, fileId, system->root[i].attributes, system->root[i].size);
			return;
		}
	}
	printf("‘айл с указаным ID не найден\n");
}