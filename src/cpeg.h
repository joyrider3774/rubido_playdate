#ifndef CPEG_H
#define CPEG_H

#include <SDL.h>
#include <stdbool.h>
#include "commonvars.h"
#include "cboardparts.h"

typedef struct CBoardParts CBoardParts;
typedef struct CPeg CPeg;

//Base Class that defines a Cboardpart, it's only a peg
struct CPeg
{
 	int Type,X,Y,PlayFieldX,PlayFieldY,AnimPhase; //Animphase holds the current selected frame of the tile
 	SDL_Surface * Image;
 	CBoardParts *ParentList; // the parentlist, points to a CBoardParts class
};

CPeg* CPeg_Create(const int PlayFieldXin,const int PlayFieldYin);
int CPeg_GetType(CPeg* Peg);
int CPeg_GetX(CPeg* Peg);
int CPeg_GetY(CPeg* Peg);
int CPeg_GetPlayFieldX(CPeg* Peg);
int CPeg_GetPlayFieldY(CPeg* Peg);
int CPeg_GetAnimPhase(CPeg* Peg);
void CPeg_SetAnimPhase(CPeg* Peg,int AnimPhaseIn);
void CPeg_SetPosition(CPeg* Peg,const int PlayFieldXin,const int PlayFieldYin);
bool CPeg_CanMoveTo(CPeg* Peg,const int PlayFieldXin,const int PlayFieldYin,bool erase);
void CPeg_Draw(CPeg* Peg,SDL_Surface* Surface);
void CPeg_Destroy(CPeg* Peg);

#endif