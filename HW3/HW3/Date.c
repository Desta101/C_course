#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		puts("Enter Flight Date dd/mm/yyyy\t");
		myGets(date, MAX_STR_LEN);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ((date[2] != '/') || (date[5] != '/'))
		return 0;
	sscanf(date, "%d/%d/%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}

char* castingDateToChars(const Date* pDate) {
	char day[3];
	char month[3];
	char year[5];
	char* date = (char*)malloc(10 * sizeof(char));
	if (!date)
		return NULL;

	_itoa(pDate->day, day, 10);
	strcpy(date, day);
	strcat(date, "/");
	_itoa(pDate->month, month, 10);
	strcat(date, month);
	strcat(date, "/");
	_itoa(pDate->year, year, 10);
	strcat(date, year);

	return date;
}

void printDateChars(const void* date) {
	printf("Date: %s\n", (char*)date);
}
