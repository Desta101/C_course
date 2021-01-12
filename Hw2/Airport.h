/*
 * Airport.h
 *
 *  Created on: May 3, 2020
 *      Author: afeka
 */




#ifndef AIRPORT_H_
#define AIRPORT_H_

#define CODE_LENGTH 3

typedef struct {
	char* name;
	char* state;
	char IATA[CODE_LENGTH+1];
	float lat;
	float lon;

	}Airport;

	int initAirport(Airport* ap);
	void printAirport(const Airport* ap);
	int isCodeEq(Airport* ap1, Airport* ap2);
	int isCodeBelong(Airport* ap, char iata[]);
	float distance(Airport* ap1, Airport* ap2);
	char* initAirportCode();
	//int checkIataCode(const char* code);

	void freeAirport(Airport* ap);

	void initLatLon(float* lat, float* lon);
#endif /* AIRPORT_H_ */
