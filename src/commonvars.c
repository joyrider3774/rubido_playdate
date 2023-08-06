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
int Moves = 0;
int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty

//game
CSelector *GameSelector;
bool PrintFormShown = false;

//titlescreen
CMainMenu* Menu;

//main
PDButtons prevButtons, currButtons;
int showFps = false;
unsigned int prevLogTime;
unsigned int FrameTime, Frames;
float CurrentMs;
bool BatteryMonitoring = false;
PlaydateAPI* pd;
PDMenuItem* menuItem1, *menuItem2, *menuItem3;

void setPDPtr(PlaydateAPI* p) {
	pd = p;
}