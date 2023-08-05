#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "cmainmenu.h"
#include "commonvars.h"

CMainMenu* CMainMenu_Create()
{
	CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
    SDL_Surface *Tmp;

    Tmp = IMG_Load("./graphics/titlescreen.png");
    Result->IMGTitle = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/newgame1.png");
    Result->IMGNewGame1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/newgame2.png");
    Result->IMGNewGame2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/credits1.png");
    Result->IMGCredits1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/credits2.png");
    Result->IMGCredits2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

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
    SDL_FreeSurface(MainMenu->IMGNewGame1);
    SDL_FreeSurface(MainMenu->IMGNewGame2);
    SDL_FreeSurface(MainMenu->IMGCredits1);
    SDL_FreeSurface(MainMenu->IMGCredits2);
    SDL_FreeSurface(MainMenu->IMGTitle);
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 3)
        MainMenu->Selection = 1;
    Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 2;
    Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu, SDL_Surface *Surface)
{
    SDL_Rect Dest;

    // draw the title screen background
    SDL_BlitSurface(MainMenu->IMGTitle,NULL,Surface,NULL);

    // if selection = newgame draw the purple new game image in the middle of the screen
    if (MainMenu->Selection == 1)
    {
        Dest.x = Surface->w/2 - MainMenu->IMGNewGame1->w/2;
        Dest.y = 87;
        Dest.w = MainMenu->IMGNewGame1->w;
        SDL_BlitSurface(MainMenu->IMGNewGame1,NULL,Surface,&Dest);
    }
    else
    // draw the blue one
    {
        Dest.x = Surface->w/2 - MainMenu->IMGNewGame2->w/2;
        Dest.y = 87;
        Dest.w = MainMenu->IMGNewGame2->w;
        SDL_BlitSurface(MainMenu->IMGNewGame2,NULL,Surface,&Dest);
    }

    if (MainMenu->Selection == 2) // = credits draw purpe
    {
        Dest.x = Surface->w/2 - MainMenu->IMGCredits1->w/2;
        Dest.y = 145;
        Dest.w = MainMenu->IMGCredits1->w;
        SDL_BlitSurface(MainMenu->IMGCredits1,NULL,Surface,&Dest);
    }
    else // blue
    {
        Dest.x = Surface->w/2 - MainMenu->IMGCredits2->w/2;
        Dest.y = 145;
        Dest.w = MainMenu->IMGCredits2->w;
        SDL_BlitSurface(MainMenu->IMGCredits2,NULL,Surface,&Dest);
    }
}
