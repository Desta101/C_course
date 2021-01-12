#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum
{
	eHourSort, eDateSort, eOriginCodeSort, eDestCodeSort, eNoSort
} eSortOptions;

typedef struct
{
	char* name;
	int				flightCount;
	Flight** flightArr;
	Node* dates;
	eSortOptions	sortOption;
} Company;

void	initCompany(Company* pComp);
int		addFlight(Company* pComp, const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	printPtrFlight(const Flight** flight);
void	freeFlightArr(Flight** arr, int size);
void	freePtrFlight(Flight** flight);
void	freeCompany(Company* pComp);
void	sortFlightsArr(Company* pComp);
void	searchFlight(Company* pComp);
int		compareByHour(const void* element1, const void* element2);
int		compareByDate(const void* element1, const void* element2);
int		compareByOriginCode(const void* element1, const void* element2);
int		compareByDestCode(const void* element1, const void* element2);
void	saveToBinaryFile(Company* pComp);
int		readFromBinaryFile(Company* pComp);

#endif

