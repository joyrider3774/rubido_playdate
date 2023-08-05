#include "main.h"
#include "pd_api.h"
#include "puzzleland.h"
#include "commonvars.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	if ( event == kEventInit )
	{
		setPDPtr(playdate);
		playdate->display->setRefreshRate(FRAMERATE);
		playdate->display->setOffset((LCD_COLUMNS - WINDOW_WIDTH) >> 1, 0);
		playdate->system->setUpdateCallback(mainLoop, NULL);
		setupGame();
	}
	return 0;
}
