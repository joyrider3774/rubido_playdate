#include <string.h>
#include "pd_helperfuncs.h"
#include "commonvars.h"
#include "pd_api.h"


LCDBitmap* loadImageAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDBitmap* img = pd->graphics->loadBitmap(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading image at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return img;
}

LCDBitmapTable* loadBitmapTableAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDBitmapTable* table = pd->graphics->loadBitmapTable(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading image at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return table;
}

LCDFont* loadFontAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDFont* fnt = pd->graphics->loadFont(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading font at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading font at path '%s': %s", path, outErr);
	}
	return fnt;
}

void DrawBitmapSrcRec(LCDBitmap* Bitmap, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH, LCDBitmapFlip FlipMode)
{
	pd->graphics->pushContext(Bitmap);
	pd->graphics->setClipRect(srcX, srcY, srcW, srcH);
	pd->graphics->pushContext(NULL);
	pd->graphics->setClipRect(dstX, dstY, srcW, srcH);
	pd->graphics->setDrawOffset(-srcX + dstX, -srcY + dstY);
	pd->graphics->drawBitmap(Bitmap, 0, 0, FlipMode);
	pd->graphics->setDrawOffset(0, 0);
	pd->graphics->clearClipRect();
	pd->graphics->popContext();
	pd->graphics->popContext();
}

void DrawBitmapScaledSrcRec(LCDBitmap* Bitmap, float xscale, float yscale, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH)
{
	pd->graphics->setClipRect(dstX, dstY, (int)(srcW * xscale), (int)(srcH * yscale));
	pd->graphics->setDrawOffset((int)(-srcX * xscale) + dstX, (int)(-srcY * yscale) + dstY);
	pd->graphics->drawScaledBitmap(Bitmap, 0, 0, xscale, yscale);
	pd->graphics->setDrawOffset(0, 0);
	pd->graphics->clearClipRect();
}

unsigned int logPower(const char* filename, unsigned int logIntervalSeconds, unsigned int prevLogTime)
{
	unsigned int s = pd->system->getSecondsSinceEpoch(NULL);
	if(s - prevLogTime >= logIntervalSeconds)
	{
		float p = pd->system->getBatteryPercentage();
		float v = pd->system->getBatteryVoltage();
		SDFile* file = pd->file->open(filename, kFileAppend);
		if (file)
		{
			char* line;
			pd->system->formatString(&line, "%d, %f, %f\n", s, p, v);
			pd->file->write(file, line, (unsigned int)strlen(line));
			pd->system->realloc(line, 0);
			//simulator crashes on windows when calling flush
#ifndef _WIN32
			pd->file->flush(file);
#endif
			pd->file->close(file);
		}
		return s;
	}
	return prevLogTime;
}
