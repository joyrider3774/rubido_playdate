#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "commonvars.h"

// A struct that holds x & y coordinate
typedef struct SPoint SPoint;
struct SPoint
{
    int X,Y;
};

typedef struct CSelector CSelector;
struct CSelector
{
	SPoint SelectedPoint,CurrentPoint; //variables to hold the current position and the selected position
    bool HasSelection;
};

// constructor, parameters define the starting position
CSelector* CSelector_Create(const int PlayFieldXin,const int PlayFieldYin);
// Will set the position only if it layes within the board boundary
void CSelector_SetPosition(CSelector* CSelector,const int PlayFieldXin,const int PlayFieldYin);
// Select will set the current position as the selected position
void CSelector_Select(CSelector* CSelector);
// return the selected position
SPoint CSelector_GetSelection(CSelector* CSelector);
// return the current position
SPoint CSelector_GetPosition(CSelector* CSelector);
void CSelector_DeSelect(CSelector* CSelector);
// Draw the blue box on the current position, with the offsets in mind
void CSelector_Draw(CSelector* CSelector);
void CSelector_Destroy(CSelector* CSelector);
#endif