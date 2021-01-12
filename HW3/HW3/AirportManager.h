#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "LinkedList.h"

typedef struct
{
	Node* airports;
	int			count;
} AirportManager;

int		 initManager(AirportManager* pManager);
int		 addAirport(AirportManager* pManager);
void	 setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		 checkUniqeCode(const char* code, const AirportManager* pManager);
int		 compareByCode(const Airport* airport1, const Airport* airport2);
void	 printAirports(const AirportManager* pManager);
void	 freeManager(AirportManager* pManager);
void	 saveToTextFile(AirportManager* pManager);
int		 readFromTextFile(AirportManager* pManager);

#endif