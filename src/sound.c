#include <stdint.h>
#include <string.h>
#include "sound.h"
#include "pd_api.h"
#include "commonvars.h"

int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

FilePlayer* musicPlayer;

SamplePlayer* SelectSoundPlayer;
SamplePlayer* GoodSoundPlayer;
SamplePlayer* WrongSoundPlayer;
SamplePlayer* StartSoundPlayer;
SamplePlayer* WinnerSoundPlayer;
SamplePlayer* LoserSoundPlayer;

AudioSample* SelectSound;
AudioSample* GoodSound;
AudioSample* WrongSound;
AudioSample* StartSound;
AudioSample* WinnerSound;
AudioSample* LoserSound;

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
    SelectSoundPlayer = loadSoundFile(SelectSound, "sounds/select");
    GoodSoundPlayer = loadSoundFile(GoodSound, "sounds/good");
    WrongSoundPlayer = loadSoundFile(WrongSound, "sounds/wrong");
    StartSoundPlayer = loadSoundFile(StartSound, "sounds/start");
    WinnerSoundPlayer = loadSoundFile(WinnerSound, "sounds/winner");
    LoserSoundPlayer = loadSoundFile(LoserSound, "sounds/loser");
}

void deInitSound(void)
{
    FreeSample(SelectSound);
    FreeSample(GoodSound);
    FreeSample(WrongSound);
    FreeSample(StartSound);
    FreeSample(WinnerSound);
    FreeSample(LoserSound);


    FreeSoundPlayer(SelectSoundPlayer);
    FreeSoundPlayer(GoodSoundPlayer);
    FreeSoundPlayer(WrongSoundPlayer);
    FreeSoundPlayer(StartSoundPlayer);
    FreeSoundPlayer(WinnerSoundPlayer);
    FreeSoundPlayer(LoserSoundPlayer);
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
                playMusicFile("music/rubido", 0);
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


void playSelectSound(void)
{
    playSound(SelectSoundPlayer, 1);
}

void playGoodSound(void)
{
    playSound(GoodSoundPlayer, 1);
}

void playWrongSound(void)
{
    playSound(WrongSoundPlayer, 1);
}

void playStartSound(void)
{
    playSound(StartSoundPlayer, 1);
}

void playWinnerSound(void)
{
    playSound(WinnerSoundPlayer, 1);
}

void playLoserSound(void)
{
    playSound(LoserSoundPlayer, 1);
}
