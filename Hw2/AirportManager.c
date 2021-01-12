/*
 * AirportManager.c
 *
 *  Created on: May 3, 2020
 *      Author: afeka
 */
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include "Airport.h"
#include "general.h"
#include "AirportManager.h"

int initAirportManager(AirportManager *am) {

	am->sumofAp = 1;
	am->aps=(Airport*)malloc(sizeof(Airport*)*am->sumofAp);
	if(!am->aps)
		return 0;
	return 1;

}
int addAirports(AirportManager *airportMan) {


	Airport air;
	initAirport(&air);

	airportMan->aps = realloc(airportMan->aps, airportMan->sumofAp + 1);
	//chack allocation
	if (!initAirport(&air))
		return 0;
	airportMan->aps[airportMan->sumofAp] = air;
	airportMan->sumofAp++;
	return 1;

}
Airport* findAirport(char iata[], const AirportManager *airportMan) {


	int size = airportMan->sumofAp;
	for (int i = 0; i < size; ++i) {
		if(isCodeBelong(&(airportMan->aps[i]),iata)==0)
			return airportMan->aps[i];


	}
	return NULL;
}
void printAirportManager(const AirportManager* airportMan){

	printf("those are the airports:\n");
	for (int var = 0; var < airportMan->sumofAp; ++var) {
		printAirport(&(airportMan->aps[var]));
	}

}

void freeAirportManager(const AirportManager* airportMan){
	for (int var = 0; var < airportMan->sumofAp; ++var) {
			freeAirport(&(airportMan->aps[var]));

		}

}


