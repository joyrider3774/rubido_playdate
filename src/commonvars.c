#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include "commonvars.h"
#include "cboardparts.h"
#include "cselector.h"
#include "cmainmenu.h"


SDL_Surface *IMGCredits,*IMGPeg,*IMGBackground,*IMGVeryEasy1,*IMGEasy1,*IMGHard1,*IMGVeryHard1,*IMGEasyInfo,*IMGVeryEasyInfo,*IMGHardInfo,*IMGVeryHardInfo;
int Difficulty = VeryEasy;
Mix_Chunk *Sounds[NrOfSounds]; // array that will hold the sounds

CBoardParts *BoardParts; // boardparts instance that will hold all the boardparts
int GameState = GSTitleScreenInit; // the game state
TTF_Font *font;
bool GlobalSoundEnabled = true; // used to see if the sound was opened succesfully
Mix_Music *Music; // the music
SDL_Surface *Screen; // the screen and buffer surface, buffer is used since hardware drawing will be used
int Moves=0,Volume = 128;
int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty

//game
CSelector *GameSelector;
bool PrintFormShown = false;

//titlescreen
CMainMenu* Menu;