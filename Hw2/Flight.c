y/*
 * Flight.c
 *
 *  Created on: May 6, 2020
 *      Author: afeka
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include "Airport.h"
#include "Flight.h"
#include "general.h"


float flightTime (Flight* fl)
{
	float time;
	time=(distance(fl->apStart,fl->apDes)/fl->AvgSpeed);
	float TimeInMin=time*60;
	float min=TimeInMin-(int)time*60;
	return time;
}




int isFligthOk(Flight* fl,char* codeStart, char* codeDes){
if(isCodeBelong(fl->apStart->IATA,codeStart)==1 &&
		isCodeBelong(fl->apDes->IATA,codeDes)==1)
		return 1;
		return 0;

}
int countFlights(Flight** fl,int countfights,char* codeStart, char* codeDes){

		int count=0;
		for (int var = 0; var <countfights; ++var) {
			if(isFligthOk(fl[var],codeStart,codeDes)==1)
				count++;
		}
		return count;


}
void initFlight(Flight* fl,Flight* start,Flight* end){
	fl->apStart=start;
	fl->apDes=end;
	fl->hourExit=Hour(0,23);
	fl->AvgSpeed=NumberPosistive();
	fl->date=CheckDate();


}
int Hour(int x,int y){
	int i=0;
	while(i){
		printf("please enter number between %d %d",x,y);
		int num;
		scanf("%d",num);
		if(num>0 && num<23)
		{
			i++;
			return num;
		}
	}
	return 0;
}
char* CheckDate(){
	char date[10];
	int i=0;
	while(i){
		printf("please enter date of the takeoff\n");
		scanf("%s",date);
		if(strcmp(date,"")==0)
			continue;
		if(strlen(date)>10)
			continue;
		if(!strstr(date,"/"))
			continue;
		if(checkDateStrck(date)==0)
			continue;
		i=1;
	}



	return *date;
}
int checkDateStrck(char  date[])
{
	char * temp=strtok(date,"/");
	if(strlen(temp[0])!=2 ||strlen(temp[1])!=2 ||strlen(temp[2])!=4 )
			return 0;
	return 1;
}
void printFlight(const Flight* fl){
	printf("the flight is:\n");
	printf("source airport:\n");
	printAirport(fl->apStart);
	printf("\n destation airport:\n");
	printAirport(fl->apDes);
	printf("\ndate : %s takeoff hour: %d   avgspeed %.2f",fl->date,fl->hourExit,fl->AvgSpeed);
}
void FreeFlight(Flight* fl){
	freeAirport(fl->apStart);
	freeAirport(fl->apDes);
}

//Errors
//how to return time flight
//free
