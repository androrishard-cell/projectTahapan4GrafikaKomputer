// sound.cpp
#include "sound.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <cstdlib>

#pragma comment(lib, "winmm.lib")

static bool soundEnabled = true;
static float volume = 1.0f;
static bool bgMusicPlaying = false;

void initSound() {
    std::cout << "Sound system initialized" << std::endl;
}

void playDoorOpen() {
    if (!soundEnabled) return;
    // Gunakan Beep sebagai placeholder (atau PlaySound untuk file WAV)
    // Untuk demo, kita gunakan Beep
    // Beep(600, 100);
    std::cout << "🔊 Door Open" << std::endl;
}

void playDoorClose() {
    if (!soundEnabled) return;
    // Beep(400, 100);
    std::cout << "🔊 Door Close" << std::endl;
}

void playFootstep() {
    if (!soundEnabled) return;
    // Beep(200, 20);
}

void playCelebration() {
    if (!soundEnabled) return;
    // Play suara SIUUU
    std::cout << "🔊 SIUUUUU!!!" << std::endl;
    // Beep(800, 200);
    // Beep(1000, 200);
    // Beep(1200, 300);
}

void playBackgroundMusic() {
    if (!soundEnabled || bgMusicPlaying) return;
    bgMusicPlaying = true;
    std::cout << "🔊 Background Music ON" << std::endl;
    // Untuk memutar file WAV:
    // PlaySound("assets/sounds/bg_music.wav", NULL, SND_ASYNC | SND_LOOP);
}

void stopBackgroundMusic() {
    if (!bgMusicPlaying) return;
    bgMusicPlaying = false;
    std::cout << "🔊 Background Music OFF" << std::endl;
    // PlaySound(NULL, NULL, 0);
}

void toggleSound() {
    soundEnabled = !soundEnabled;
    if (!soundEnabled) {
        stopBackgroundMusic();
    } else {
        playBackgroundMusic();
    }
    std::cout << "Sound: " << (soundEnabled ? "ON" : "OFF") << std::endl;
}

void setVolume(float vol) {
    volume = vol;
    if (volume < 0) volume = 0;
    if (volume > 1) volume = 1;
    std::cout << "Volume: " << (int)(volume * 100) << "%" << std::endl;
}

bool isSoundEnabled() {
    return soundEnabled;
}

void cleanupSound() {
    stopBackgroundMusic();
}