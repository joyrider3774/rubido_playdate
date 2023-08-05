#include <stdint.h>
#include <string.h>
#include "sound.h"
#include "pd_api.h"
#include "commonvars.h"

int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

FilePlayer* musicPlayer;

SamplePlayer* stageEndSoundPlayer;
SamplePlayer* menuSoundPlayer;
SamplePlayer* errorSoundPlayer;
SamplePlayer* menuSelectSoundPlayer;
SamplePlayer* flipBlockSoundPlayer;
SamplePlayer* pickupBlockSoundPlayer;
SamplePlayer* dropBlockSoundPlayer;
SamplePlayer* rotateBlockSoundPlayer;
SamplePlayer* bridgeSoundPlayer;
SamplePlayer* elfSoundPlayer;
SamplePlayer* textSoundPlayer;


AudioSample* stageEndSound;
AudioSample* errorSound;
AudioSample* menuSound;
AudioSample* menuSelectSound;
AudioSample* flipBlockSound;
AudioSample* pickupBlockSound;
AudioSample* dropBlockSound;
AudioSample* rotateBlockSound;
AudioSample* bridgeSound;
AudioSample* elfSound;
AudioSample* textSound;

void stopMusic(void)
{
    if (pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }
}

void setMusicOn(int value)
{
    music_on = value;
    if(music_on)
    {
        if (prev_music != -1)
        {
            force = 1;
            SelectMusic(prev_music);
        }
        else if (GameState == GSTitleScreen)
        {
            force = 1;
            SelectMusic(musTitle);
        }
    }
    else
    {
        stopMusic();
    }
}

void setSoundOn(int value)
{
    sound_on = value;
}

int isMusicOn(void)
{
    return music_on;
}

int isSoundOn(void)
{
    return sound_on;
}

SamplePlayer* loadSoundFile(AudioSample* Sample, const char* path)
{   
    Sample = NULL;
    SamplePlayer* soundPlayer = pd->sound->sampleplayer->newPlayer();
    if (soundPlayer)
    {
        Sample = pd->sound->sample->load(path);
        if (Sample)
        {
            pd->sound->sampleplayer->setSample(soundPlayer, Sample);
            pd->sound->sampleplayer->setVolume(soundPlayer, 0.7f, 0.7f);
            pd->sound->sampleplayer->setRate(soundPlayer, 1.0f);
        }
    }
    return soundPlayer;
}

void FreeSample(AudioSample* Sample)
{
    if (Sample)
    {
        pd->sound->sample->freeSample(Sample);
    }
    Sample = NULL;
}

void FreeSoundPlayer(SamplePlayer* SoundPlayer)
{
    if (SoundPlayer)
    {
        pd->sound->sampleplayer->freePlayer(SoundPlayer);
    }
    SoundPlayer = NULL;
}

void initSound(void)
{
    stageEndSoundPlayer = loadSoundFile(stageEndSound, "sounds/stageend");
    errorSoundPlayer = loadSoundFile(errorSound, "sounds/error");
    menuSelectSoundPlayer = loadSoundFile(menuSelectSound, "sounds/select");
    menuSoundPlayer = loadSoundFile(menuSound, "sounds/menu");
    flipBlockSoundPlayer = loadSoundFile(flipBlockSound, "sounds/rotate");
    pickupBlockSoundPlayer = loadSoundFile(pickupBlockSound, "sounds/pickup");
    dropBlockSoundPlayer = loadSoundFile(dropBlockSound, "sounds/drop");
    rotateBlockSoundPlayer = loadSoundFile(rotateBlockSound, "sounds/rotate");
    bridgeSoundPlayer = loadSoundFile(bridgeSound, "sounds/bridge");
    elfSoundPlayer = loadSoundFile(elfSound, "sounds/elf");
    textSoundPlayer = loadSoundFile(textSound, "sounds/text");
}

void deInitSound(void)
{
    FreeSample(stageEndSound);
    FreeSample(errorSound);
    FreeSample(menuSelectSound);
    FreeSample(menuSound);
    FreeSample(pickupBlockSound);
    FreeSample(dropBlockSound);
    FreeSample(rotateBlockSound);
    FreeSample(bridgeSound);
    FreeSample(elfSound);
    FreeSample(flipBlockSound);
    FreeSample(textSound);


    FreeSoundPlayer(stageEndSoundPlayer);
    FreeSoundPlayer(errorSoundPlayer);
    FreeSoundPlayer(menuSelectSoundPlayer);
    FreeSoundPlayer(menuSoundPlayer);
    FreeSoundPlayer(pickupBlockSoundPlayer);
    FreeSoundPlayer(dropBlockSoundPlayer);
    FreeSoundPlayer(rotateBlockSoundPlayer);
    FreeSoundPlayer(bridgeSoundPlayer);
    FreeSoundPlayer(elfSoundPlayer);
    FreeSoundPlayer(flipBlockSoundPlayer);
    FreeSoundPlayer(textSoundPlayer);
}

void playMusicFile(const char* path, int repeat)
{
    if(pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }

    if (pd->sound->fileplayer->loadIntoPlayer(musicPlayer, path))
    {
        pd->sound->fileplayer->play(musicPlayer, repeat);
    }
}

void SelectMusic(int musicFile)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        force = 0;
        prev_music = musicFile;
        switch (musicFile) 
        {
            case musTitle:
                playMusicFile("music/title", 0);
                break;
            case musGame1:
                playMusicFile("music/game1", 0);
                break;
            case musGame2:
                playMusicFile("music/game2", 0);
                break;
            case musOldman:
                playMusicFile("music/oldman", 0);
                break;
            case musStage:
                playMusicFile("music/stage", 0);
                break;
        }
    }
    else
    {
        //still need to remember last music we tried to play in case music was off & we reenable
        if (!music_on)
        {
            prev_music = musicFile;
        }
    }
}


void initMusic(void)
{
    prev_music = -1;
    musicPlayer = pd->sound->fileplayer->newPlayer();
    pd->sound->fileplayer->setStopOnUnderrun(musicPlayer, 0);
    pd->sound->fileplayer->setVolume(musicPlayer, 0.55f, 0.55f);
    pd->sound->fileplayer->setRate(musicPlayer, 1.0f);
}

void deInitMusic(void)
{
    if (pd->sound->fileplayer->isPlaying(musicPlayer))
    {
        pd->sound->fileplayer->stop(musicPlayer);
    }

    pd->sound->fileplayer->freePlayer(musicPlayer);
    musicPlayer = NULL;
}

void stopSound(SamplePlayer* soundPlayer)
{
    if (pd->sound->sampleplayer->isPlaying(soundPlayer))
    {
        pd->sound->sampleplayer->stop(soundPlayer);
    }
}

void playSound(SamplePlayer* soundPlayer, int repeats)
{
    if (!sound_on)
    {
        return;
    }

    if (pd->sound->sampleplayer->isPlaying(soundPlayer))
    {
        pd->sound->sampleplayer->stop(soundPlayer);
    }
    pd->sound->sampleplayer->play(soundPlayer, repeats, 1.0f);   
}

void stopTextSound(void)
{
    stopSound(textSoundPlayer);
}

void playTextSound(void)
{
    playSound(textSoundPlayer, 0);
}

void playRotateBlockSound(void)
{
    playSound(rotateBlockSoundPlayer, 1);
}

void playElfSound(void)
{
    playSound(elfSoundPlayer, 1);
}

void playStageEndSound(void)
{
    playSound(stageEndSoundPlayer, 1);
}

void playBridgeSound(void)
{
    playSound(bridgeSoundPlayer, 1);
}

void playErrorSound(void)
{
    playSound(errorSoundPlayer, 1);
}

void playMenuSelectSound(void)
{
    playSound(menuSelectSoundPlayer, 1);
}

void playFlipBlockSound(void)
{
    playSound(flipBlockSoundPlayer, 1);
}

void playPickupBlockSound(void)
{
    playSound(pickupBlockSoundPlayer, 1);
}

void playDropBlockSound(void)
{
    playSound(dropBlockSoundPlayer, 1);
}

void playMenuSound(void)
{
    playSound(menuSoundPlayer, 1);
}
