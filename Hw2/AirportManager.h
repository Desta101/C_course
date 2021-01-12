/*
 * AirportManager.h
 *
 *  Created on: May 3, 2020
 *      Author: afeka
 */

#ifndef AIRPORTMANAGER_H_
#define AIRPORTMANAGER_H_
#include "Airport.h"

typedef struct
{

	int sumofAp;
	Airport* aps ;

} AirportManager;
int initAirportManager(AirportManager* am);
int addAirports(AirportManager* airportMan);
Airport* findAirport(char iata[], const AirportManager* airportMan );
void printAirportManager(const AirportManager* airportMan);
void freeAirportManager(const AirportManager* airportMan);
#endif /* AIRPORTMANAGER_H_ */
