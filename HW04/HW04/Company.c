/*
============================================================================
Name        : HW04.c
	Author : Shimon desta 203670286 and Tal saar 209151380
	Copyright : Your copyright notice
	Description : Airport Manager in C
============================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdarg.h>
#include "myMacros.h"
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "fileHelper.h"

static const char* sortOptStr[eNofSortOpt] = {
	"None","Hour", "Date", "Airport takeoff code", "Airport landing code" };


int	initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName)
{
#ifdef DETAIL_PRINT
	FILE* fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp, "error loading");
	BYTE data[10];
	fread(data, sizeof(char), 2, fp);
	pComp->flightCount = (data[1] << 1 ) | (data[0] >> 7);
	pComp->sortOpt = data[0] >> 4 & 0x7;
	int size = data[0] & 0xF;
	pComp->name = (char*)malloc((size + 1) * sizeof(char));
	CHECK_RETURN_0(pComp->name);
	fread(pComp->name, sizeof(char), size + 1, fp);
	pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
	for (int i = 0; i < pComp->flightCount; i++)
	{
		addinfo(pComp,pManaer,i,fp,&data);
	}
	L_init(&pComp->flighDateList);
	initDateList(pComp);
	return 1;

#else
	L_init(&pComp->flighDateList);
	if (loadCompanyFromFile(pComp, pManaer, fileName))
	{
		initDateList(pComp);
		return 1;
	}
	return 0;
#endif 

}
void addinfo(Company* pComp, AirportManager* pManaer, int i, FILE *fp,BYTE *data) {
	fread(data, sizeof(char), 10, fp);
	char code[CODE_LENGTH + 1];
	pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
	CHECK_NULL__MSG_COLSE_FILE(pComp->flightArr[i], "Alocation error", fp);
	code[0] = data[0];
	code[1] = data[1];
	code[2] = data[2];
	code[3] = '\0';
	Airport* AirportCode = findAirportByCode(pManaer, code);
	CHECK_RETURN_0(AirportCode);
	strcpy(pComp->flightArr[i]->originCode, code);
	code[0] = data[3];
	code[1] = data[4];
	code[2] = data[5];
	code[3] = '\0';
	AirportCode = findAirportByCode(pManaer, code);
	CHECK_RETURN_0(AirportCode);
	strcpy(pComp->flightArr[i]->destCode, code);
	pComp->flightArr[i]->date.year = (data[9] << 10) | (data[8] << 2) | (data[7] >> 6); 
	pComp->flightArr[i]->date.month = data[7] >> 2 & 0xF;
	pComp->flightArr[i]->date.day = ((data[7] & 0x3) << 3) | (data[6] >> 5);
	pComp->flightArr[i]->hour = data[6] & 0x1F;

}


void	initCompany(Company* pComp,AirportManager* pManaer)
{
	printf("-----------  Init Airline Company  -------------\n");
	L_init(&pComp->flighDateList);
	pComp->name = getStrExactName("Enter company name: ");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
}

void	initDateList(Company* pComp)
{	
	int count = 0;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		for (int j = 0; j < i; j++) {
			if (compareDate(&pComp->flightArr[i]->date, &pComp->flightArr[j]->date) != 0)
				count++;
		}
		if (count == i) {
			char* sDate = createDateString(&pComp->flightArr[i]->date);
			L_insert(&(pComp->flighDateList.head), sDate);
		}
		count = 0;
	}
}

int		isUniqueDate(const Company* pComp, int index)
{
	Date* pCheck = &pComp->flightArr[index]->date;
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (i == index)
			continue;
		if (equalDate(&pComp->flightArr[i]->date,pCheck))
			return 0;
	}
	return 1;
}

int		addFlight(Company* pComp, const AirportManager* pManager)
{

	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	if (isUniqueDate(pComp, pComp->flightCount))
	{
		char* sDate = createDateString(&pComp->flightArr[pComp->flightCount]->date);
		L_insert(&(pComp->flighDateList.head), sDate);
	}
	pComp->flightCount++;
	return 1;
}

void printCompany(const Company* pComp,char* word,...){

	va_list allWords;
	char* currentWord;
	va_start(allWords, word);
	currentWord = word;
	printf("%s", pComp->name);
	while (currentWord != NULL) {
		printf("_%s", currentWord);
		currentWord = va_arg(allWords, char*);
	}
	va_end(allWords);
	printf("\n");
	printf("Has %d flights\n", pComp->flightCount);

#ifdef DETAIL_PRINT
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), printFlightV);
	printf("\nFlight Date List:");
	L_print(&pComp->flighDateList, printStr);
	
#endif
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}

int		saveCompanyToFile(const Company* pComp, const char* fileName)
{
#ifdef DETAIL_PRINT
	FILE* fp;
	fp = fopen(fileName, "wb");
	CHECK_RETURN_0(fp);
	int sizeName = strlen(pComp->name);
	int size = 2 + strlen(pComp->name);
	BYTE* data = (BYTE*)calloc(sizeof(BYTE), size + 1);
	data[1] = (pComp->flightCount >> 1);
	data[0] = (pComp->flightCount << 7) | (pComp->sortOpt << 4) | sizeName;
	for (int i = 2; i < size; i++)
		data[i] = pComp->name[i - 2];
	data[size] = '\0';
	fwrite(data, sizeof(char), size + 1, fp);
	data = (char*)realloc(data, sizeof(char) * 10);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		for (int j = 0; j < CODE_LENGTH; j++)
		{
			data[j] = pComp->flightArr[i]->originCode[j];
			data[j + 3] = pComp->flightArr[i]->destCode[j];
		}
		data[9] = pComp->flightArr[i]->date.year >> 10;
		data[8] = (pComp->flightArr[i]->date.year >> 2) & 0xFF;
		data[7] = (pComp->flightArr[i]->date.year & 0x3) << 6 | (pComp->flightArr[i]->date.month << 2) | (pComp->flightArr[i]->date.day >> 3);
		data[6] = (pComp->flightArr[i]->date.day << 5) | (pComp->flightArr[i]->hour);
		fwrite(data, sizeof(char), 10, fp);
	}
	free(data);
	fclose(fp);
	return 1;
#else
	FILE* fp;
	fp = fopen(fileName, "wb");
	CHECK_NULL__MSG_COLSE_FILE(fp, fp, "Error open company file to write");
	CHECK_0_MSG_CLOSE_FILE(writeStringToFile(pComp->name, fp, "Error write company name"),"Error write company name",fp);
	CHECK_0_MSG_CLOSE_FILE(writeIntToFile(pComp->flightCount, fp, "Error write flight count"),"Error write flight count",fp);
	CHECK_0_MSG_CLOSE_FILE(writeIntToFile((int)pComp->sortOpt, fp, "Error write sort option"),"Error write sort option",fp);

	for (int i = 0; i < pComp->flightCount; i++)
		CHECK_RETURN_0(saveFlightToFile(pComp->flightArr[i], fp));

	fclose(fp);
	return 1;
#endif
}

int loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp,"Error open company file");
	pComp->flightArr = NULL;
	pComp->name = readStringFromFile(fp, "Error reading company name");
	CHECK_RETURN_0(pComp->name);
	CHECK_0_MSG_COLSE_FILE(readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name"),"Error reading flight count name",fp);
	int opt;
	CHECK_MSG_RETURN_0(readIntFromFile(&opt, fp, "Error reading sort option\n"), "Error reading sort option");
	pComp->sortOpt = (eSortOption)opt;

	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
		CHECK_NULL__MSG_COLSE_FILE(pComp->flightArr,  "Allocation error", fp);
	}
	else
		pComp->flightArr = NULL;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		CHECK_NULL__MSG_COLSE_FILE(pComp->flightArr[i], "Allocation error", fp);
		CHECK_RETURN_0(loadFlightFromFile(pComp->flightArr[i], pManager, fp));	
	}
	fclose(fp);
	return 1;
}

void	sortFlight(Company* pComp)
{
	pComp->sortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pComp->sortOpt)
	{
	case eHour:
		compare = compareByHour;
		break;
	case eDate:
		compare = compareByDate;
		break;
	case eSorceCode:
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		compare = compareByCodeDest;
		break;
	
	}

	if (compare != NULL)
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);

}

void	findFlight(const Company* pComp)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Flight f = { 0 };
	Flight* pFlight = &f;


	switch (pComp->sortOpt)
	{
	case eHour:
		f.hour = getFlightHour();
		compare = compareByHour;
		break;
	case eDate:
		getchar();
		getCorrectDate(&f.date);
		compare = compareByDate;
		break;
	case eSorceCode:
		getchar();
		getAirportCode(f.originCode);
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		getchar();
		getAirportCode(f.destCode);
		compare = compareByCodeDest;
		break;
	}

	if (compare != NULL)
	{
		Flight** pF = bsearch(&pFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);
		if (pF == NULL)
			printf("Flight was not found\n");
		else {
			printf("Flight found, ");
			printFlight(*pF);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}

}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >eNofSortOpt);

	return (eSortOption)opt;
}

void	freeCompany(Company* pComp)
{
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->flighDateList, freePtr);
}
