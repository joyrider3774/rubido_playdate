#ifndef PD_HELPERFUNCS_H
#define PD_HELPERFUNCS_H

#include "pd_api.h"

void DrawBitmapScaledSrcRec(LCDBitmap* Bitmap, float xscale, float yscale, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH);
void DrawBitmapSrcRec(LCDBitmap* Bitmap, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH, LCDBitmapFlip FlipMode);
LCDFont* loadFontAtPath(const char* path);
LCDBitmap* loadImageAtPath(const char* path);
LCDBitmapTable* loadBitmapTableAtPath(const char* path);
unsigned int logPower(const char* filename, unsigned int logIntervalSeconds, unsigned int prevLogTime);

#endif