#include <stdbool.h>
#include "cpeg.h"
#include "cboardparts.h"
#include "commonvars.h"

CPeg* CPeg_Create(const int PlayFieldXin,const int PlayFieldYin)
{
	CPeg* Result = (CPeg*) malloc(sizeof(CPeg));
	Result->Type = IDPeg; // Id, isn't actually used in the game but if u have diffrent boardparts, u can identify it by this
    Result->Image = IMGPeg; // set the image
    Result->AnimPhase = 0; // current frame = 0 (a red dot)
 	Result->PlayFieldX=PlayFieldXin; // Set the current playfield position
 	Result->PlayFieldY=PlayFieldYin;
 	Result->X=XOffSet + PlayFieldXin*TileWidth; //set the screen position (for drawing)
 	Result->Y=YOffSet + PlayFieldYin*TileHeight;
 	Result->ParentList = NULL;
	return Result;
}

int CPeg_GetType(CPeg* Peg) 
{
	return Peg->Type;
}

int CPeg_GetX(CPeg* Peg) 
{
	return Peg->X;
}
 	
int CPeg_GetY(CPeg* Peg) 
{
	return Peg->Y;
}
 	
int CPeg_GetPlayFieldX(CPeg* Peg) 
{
	return Peg->PlayFieldX;
}
 	
int CPeg_GetPlayFieldY(CPeg* Peg) 
{
	return Peg->PlayFieldY;
}
 	
int CPeg_GetAnimPhase(CPeg* Peg) 
{
	return Peg->AnimPhase;
}

void CPeg_SetAnimPhase(CPeg* Peg, int AnimPhaseIn) 
{ 
	Peg->AnimPhase = AnimPhaseIn;
}

void CPeg_SetPosition(CPeg* Peg, const int PlayFieldXin,const int PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		Peg->PlayFieldX=PlayFieldXin;
		Peg->PlayFieldY=PlayFieldYin;
		Peg->X=XOffSet + PlayFieldXin*TileWidth;
		Peg->Y=YOffSet + PlayFieldYin*TileHeight;
	}
}

bool CPeg_CanMoveTo(CPeg* Peg, const int PlayFieldXin,const int PlayFieldYin,bool erase) 
{
	bool temp;
	temp = true;
	float Xi,Yi;
	int LowX,LowY;
	// if there isn't a boardpart on the specified location
	if (!(CBoardParts_GetPart(Peg->ParentList, PlayFieldXin, PlayFieldYin)))
		return false;
	else
	// if the current frame isn't either a red peg or a blue peg
	if (!(Peg->AnimPhase <2))
		return false;
	else
	//if the place we wan't to move to is an empty peg (animphase = 6)
	if (CPeg_GetAnimPhase(CBoardParts_GetPart(Peg->ParentList,PlayFieldXin,PlayFieldYin)) == 6)
	{
		//calculate the diffrence between the 2 points as a float
		Xi = (float)abs(PlayFieldXin - Peg->PlayFieldX)/2;
		Yi = (float)abs(PlayFieldYin - Peg->PlayFieldY)/2;

		if((Difficulty == VeryHard ) || (Difficulty == Hard))
			// here we see if xi, or yi quals 1 io movement is vertical or horintal and
			// xi or yi is 1. if it isn't 1 this means the new position isn't
			// exactly 2 pegs further away
			temp = temp &&  (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)));
		else
			// same as above except we add a diagonal
			temp = temp && (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)) || ((Xi==1) && (Yi == 1)));
		if (temp)
		{
			// calculate the lowest X & Y coordinate
			// will be used to find the middle peg (io the one we jumped over)
			if (PlayFieldXin <= Peg->PlayFieldX)
				LowX = PlayFieldXin;
			else
				LowX = Peg->PlayFieldX;
			if (PlayFieldYin <= Peg->PlayFieldY)
				LowY = PlayFieldYin;
			else
				LowY = Peg->PlayFieldY;
			// if the middle peg doesn't exists
				if (!(CBoardParts_GetPart(Peg->ParentList, LowX+(int)Xi,LowY+(int)Yi)))
				return false;
			else
			// If the middle peg is either a blue (will never happen) or a red peg
			if (CPeg_GetAnimPhase(CBoardParts_GetPart(Peg->ParentList, LowX+(int)Xi,LowY+(int)Yi)) < 2)
			{
				// simple hack to specify we want the middle peg to be emptied (animpahse = 6)
				// i did this so i didn't need to do the above calcultions again in Game()
				if (erase)
					CPeg_SetAnimPhase(CBoardParts_GetPart(Peg->ParentList, LowX+(int)Xi,LowY+(int)Yi),6);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

void CPeg_Draw(CPeg* Peg, SDL_Surface* Surface) // drawing
{
	//printf("Start draw type:%d\n",Type);
	if (Peg->Image)
	{

		SDL_Rect SrcRect,DstRect;
		SrcRect.x = Peg->AnimPhase * TileWidth; // current frame * tilewidth is
		SrcRect.y = 0;
		SrcRect.w = TileWidth;
		SrcRect.h = TileHeight;
		DstRect.x = Peg->X;
		DstRect.y = Peg->Y;
		DstRect.w = TileWidth;
		DstRect.h = TileHeight;
		SDL_BlitSurface(Peg->Image,&SrcRect,Surface,&DstRect); // blit it to the specified surface
	}
}

void CPeg_Destroy(CPeg* Peg)
{
	free(Peg);
	Peg = NULL;
}