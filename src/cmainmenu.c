#include <pd_api.h>
#include "cmainmenu.h"
#include "commonvars.h"
#include "sound.h"
#include "pd_helperfuncs.h"

CMainMenu* CMainMenu_Create()
{
	CMainMenu* Result = pd->system->realloc(NULL, sizeof(CMainMenu));
    Result->Selection = 1;

    Result->IMGTitle = loadImageAtPath("./graphics/titlescreen.png");
    Result->IMGNewGame1 = loadImageAtPath("./graphics/newgame1.png");
    Result->IMGNewGame2 = loadImageAtPath("./graphics/newgame2.png");
    Result->IMGCredits1 = loadImageAtPath("./graphics/credits1.png");
    Result->IMGCredits2 = loadImageAtPath("./graphics/credits2.png");

	return Result;
}

 // return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu)
{
	return MainMenu->Selection;
}

// Destructor will free the surface images
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    pd->graphics->freeBitmap(MainMenu->IMGNewGame1);
    pd->graphics->freeBitmap(MainMenu->IMGNewGame2);
    pd->graphics->freeBitmap(MainMenu->IMGCredits1);
    pd->graphics->freeBitmap(MainMenu->IMGCredits2);
    pd->graphics->freeBitmap(MainMenu->IMGTitle);
    pd->system->realloc(MainMenu, 0);
    MainMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 3)
        MainMenu->Selection = 1;
    playSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 2;
    playSelectSound();
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    // draw the title screen background
    pd->graphics->drawBitmap(MainMenu->IMGTitle,0,0, kBitmapUnflipped);

    // if selection = newgame draw the purple new game image in the middle of the screen
    int w;
    if (MainMenu->Selection == 1)
    {
        pd->graphics->getBitmapData(MainMenu->IMGNewGame1, &w, NULL, NULL, NULL, NULL);
        pd->graphics->drawBitmap(MainMenu->IMGNewGame1, WINDOW_WIDTH / 2 - w / 2, 87, kBitmapUnflipped);
    }
    else
    // draw the blue one
    {
        pd->graphics->getBitmapData(MainMenu->IMGNewGame2, &w, NULL, NULL, NULL, NULL);
        pd->graphics->drawBitmap(MainMenu->IMGNewGame2, WINDOW_WIDTH / 2 - w / 2, 87, kBitmapUnflipped);
    }

    if (MainMenu->Selection == 2) // = credits draw purpe
    {
        pd->graphics->getBitmapData(MainMenu->IMGCredits1, &w, NULL, NULL, NULL, NULL);
        pd->graphics->drawBitmap(MainMenu->IMGCredits1, WINDOW_WIDTH / 2 - w / 2, 145, kBitmapUnflipped);
    }
    else // blue
    {
        pd->graphics->getBitmapData(MainMenu->IMGCredits2, &w, NULL, NULL, NULL, NULL);
        pd->graphics->drawBitmap(MainMenu->IMGCredits2, WINDOW_WIDTH / 2 - w / 2, 145, kBitmapUnflipped);
    }
}
