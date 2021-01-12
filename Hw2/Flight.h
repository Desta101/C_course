/*
 * Flight.h
 *
 *  Created on: May 6, 2020
 *      Author: afeka
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_
#define dateLen 10
typedef struct {

	Airport* apStart;
	Airport* apDes;
	int hourExit;
	char date[dateLen+1];
	float AvgSpeed;

	}Flight;
float flightTime (Flight* fl);
int isFligthOk(Flight* fl,char* codeStart, char* codeDes);
int countFlights(Flight** fl,char* codeStart, char* codeDes);
void initFlight(Flight* fl);
void printFlight(const Flight* fl);
void FreeFlight(Flight* fl);
int Hour(int x,int y);
char* CheckDate();
int checkDateStrck(char  date[]);
#endif /* FLIGHT_H_ */
