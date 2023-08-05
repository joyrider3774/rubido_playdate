#ifndef COMMONVARS_H
#define COMMONVARS_H

#include <pd_api.h>
#include <stdbool.h>
#include "cselector.h"
#include "cmainmenu.h"

typedef struct CBoardParts CBoardParts;
typedef struct CPeg CPeg;
typedef struct SPoint SPoint;
typedef struct CSelector CSelector;

#define FRAMERATE 15

// The diffrent difficultys
#define VeryEasy 0
#define Easy 1
#define Hard 2
#define VeryHard 3

// The diffrent gameStates possible in the game
#define GSQuit 0
#define GSGame 1 
#define GSTitleScreen 2
#define GSDifficultySelect 3 
#define GSCredits 4

#define GSInitDiff 50

#define GSGameInit (GSGame + GSInitDiff)
#define GSTitleScreenInit (GSTitleScreen + GSInitDiff)
#define GSDifficultySelectInit (GSDifficultySelect + GSInitDiff)
#define GSCreditsInit (GSCredits + GSInitDiff)

// window size
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

//game defines
#define NrOfRows 9
#define NrOfCols 9
#define TileWidth 24
#define TileHeight 24
#define IDPeg 1
#define XOffSet 10
#define YOffSet 11


extern LCDBitmap *IMGCredits,*IMGPeg,*IMGBackground,*IMGVeryEasy1,*IMGEasy1,*IMGHard1,*IMGVeryHard1,*IMGEasyInfo,*IMGVeryEasyInfo,*IMGHardInfo,*IMGVeryHardInfo;
extern int Difficulty;

extern CBoardParts *BoardParts; // boardparts instance that will hold all the boardparts
extern int GameState; // the game state
extern LCDFont *Ash;
extern LCDBitmap *Screen; // the screen and buffer surface, buffer is used since hardware drawing will be used
extern int Moves,Volume;
extern int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty

//game
extern CSelector *GameSelector;
extern bool PrintFormShown;

//titlescreen
extern CMainMenu* Menu;

//main
extern PDButtons prevButtons, currButtons;
extern int showFps;
extern unsigned int prevLogTime;
extern unsigned int FrameTime, Frames;
extern float CurrentMs;
extern bool BatteryMonitoring;
extern PlaydateAPI* pd;

void setPDPtr(PlaydateAPI* p);

#endif