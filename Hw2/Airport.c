/*
 * Airport.c
 *
 *  Created on: May 3, 2020
 *      Author: bar & hen
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Airport.h"
#include "general.h"
#define PI 3.141592


int initAirport(Airport *ap) {
	printf("please enter name, state , iata code, lat and lon");
	char *name = getStrExactLength();
	putchar(toupper(name[0]));
	char *state = getStrExactLength();

	char* iata = initAirportCode();
	float lat, lon;
	initLatLon(&lat, &lon);
	ap->name = name;
	ap->state = state;
    *(ap->IATA) = *iata;
	ap->lat = lat;
	ap->lon = lon;
	if(!ap->name||!ap->state)
		return 0;
	return 1;
}
char* initAirportCode() {

	int i = 0;
	int flag = 1;
	char* code;
	while (i == 0) {
		printf("Enter a code:");
		scanf("%s", &code);

		if (strlen(code) != 3) {
			printf("the code is invaild");
			continue;
		}

		for (int j = 0; j < strlen(code); ++j) {
			if (!(code[i] >= 'A' && code[i] <= 'Z')) {
				flag = 0;
				break;
			}
		}
		if (flag == 0) {
			printf("the code is invaild");
			continue;
		} else
			i = 1;
	}
	return code;


}

float distance(Airport *ap1, Airport *ap2) {
	if(ap1->lon==ap2->lon && ap1->lat==ap2->lat)
		return 0;

	const int R = 3950;
	float q1=ap1->lat*PI/180;
	float q2=ap2->lat*PI/180;
	float dlat=(ap2->lat-ap1->lat)*PI / 180;
	float dlon=(ap2->lon-ap1->lon)*PI/180;
	float a=(sin(dlat/2)*sin(dlat/2)+cos(q1)*cos(q2)*sin(dlon/2)*sin(dlon/2));
	const float c = 2 * atan2(sqrt(a), sqrt(1 - a));


	const float d = R * c; // in metres

	return d;
}
int isCodeEq(Airport *ap1, Airport *ap2) {

	if (strcmp(ap1->IATA, ap2->IATA) == 0)
		return 1;
	else
		return 0;
}

int isCodeBelong(Airport *ap, char iata[]) {
	if (strcmp(ap->IATA, iata)==0)
		return 1;
	else
		return 0;

}




void initLatLon(float *lat, float *lon) {
	int i = 0;
	int j = 0;
	while (i == 0) {
		printf("Enter the latitude:");
		scanf("%f", lat);
		if (*lat > 180 || *lat < -180) {
			printf("the latitude is invalid");
			continue;
		} else
			i = 1;
	}
	while (j == 0) {
		printf("Enter the Longitude:");
		scanf("%f", lon);
		if (*lon > 180 || *lon < -180) {
			printf("the Longitude is invalid");
			continue;
		} else
			j = 1;
	}
}
void freeAirport(Airport *ap) {

	free(ap->state);
	free(ap->name);
}
void printAirport(const Airport* ap) {

	printf(
			"airport name %s, state: %s, code %s, latitude and Longitude %.2f %.2f",
			ap->name, ap->state, ap->IATA, ap->lon, ap->lat);
}



