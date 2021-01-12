#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

const char* sort[eNoSort] = { "Sort by hour", "Sort by date",
								"Sort by origin code", "Sort by dest code" };

/* The function init the company */
void initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->dates = initLinkedList();
	pComp->sortOption = eNoSort;
}

/* The function add flight to the company */
int	addFlight(Company* pComp, const AirportManager* pManager)
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
	insert(&(pComp->dates), castingDateToChars(&(pComp->flightArr[pComp->flightCount]->date)), NULL);
	pComp->flightCount++;
	return 1;
}

/* The function print all the deatils of the company */
void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);

	printf("\nFlights Date List:\n");
	printLinkedList(pComp->dates, printDateChars);
}

/* The function print the number of the flights between 2 airports */
void printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0) {
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

/* The function print the flights arr by general function */
void printFlightArr(Flight** pFlight, int size) {
	generalArrayFunction(pFlight, size, sizeof(Flight*), printPtrFlight);
}

/* The function print the flight by the pointer */
void printPtrFlight(const Flight** flight) {
	printFlight(*flight);
}

/* The function free the flights arr by general function */
void freeFlightArr(Flight** arr, int size) {
	generalArrayFunction(arr, size, sizeof(Flight*), freePtrFlight);
}

/* The function free the flight by the pointer */
void freePtrFlight(Flight** flight) {
	freeFlight(*flight);
}

/* The function free all the memory of the company */
void freeCompany(Company* pComp) {
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	freeAllLinkedList(pComp->dates, free);
	free(pComp->name);
}

/* The function allow to sort the flights arr by 4 options */
void sortFlightsArr(Company* pComp) {
	int sortOption = 0;
	void* compareFunc = NULL;

	printf("Please, choose one of the following sort options: \n");
	for (int i = 0; i < eNoSort; i++)
		printf("%d - %s\n", i, sort[i]);
	scanf("%d", &sortOption);

	switch (sortOption) {
	case eHourSort:
		compareFunc = compareByHour;
		break;
	case eDateSort:
		compareFunc = compareByDate;
		break;
	case eOriginCodeSort:
		compareFunc = compareByOriginCode;
		break;
	case eDestCodeSort:
		compareFunc = compareByDestCode;
		break;
	default:
		printf("Wrong option\n");
		return;
	}

	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFunc);
	pComp->sortOption = sortOption;
}

/* The function allow to search flight by 4 options */
void searchFlight(Company* pComp) {
	void* compareFunc;
	Flight* flight = (Flight*)malloc(sizeof(Flight));
	if (!flight)
		return;

	switch (pComp->sortOption) {
		case eHourSort: {
			flight->hour = getFlightHour();
			compareFunc = compareByHour;
			break;
		}
		case eDateSort: {
			getCorrectDate(&(flight->date));
			compareFunc = compareByDate;
			break;
		}
		case eOriginCodeSort: {
			getAirportCode(flight->originCode);
			compareFunc = compareByOriginCode;
			break;
		}
		case eDestCodeSort: {
			getAirportCode(flight->destCode);
			compareFunc = compareByDestCode;
			break;
		}
		case eNoSort: {
			printf("The search cannot be performed, array not sorted\n");
			return;
		}
		default: {
			printf("Wrong option\n");
			return;
		}
	}

	flight = bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFunc);
	if (flight)
		printFlight(*(Flight**)flight);
	else
		printf("Flight not found");
}

/* The function compare between 2 flights by they hour */
int compareByHour(const void* element1, const void* element2) {
	const Flight* flight1 = *(const Flight**)element1;
	const Flight* flight2 = *(const Flight**)element2;
	return flight1->hour - flight2->hour;
}

/* The function compare between 2 flights by they date */
int compareByDate(const void* element1, const void* element2) {
	const Flight* flight1 = *(const Flight**)element1;
	const Flight* flight2 = *(const Flight**)element2;
	Date date1 = flight1->date;
	Date date2 = flight2->date;

	if (date1.year < date2.year)
		return -1;
	else if (date1.year > date2.year)
		return 1;
	else {
		if (date1.month < date2.month)
			return -1;
		else if (date1.month > date2.month)
			return 1;
		else if (date1.day < date2.day)
			return -1;
		else if (date1.day > date2.day)
			return 1;
		else
			return 0;
	}
}

/* The function compare between 2 flights by they origin code */
int compareByOriginCode(const void* element1, const void* element2) {
	const Flight* flight1 = *(const Flight**)element1;
	const Flight* flight2 = *(const Flight**)element2;
	return strcmp(flight1->originCode, flight2->originCode);
}

/* The function compare between 2 flights by they dest code */
int compareByDestCode(const void* element1, const void* element2) {
	const Flight* flight1 = *(const Flight**)element1;
	const Flight* flight2 = *(const Flight**)element2;
	return strcmp(flight1->destCode, flight2->destCode);
}

/* The function save all the company deatils in binary file */
void saveToBinaryFile(Company* pComp) {
	int i, nameLength;
	FILE* f = fopen("company.bin", "wb");
	if (!f)
		return;

	nameLength = (int)strlen(pComp->name) + 1;
	fwrite(&nameLength, sizeof(int), 1, f);
	fwrite(pComp->name, sizeof(char), nameLength, f);
	fwrite(&(pComp->flightCount), sizeof(int), 1, f);
	fwrite(&(pComp->sortOption), sizeof(int), 1, f);

	for (i = 0; i < pComp->flightCount; i++)
		fwrite(pComp->flightArr[i], sizeof(Flight), 1, f);

	fclose(f);
}

/* The function read all the company deatils from binary file */
int	readFromBinaryFile(Company* pComp) {
	int i, nameLength;
	FILE* f = fopen("company.bin", "rb");
	if (!f)
		return 0;

	fread(&nameLength, sizeof(int), 1, f);
	if (!nameLength || nameLength <= 0)
		return 0;

	pComp->name = (char*)malloc(nameLength * sizeof(char));
	if (!pComp->name)
		return 0;

	pComp->dates = initLinkedList();

	fread(pComp->name, sizeof(char), nameLength, f);
	fread(&(pComp->flightCount), sizeof(int), 1, f);
	fread(&(pComp->sortOption), sizeof(int), 1, f);

	pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;

	for (i = 0; i < pComp->flightCount; i++) {
		pComp->flightArr[i] = (Flight*)malloc(sizeof(Flight));
		if (!pComp->flightArr[i])
			return 0;

		fread(pComp->flightArr[i], sizeof(Flight), 1, f);
		insert(&pComp->dates, castingDateToChars(&(pComp->flightArr[i]->date)), NULL);
	}

	fclose(f);
	return 1;
}