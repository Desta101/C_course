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
#include "Company.h"
#include "AirportManager.h"
#include "General.h"
#include "main.h"
#include "myMacros.h"

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
"PrintCompany", "Print all Airports",
	"Print flights between origin-destination",
"Sort Flights", "Search Flight" };


int main(int  argc, char*  argv[])
{
	if (argc != 3)
		return 0;
	char airportFile[MAX_STR_LEN];
	char companyFile[MAX_STR_LEN];
	sscanf(argv[1], "%s", airportFile);
	sscanf(argv[2], "%s", companyFile);

	AirportManager	manager;
	Company			company;

	initManagerAndCompany(&manager, &company, airportFile, companyFile);
	
	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company,"Hachi","Babit","Ba","Olam",NULL);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;
		
		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;
		
		case eSortFlights:
			sortFlight(&company);
			break;

		case eSearchFlight:
			findFlight(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);


	saveManagerToFile(&manager, airportFile);
	saveCompanyToFile(&company, companyFile);
	freeManager(&manager);
	freeCompany(&company);

	system("pause");
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int initManagerAndCompany(AirportManager* pManager ,Company* pCompany, char* textFileName, char* testBinName)
{
	int res = initManager(pManager, textFileName);
	CHECK_MSG_RETURN_0(res,"Error init manager");

	if (res == FROM_FILE)
		return initCompanyFromFile(pCompany,pManager, testBinName);
	else
		initCompany(pCompany, pManager);
	return 1;
}