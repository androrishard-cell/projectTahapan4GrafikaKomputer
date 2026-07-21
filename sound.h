// sound.h
#ifndef SOUND_H
#define SOUND_H

#include <string>

// Forward declaration
struct SoundData;

extern void initSound();
extern void playDoorOpen();
extern void playDoorClose();
extern void playFootstep();
extern void playCelebration();
extern void playBackgroundMusic();
extern void stopBackgroundMusic();
extern void toggleSound();
extern void setVolume(float volume);
extern bool isSoundEnabled();
extern void cleanupSound();

#endif