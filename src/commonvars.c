#include <pd_api.h>
#include <stdbool.h>
#include "commonvars.h"
#include "cboardparts.h"
#include "cselector.h"
#include "cmainmenu.h"


LCDBitmap *IMGCredits,*IMGPeg,*IMGBackground,*IMGVeryEasy1,*IMGEasy1,*IMGHard1,*IMGVeryHard1,*IMGEasyInfo,*IMGVeryEasyInfo,*IMGHardInfo,*IMGVeryHardInfo;
int Difficulty = VeryEasy;
CBoardParts *BoardParts; // boardparts instance that will hold all the boardparts
int GameState = GSTitleScreenInit; // the game state
LCDFont *Ash;
LCDBitmap *Screen; // the screen and buffer surface, buffer is used since hardware drawing will be used
int Moves=0,Volume = 128;
int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty

//game
CSelector *GameSelector;
bool PrintFormShown = false;

//titlescreen
CMainMenu* Menu;

//main
PDButtons prevButtons, currButtons;
int showFps;
unsigned int prevLogTime;
unsigned int FrameTime, Frames;
float CurrentMs;
bool BatteryMonitoring;
PlaydateAPI* pd;

void setPDPtr(PlaydateAPI* p) {
	pd = p;
}