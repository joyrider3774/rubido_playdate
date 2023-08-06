#include <pd_api.h>
#include "cselector.h"
#include "commonvars.h"

CSelector* CSelector_Create(const int PlayFieldXin,const int PlayFieldYin)
{
	CSelector* Result = pd->system->realloc(NULL, sizeof(CSelector));
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


void CSelector_Draw(CSelector *Selector)
{
	pd->graphics->drawRect(XOffSet - 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet - 1 + Selector->CurrentPoint.Y * (TileHeight), (TileWidth + 2), (TileHeight + 2), kColorBlack);
	pd->graphics->drawRect(XOffSet + Selector->CurrentPoint.X * (TileWidth), YOffSet+ Selector->CurrentPoint.Y * (TileHeight), TileWidth, TileHeight, kColorWhite);
	pd->graphics->drawRect(XOffSet + 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 1 + Selector->CurrentPoint.Y * (TileHeight), (TileWidth-2), (TileHeight-2), kColorWhite);
	pd->graphics->drawRect(XOffSet + 2 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 2 + Selector->CurrentPoint.Y * (TileHeight), (TileWidth-4), (TileHeight-4), kColorWhite);
	pd->graphics->drawRect(XOffSet + 3 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 3 + Selector->CurrentPoint.Y * (TileHeight), (TileWidth-6), (TileHeight-6), kColorBlack);
}

void CSelector_Destroy(CSelector *Selector)
{
	pd->system->realloc(Selector, 0);
	Selector = NULL;
}