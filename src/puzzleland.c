#include <stdbool.h>
#include <string.h>
#include "gamestates/game.h"
#include "gamestates/stageclear.h"
#include "gamestates/nextstage.h"
#include "gamestates/options.h"
#include "gamestates/stageselect.h"
#include "gamestates/oldmanspeaking.h"
#include "gamestates/passwordentry.h"
#include "gamestates/titlescreen.h"
#include "gamestates/intro.h"
#include "gamestates/credits.h"
#include "gamestates/gamecommon.h"
#include "gameobjects/chand.h"
#include "pd_helperfuncs.h"
#include "commonvars.h"
#include "sound.h"

void LoadFonts(void)
{
	Nano = loadFontAtPath("fonts/Nano Sans/Nano Sans");
	Mini = loadFontAtPath("fonts/Mini Sans/Mini Sans");
	Mini2X = loadFontAtPath("fonts/Mini Sans 2X/Mini Sans 2X");
	Ash = loadFontAtPath("fonts/Asheville-Sans-14-Bold/Asheville-Sans-14-Bold");
}

void setupGame()
{
	GameState = GSIntroInit;
	initSound();
	initMusic();
	LoadFonts();
	LoadImages();
	//setMusicOn(isMusicOnSaveState());
	//setSoundOn(isSoundOnSaveState());
	setMusicOn(true);
	setSoundOn(true);
	pd->graphics->setFont(Mini);
	Hand = CHand_Create();
}

int mainLoop(void* ud)
{
	prevButtons = currButtons;
	pd->system->getButtonState(&currButtons, NULL, NULL);
	switch(GameState)
	{
		case GSIntroInit :
		case GSIntro :
			Intro();
			break;
		case GSTitleScreenInit :
		case GSTitleScreen :
			TitleScreen();
			break;
		case GSOldManSpeakingInit :
		case GSOldManSpeaking :
			OldManSpeaking();
			break;
		case GSPasswordEntryInit :
		case GSPasswordEntry :
			PasswordEntry();
			break;
		case GSCreditsInit :
		case GSCredits :
			Credits();
			break;
		case GSOptionsInit :
		case GSOptions :
			Options();
			break;
		case GSGameInit :
		case GSGame :
			Game();
			break;
		case GSStageClearInit:
		case GSStageClear:
			StageClear();
			break;
		case GSNextStageInit:
		case GSNextStage:
			if (Level ==0)
				NextStageLevel0();
			else
				NextStageLevel1to35();
			break;
		case GSStageSelectInit:
		case GSStageSelect:
			StageSelect();
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
		pd->graphics->setFont(Mini2X);
		pd->graphics->fillRect(0, 0, pd->graphics->getTextWidth(Mini2X, Text, strlen(Text), kASCIIEncoding, 0), 16, kColorWhite);
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
