#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>
#include "pd_api.h"

#define musTitle 1
#define musGame1 2
#define musGame2 3
#define musOldman 4
#define musStage 5

#define SFX_SUSTAIN 100

void initSound(void);
void SelectMusic(int musicFile);
void initMusic(void);
void playMenuSound(void);
void playDropBlockSound(void);
void playPickupBlockSound(void);
void playFlipBlockSound(void);
void playMenuSelectSound(void);
void playErrorSound(void);
void playBridgeSound(void);
void playStageEndSound(void);
void playElfSound(void);
void playRotateBlockSound(void);
void playTextSound(void);
void stopTextSound(void);

void setMusicOn(int value);
void setSoundOn(int value);
int isMusicOn(void);
int isSoundOn(void);
void stopMusic(void);
void deInitMusic(void);
void deInitSound(void);
SamplePlayer* loadSoundFile(AudioSample* Sample, const char* path);

#endif