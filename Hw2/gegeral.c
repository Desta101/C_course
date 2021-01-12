/*
 * gegeral.c
 *
 *  Created on: 7 May 2020
 *      Author: hen
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "general.h"
#define MAX_LENGTH 100
char* getStrExactLength() {
	char *theStr = NULL;
	int len;
	char inpStr[MAX_LENGTH]; //variable to hold the string that the user gives

	//Ask for a string from the user
	printf("Enter a String:");
	myGets(inpStr, sizeof(inpStr));
	//find string size and add 1 for the '\0'
	len = strlen(inpStr) + 1;
	//allocate a place for the string in the right location in the array
	theStr = (char*) malloc(len * sizeof(char));
	//Copy the string to the right location in the array
	if (theStr != NULL)
		strcpy(theStr, inpStr);

	return theStr;
}
char* myGets(char* buf, int size)
{
	if(buf != NULL && size > 0)
	{
		if(fgets(buf,size,stdin))
		{
			buf[strcspn(buf,"\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;

}
int NumberPosistive(){
	int i=0;
	while(i){
		printf("please postive number\n");
		int num;
		scanf("%d",num);
		if(num>0)
		{
			i++;
			return num;
		}
	}
	return 0;

}



