#include <SDL.h>
#include "cselector.h"
#include "commonvars.h"

CSelector* CSelector_Create(const int PlayFieldXin,const int PlayFieldYin)
{
	CSelector* Result = (CSelector*) malloc(sizeof(CSelector));
	Result->SelectedPoint.X = 0; // there's no selection set it 0
	Result->SelectedPoint.Y = 0;
	Result->CurrentPoint.X = PlayFieldXin; // set current position
	Result->CurrentPoint.Y = PlayFieldYin;
	Result->HasSelection = false; // No selection when it's created
	return Result;
}

void CSelector_SetPosition(CSelector *Selector, const int PlayFieldXin,const int PlayFieldYin)
{
	// check if the new position is inside the board, if so set the new position as the currentposition
	if (((PlayFieldYin>=0) && (PlayFieldYin < 3) && (PlayFieldXin > 2) && (PlayFieldXin < 6)) ||
		((PlayFieldYin > 2) && (PlayFieldYin<6) && (PlayFieldXin >=0) && (PlayFieldXin <NrOfCols)) ||
		((PlayFieldYin > 5)&& (PlayFieldYin < NrOfRows) && (PlayFieldXin > 2) && (PlayFieldXin <6)))
		{
			Selector->CurrentPoint.X = PlayFieldXin;
			Selector->CurrentPoint.Y = PlayFieldYin;
		}
}

void CSelector_Select(CSelector *Selector)
{
	Selector->SelectedPoint.X = Selector->CurrentPoint.X;
	Selector->SelectedPoint.Y = Selector->CurrentPoint.Y;
	Selector->HasSelection = true;
}

SPoint CSelector_GetSelection(CSelector *Selector)
{
	return Selector->SelectedPoint;
}

SPoint CSelector_GetPosition(CSelector *Selector)
{
	return Selector->CurrentPoint;
}

void CSelector_DeSelect(CSelector *Selector)
{
	Selector->HasSelection = false;
}


void CSelector_Draw(CSelector *Selector,SDL_Surface *Surface)
{
	rectangleRGBA(Surface, XOffSet + Selector->CurrentPoint.X * (TileWidth), YOffSet+ Selector->CurrentPoint.Y * (TileHeight), XOffSet-1 + (Selector->CurrentPoint.X +1)* (TileWidth ), YOffSet-1+ (Selector->CurrentPoint.Y+1) * (TileHeight), 0,0, 0, 255);
	rectangleRGBA(Surface, XOffSet + 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 1 + Selector->CurrentPoint.Y * (TileHeight), XOffSet-2 + (Selector->CurrentPoint.X +1)* (TileWidth ), YOffSet-2+ (Selector->CurrentPoint.Y+1) * (TileHeight), 255,255, 255, 255);
	rectangleRGBA(Surface, XOffSet + 2 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 2 + Selector->CurrentPoint.Y * (TileHeight), XOffSet-3 + (Selector->CurrentPoint.X +1)* (TileWidth ), YOffSet-3+ (Selector->CurrentPoint.Y+1) * (TileHeight), 255,255,255, 255);
	rectangleRGBA(Surface, XOffSet + 3 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 3 + Selector->CurrentPoint.Y * (TileHeight), XOffSet-4 + (Selector->CurrentPoint.X +1)* (TileWidth ), YOffSet-4+ (Selector->CurrentPoint.Y+1) * (TileHeight), 0,0, 0, 255);
}

void CSelector_Destroy(CSelector *Selector)
{
	free(Selector);
	Selector = NULL;
}