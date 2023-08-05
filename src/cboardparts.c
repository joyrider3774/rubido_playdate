#include <SDL.h>
#include "cboardparts.h"
#include "cpeg.h"

struct CBoardParts;

//constructor of boardparts, we start with 0 items
CBoardParts* CBoardParts_Create()
{
	CBoardParts* Result = (CBoardParts*) malloc(sizeof(CBoardParts));
	Result->ItemCount = 0;
	return Result;
}

void CBoardParts_Destroy(CBoardParts* BoardParts)
{
	CBoardParts_RemoveAll(BoardParts);
	free(BoardParts);
	BoardParts = NULL;
}

// returns a boardpart if it's found with the same coordinate otherwise return null
CPeg* CBoardParts_GetPart(CBoardParts* BoardParts, const int PlayFieldXin,const int PlayFieldYin)
{
    int Teller;
    for (Teller=0;Teller < BoardParts->ItemCount;Teller++)
        if((CPeg_GetPlayFieldX(BoardParts->Items[Teller]) == PlayFieldXin) && (CPeg_GetPlayFieldY(BoardParts->Items[Teller]) == PlayFieldYin))
            return BoardParts->Items[Teller];
    return NULL;
}

// Remove all board parts
void CBoardParts_RemoveAll(CBoardParts* BoardParts)
{
	int Teller;
	for (Teller=0;Teller<BoardParts->ItemCount;Teller++)
	{
		free(BoardParts->Items[Teller]);
		BoardParts->Items[Teller] = NULL;
	}
	BoardParts->ItemCount=0;
}

// Add a partboart, and set the boardparts parentlist to this (class/instance)
void CBoardParts_Add(CBoardParts* BoardParts, CPeg *BoardPart)
{
	if( BoardParts->ItemCount < 9*9*3 )
	{
		BoardPart->ParentList = BoardParts;
		BoardParts->Items[BoardParts->ItemCount] = BoardPart;
		BoardParts->ItemCount++;
	}
}

// draw all boarparts
void CBoardParts_Draw(CBoardParts* BoardParts, SDL_Surface *Surface)
{
	int Teller;
	for (Teller=0;Teller<BoardParts->ItemCount;Teller++)
		CPeg_Draw(BoardParts->Items[Teller], Surface);
}