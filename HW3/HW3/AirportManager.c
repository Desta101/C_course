#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AirportManager.h"

/* The function init AirportManager */
int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	pManager->airports = initLinkedList();

	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	for (int i = 0; i < count; i++)
		addAirport(pManager);

	return 1;
}

/* The function add airport to the AirportManager */
int	addAirport(AirportManager* pManager)
{
	Airport* airport = (Airport*)malloc(sizeof(Airport));
	if (!airport)
		return 0;

	setAirport(airport, pManager);
	insert(&pManager->airports, airport, compareByCode);
	pManager->count++;
	return 1;
}

/* The function set airport deatils in the AirportManager */
void setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

/* The function find airport be his code */
Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	Node* temp = pManager->airports;

	while (temp)
	{
		if (isAirportCode(temp->data, code))
			return temp->data;
		temp = temp->next;
	}

	return NULL;
}

/* The function check if the airport code is uniqe */
int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

/* The function compare between 2 airport by they code */
int compareByCode(const Airport* airport1, const Airport* airport2) {
	return strcmp(airport1->code, airport2->code);
}

/* The function print all the airports */
void printAirports(const AirportManager* pManager) {
	printf("there are %d airports\n", pManager->count);
	printLinkedList(pManager->airports, printAirport);
}

/* The function free all the airports */
void freeManager(AirportManager* pManager) {
	freeAllLinkedList(pManager->airports, freeAirport);
}

/* The function save all the AirportManager deatils in text file */
void saveToTextFile(AirportManager* pManager) {
	int i;
	Airport* airport;
	Node* temp = pManager->airports;

	FILE* f = fopen("airport_authority.txt", "w");
	if (!f)
		return;

	fprintf(f, "%d\n", pManager->count);

	for (i = 0; i < pManager->count; i++) {
		airport = (Airport*)(temp->next->data);
		fprintf(f, "%s\n", airport->name);
		fprintf(f, "%s\n", airport->country);
		fprintf(f, "%s\n", airport->code);
		temp = temp->next;
	}

	fclose(f);
}

/* The function read all the AirportManager deatils from text file */
int	readFromTextFile(AirportManager* pManager) {
	int i;
	char name[MAX_STR_LEN], country[MAX_STR_LEN];
	Airport* airport;
	FILE* f = fopen("airport_authority.txt", "r");
	if (!f)
		return 0;

	fscanf(f, "%d\n", &pManager->count);
	if (!pManager->count || pManager->count <= 0)
		return 0;

	pManager->airports = initLinkedList();

	for (i = 0; i < pManager->count; i++) {
		airport = (Airport*)malloc(sizeof(Airport));
		if (!airport)
			return 0;

		fgets(name, MAX_STR_LEN, f);
		fgets(country, MAX_STR_LEN, f);
		fscanf(f, "%s\n", airport->code);

		name[strlen(name) - 1] = '\0';
		airport->name = (char*)malloc(strlen(name) * sizeof(char));
		if (!airport->name)
			return 0;
		strcpy(airport->name, name);

		country[strlen(country) - 1] = '\0';
		airport->country = (char*)malloc(strlen(country) * sizeof(char));
		if (!airport->country)
			return 0;
		strcpy(airport->country, country);

		insert(&pManager->airports, airport, compareByCode);
	}

	fclose(f);
	return 1;
}