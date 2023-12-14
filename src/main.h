#ifndef MAIN_H
#define MAIN_H

#include "pd_api.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg);

#endif