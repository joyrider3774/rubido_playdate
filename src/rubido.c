#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pd_api.h>
#include "pd_helperfuncs.h"
#include "sound.h"
#include "cboardparts.h"
#include "cmainmenu.h"
#include "cpeg.h"
#include "cselector.h"
#include "commonvars.h"

// Load the settings, if there isn't a settings file, set some initial values
void LoadSettings()
{
	SDFile* SettingsFile;
	SettingsFile = pd->file->open("settings.dat", kFileReadData);
	if (SettingsFile)
	{
		pd->file->read(SettingsFile, &BestPegsLeft[VeryEasy], sizeof(int));
		pd->file->read(SettingsFile, &BestPegsLeft[Easy], sizeof(int));
		pd->file->read(SettingsFile, &BestPegsLeft[Hard], sizeof(int));
		pd->file->read(SettingsFile, &BestPegsLeft[VeryHard], sizeof(int));
		int tmp;
		pd->file->read(SettingsFile, &tmp, sizeof(int));
		setSoundOn(tmp);
		pd->file->read(SettingsFile, &tmp, sizeof(int));
		setMusicOn(tmp);
		pd->file->close(SettingsFile);
	}
	else
	{
		BestPegsLeft[VeryEasy] = 0;
		BestPegsLeft[Easy] = 0;
		BestPegsLeft[Hard] = 0;
		BestPegsLeft[VeryHard] = 0;
		setSoundOn(true);
		setMusicOn(true);
	}
}

// Save the settings
void SaveSettings()
{
	SDFile* SettingsFile;
	SettingsFile = pd->file->open("settings.dat", kFileWrite);
	if (SettingsFile)
	{
		pd->file->write(SettingsFile, &BestPegsLeft[VeryEasy], sizeof(int));
		pd->file->write(SettingsFile, &BestPegsLeft[Easy], sizeof(int));
		pd->file->write(SettingsFile, &BestPegsLeft[Hard], sizeof(int));
		pd->file->write(SettingsFile, &BestPegsLeft[VeryHard], sizeof(int));
		int tmp = isSoundOn();
		pd->file->write(SettingsFile, &tmp, sizeof(int));
		tmp = isMusicOn();
		pd->file->write(SettingsFile, &tmp, sizeof(int));
		pd->file->close(SettingsFile);
	}
}


void LoadFonts(void)
{
	Ash = loadFontAtPath("fonts/Asheville-Sans-14-Bold/Asheville-Sans-14-Bold");
}

void LoadGraphics()
{
	IMGBackground = loadImageAtPath("graphics/background");
	IMGPeg = loadImageAtPath("graphics/peg");
	IMGVeryEasyInfo = loadImageAtPath("graphics/infoveryeasy");
	IMGEasyInfo = loadImageAtPath("graphics/infoeasy");
	IMGHardInfo = loadImageAtPath("graphics/infohard");
	IMGVeryHardInfo = loadImageAtPath("graphics/infoveryhard");
	IMGVeryEasy1 = loadImageAtPath("graphics/veryeasy1");
	IMGEasy1 = loadImageAtPath("graphics/easy1");
	IMGHard1 = loadImageAtPath("graphics/hard1");
	IMGVeryHard1 = loadImageAtPath("graphics/veryhard1");
	IMGCredits = loadImageAtPath("graphics/credits");
}

void UnLoadGraphics()
{
	if (IMGBackground)
	{
		pd->graphics->freeBitmap(IMGBackground);
	}

	if (IMGPeg)
	{
		pd->graphics->freeBitmap(IMGPeg);
	}

	if (IMGVeryEasy1)
	{
		pd->graphics->freeBitmap(IMGVeryEasy1);
	}

	if (IMGEasy1)
	{
		pd->graphics->freeBitmap(IMGEasy1);
	}

	if (IMGHard1)
	{
		pd->graphics->freeBitmap(IMGHard1);
	}

	if (IMGVeryHard1)
	{
		pd->graphics->freeBitmap(IMGVeryHard1);
	}

	if (IMGVeryEasyInfo)
	{
		pd->graphics->freeBitmap(IMGVeryEasyInfo);
	}

	if (IMGEasyInfo)
	{
		pd->graphics->freeBitmap(IMGEasyInfo);
	}

	if (IMGHardInfo)
	{
		pd->graphics->freeBitmap(IMGHardInfo);
	}

	if (IMGVeryHardInfo)
	{
		pd->graphics->freeBitmap(IMGVeryHardInfo);
	}

	if (IMGCredits)
	{
		pd->graphics->freeBitmap(IMGVeryHardInfo);
	}

}


void setupGame()
{
	GameState = GSTitleScreenInit;
	initSound();
	initMusic();
	LoadFonts();
	LoadGraphics();
	LoadSettings();
	pd->graphics->setFont(Ash);
	BoardParts = CBoardParts_Create();
	Menu = CMainMenu_Create();
	GameSelector = CSelector_Create(4,4);
	pd->graphics->setBackgroundColor(kColorWhite);
}

void MenuItemCallback(void* userdata)
{
	if (userdata == &menuItem1)
	{
		GameState = GSTitleScreenInit;
	}

	if (userdata == &menuItem2)
	{
		setMusicOn(!isMusicOn());
		SaveSettings();
	}

	if (userdata == &menuItem3)
	{
		setSoundOn(!isSoundOn());
		SaveSettings();
	}
}

void DestroyMenuItems()
{
	if (menuItem1)
	{
		pd->system->removeMenuItem(menuItem1);
		menuItem1 = NULL;
	}

	if (menuItem2)
	{
		pd->system->removeMenuItem(menuItem2);
		menuItem2 = NULL;
	}

	if (menuItem3)
	{
		pd->system->removeMenuItem(menuItem3);
		menuItem3 = NULL;
	}
}

void CreateGameMenuItems()
{
	DestroyMenuItems();
	//TitleScreen
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Title Screen", MenuItemCallback, &menuItem1);
	}

	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addCheckmarkMenuItem("Music", isMusicOn(), MenuItemCallback, &menuItem2);
	}

	if (menuItem3 == NULL)
	{
		menuItem3 = pd->system->addCheckmarkMenuItem("Sound", isSoundOn(), MenuItemCallback, &menuItem3);
	}
}

void CreateTitleScreenMenuItems()
{
	DestroyMenuItems();
	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addCheckmarkMenuItem("Music", isMusicOn(), MenuItemCallback, &menuItem2);
	}

	if (menuItem3 == NULL)
	{
		menuItem3 = pd->system->addCheckmarkMenuItem("Sound", isSoundOn(), MenuItemCallback, &menuItem3);
	}
}


// procedure that calculates how many moves are possible in the current board state
// we can simply do this by checking all parts and see if they can move to all directions
// the canmoveto method in CPegs is does all the checking
int MovesLeft()
{
    CPeg *BoardPart ;
    int TmpMoves=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = CBoardParts_GetPart(BoardParts, X,Y);
            // if there is a boardpart on that X,Y Coordinate
            // check all direction if we can move to that if so increases the movesleft
            if (BoardPart)
            {
                if (CPeg_CanMoveTo(BoardPart,X+2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y-2,false))
                    TmpMoves++;
            }
        }
    return TmpMoves;
}

// Procedure that counts how many pegs are left on the board (animphase must be lower then 2 io a red or blue peg)
int PegsLeft()
{
    CPeg *BoardPart ;
    int Pegs=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = CBoardParts_GetPart(BoardParts,X,Y);
            if (BoardPart)
                if ((CPeg_GetType(BoardPart) == IDPeg) && (CPeg_GetAnimPhase(BoardPart) < 2))
                    Pegs++;
        }
    return Pegs;
}

// procedure that draws the board, boardparts info and a boxed message over the playfield
// and waits till the A button is pressed

void PrintForm(char *msg)
{
	PrintFormShown = true;
	pd->graphics->fillRect(3,75,231,160-55,kColorWhite);
	pd->graphics->drawRect(3,75,231,160-55,kColorBlack);
	pd->graphics->drawRect(5,77,231-4,160-55-4,kColorBlack);
	pd->graphics->drawText(msg,strlen(msg),kASCIIEncoding,9,85);
}

// this will ceate the initial board state, io a cross of pegs, with the middle on being empty (=animphase 6)
void InitBoard()
{
	CBoardParts_RemoveAll(BoardParts);
    int X,Y;
    for (Y=0;Y < NrOfRows;Y++)
        for (X=0;X < NrOfCols;X++)
        {
            if ((Y < 3) && (X > 2) && (X < 6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
             if ((Y > 2) && (Y <6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
            if ((Y > 5) && (X > 2) && (X <6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
        }
     CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,4,4), 6);

}

// Checks if we won the game
bool IsWinningGame()
{
    if (PegsLeft() == 1) //must be 1 peg left
    {
        if ((Difficulty == VeryHard) || (Difficulty == Easy))
        {
            if(CPeg_GetAnimPhase(CBoardParts_GetPart(BoardParts,4,4)) < 2) // must be in the middle with veryhard or easy
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

void GameInit()
{
	pd->graphics->setBackgroundColor(kColorBlack);
	CSelector_SetPosition(GameSelector, 4, 4);
	InitBoard();
    Moves = 0;
	playStartSound();
	CreateGameMenuItems();
	PrintFormShown = false;
}

// The main Game Loop
void Game()
{
	if (GameState == GSGameInit)
	{
		GameInit();
		GameState -= GSInitDiff;
	}
	pd->graphics->drawBitmap(IMGBackground, 0, 0, kBitmapUnflipped);
	char* Msg;
	// Write some info to the screen
	pd->system->formatString(&Msg, "Moves Left:%d", MovesLeft());
	pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, 242, 37);
	pd->system->realloc(Msg, 0);

	pd->system->formatString(&Msg, "Moves:%d", Moves);
	pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, 242, 53);
	pd->system->realloc(Msg, 0);

	pd->system->formatString(&Msg, "Pegs Left:%d", PegsLeft());
	pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, 242, 69);
	pd->system->realloc(Msg, 0);

	// Only show best pegs if it isn't 0
	if (BestPegsLeft[Difficulty] != 0)
	{
		pd->system->formatString(&Msg, "Best Pegs:%d", BestPegsLeft[Difficulty]);
		pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, 242, 85);
	}
	CBoardParts_Draw(BoardParts);
	CSelector_Draw(GameSelector);

	//need to repeat showing it until it's no longer shown
	if (PrintFormShown)
	{
		// if it's the winning game play the winning sound and show the form with the winning message
		if (IsWinningGame())
		{
			PrintForm("Congrats you have solved the\npuzzle! Try a new difficulty!\n\nPress (A) to continue");
		}
		else // show the loser messager, play loser sound
		{
			PrintForm("You couldn't solve the puzzle!\nDon't give up, try it again!\n\nPress (A) to continue");
		}
	}

	if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X - 1, CSelector_GetPosition(GameSelector).Y);

	if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X + 1, CSelector_GetPosition(GameSelector).Y);

	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y - 1);

	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y + 1);

	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
		if (!PrintFormShown && GameSelector->HasSelection)
		{
			CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetSelection(GameSelector).X, CSelector_GetSelection(GameSelector).Y), 0);
			CSelector_DeSelect(GameSelector);
		}

	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		if (PrintFormShown)
		{
			GameState = GSTitleScreenInit;
			PrintFormShown = false;
		}
		else
		{
			if (GameSelector->HasSelection) // if we have a selection
			{
				// see if the selected boardpart can move to the current position
				if (CPeg_CanMoveTo(CBoardParts_GetPart(BoardParts, CSelector_GetSelection(GameSelector).X, CSelector_GetSelection(GameSelector).Y), CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y, true))
				{
					playGoodSound();
					//if so play a sound, increase the moves, set the selected part to empty and the current part to red
					Moves++;
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetSelection(GameSelector).X, CSelector_GetSelection(GameSelector).Y), 6);
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y), 0);
					// if no moves are left see if the best pegs left value for the current difficulty is
					// greater if so set te new value
					if (MovesLeft() == 0)
					{
						if (BestPegsLeft[Difficulty] != 0)
						{
							if (PegsLeft() < BestPegsLeft[Difficulty])
								BestPegsLeft[Difficulty] = PegsLeft();
						}
						else
							BestPegsLeft[Difficulty] = PegsLeft();
						SaveSettings();
						// if it's the winning game play the winning sound and show the form with the winning message
						if (IsWinningGame())
						{
							playWinnerSound();
							PrintFormShown = true;
						}
						else // show the loser messager, play loser sound
						{
							playLoserSound();
							PrintFormShown = true;
						}
					}

				}
				else // if we can't move to the spot, play the wrong move sound, and reset the selection to a red peg (instead of blue / selected)
				{
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetSelection(GameSelector).X, CSelector_GetSelection(GameSelector).Y), 0);
					playWrongSound();
				}
				CSelector_DeSelect(GameSelector); // deselect the selection
			}
			else // we didn't have a selection, set the new selection
			{
				if (CPeg_GetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y)) == 0)
				{
					playSelectSound();
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts, CSelector_GetPosition(GameSelector).X, CSelector_GetPosition(GameSelector).Y), 1);
					CSelector_Select(GameSelector);
				}

			}
		}
	}
}

void TitleScreenInit()
{
	pd->graphics->setBackgroundColor(kColorWhite);
	CreateTitleScreenMenuItems();
	SelectMusic(musTitle);
}

// main title screen loop
void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSInitDiff;
	}
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		CMainMenu_NextItem(Menu);
	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		CMainMenu_PreviousItem(Menu);
	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		playGoodSound();
		switch (CMainMenu_GetSelection(Menu))
		{
			case 1:
				GameState = GSDifficultySelectInit;
				break;
			case 2:
				GameState = GSCreditsInit;
				break;
		}
	}
	CMainMenu_Draw(Menu);
}

void DifficultySelectInit()
{
	CreateGameMenuItems();
}

// Main difficulty select loop
void DifficultySelect()
{
	if(GameState == GSDifficultySelectInit)
	{
		DifficultySelectInit();
		GameState -= GSInitDiff;
	}

	if ((currButtons & kButtonA) && ! (prevButtons & kButtonA))
		GameState = GSGameInit;
	
	if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
	{
		if (Difficulty == VeryHard)
		{
			Difficulty = Hard;
		}
		else
			if (Difficulty == Hard)
			{
				Difficulty = Easy;
			}
			else
				if (Difficulty == Easy)
				{
					Difficulty = VeryEasy;
				}
				else
					if (Difficulty == VeryEasy)
						Difficulty = VeryHard;
	}
	
	if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
	{
		if (Difficulty == VeryEasy)
		{
			Difficulty = Easy;
		}
		else
			if (Difficulty == Easy)
			{
				Difficulty = Hard;
			}
			else
				if (Difficulty == Hard)
				{
					Difficulty = VeryHard;
				}
				else
					if (Difficulty == VeryHard)
						Difficulty = VeryEasy;
	}
	
	// decide what we draw to the buffer based on the difficuly
	int w;
	switch(Difficulty)
	{
		case VeryEasy:
			pd->graphics->getBitmapData(IMGVeryEasy1, &w, NULL, NULL, NULL, NULL);
			pd->graphics->drawBitmap(IMGVeryEasyInfo, 0, 0, kBitmapUnflipped);
			pd->graphics->drawBitmap(IMGVeryEasy1, WINDOW_WIDTH / 2 - w / 2, 35, kBitmapUnflipped);
			break;
		case Easy:
			pd->graphics->getBitmapData(IMGEasy1, &w, NULL, NULL, NULL, NULL);
			pd->graphics->drawBitmap(IMGEasyInfo, 0, 0, kBitmapUnflipped);
			pd->graphics->drawBitmap(IMGEasy1, WINDOW_WIDTH / 2 - w / 2, 35, kBitmapUnflipped);
			break;
		case Hard:
			pd->graphics->getBitmapData(IMGHard1, &w, NULL, NULL, NULL, NULL);
			pd->graphics->drawBitmap(IMGHardInfo, 0, 0, kBitmapUnflipped);
			pd->graphics->drawBitmap(IMGHard1, WINDOW_WIDTH / 2 - w / 2, 35, kBitmapUnflipped);
			break;
		case VeryHard:
			pd->graphics->getBitmapData(IMGVeryHard1, &w, NULL, NULL, NULL, NULL);
			pd->graphics->drawBitmap(IMGVeryHardInfo, 0, 0, kBitmapUnflipped);
			pd->graphics->drawBitmap(IMGVeryHard1, WINDOW_WIDTH / 2 - w / 2, 35, kBitmapUnflipped);
			break;

	}
}

void CreditsInit()
{
	CreateGameMenuItems();
}

//Main Credits loop, will just show an image and wait for a button to be pressed
void Credits()
{
	if (GameState == GSCreditsInit)
	{
		CreditsInit();
		GameState -= GSInitDiff;
	}

	if (((currButtons & kButtonA) && ! (prevButtons & kButtonA)) || 
		((currButtons & kButtonB) && ! (prevButtons & kButtonB)))
			GameState = GSTitleScreenInit;
	pd->graphics->drawBitmap(IMGCredits, 0, 0, kBitmapUnflipped);
}

int mainLoop(void* ud)
{
	prevButtons = currButtons;
	pd->system->getButtonState(&currButtons, NULL, NULL);
    switch(GameState)
    {
		case GSGameInit:
        case GSGame :
            Game();
            break;
		case GSTitleScreenInit:
        case GSTitleScreen:
            TitleScreen();
            break;
		case GSDifficultySelectInit:
        case GSDifficultySelect:
            DifficultySelect();
            break;
		case GSCreditsInit:
        case GSCredits:
            Credits();
            break;
		default:
			break;
    }
	if (showFps)
	{
		Frames++;
		if (pd->system->getCurrentTimeMilliseconds() - FrameTime >= 1000)
		{
			CurrentMs = (float)(1000.0f / Frames);
			Frames = 0;
			FrameTime += 1000;
		}
		char* Text;
		pd->system->formatString(&Text, "%f %f", CurrentMs, 1000.0f / CurrentMs);
		pd->graphics->pushContext(NULL);
		pd->graphics->setFont(Ash);
		pd->graphics->fillRect(0, 0, pd->graphics->getTextWidth(Ash, Text, strlen(Text), kASCIIEncoding, 0), 16, kColorWhite);
		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 0, 0);
		pd->system->realloc(Text, 0);
		pd->graphics->popContext();
	}
	if (BatteryMonitoring)
	{
		pd->system->setAutoLockDisabled(true);
		prevLogTime = logPower("power.csv", 60u, prevLogTime);
	}
	return 1;

}
