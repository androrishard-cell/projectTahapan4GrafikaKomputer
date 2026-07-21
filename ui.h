// ui.h
#ifndef UI_H
#define UI_H

#include <GL/glut.h>
#include <string>
#include <vector>

struct Notification {
    std::string text;
    float timer;
    float maxTimer;
    bool active;
};

struct ControlHint {
    std::string key;
    std::string action;
    float x, y;
};

extern void initUI();
extern void renderUI();
extern void updateUI(float deltaTime);
extern void showNotification(const std::string& text, float duration = 2.0f);
extern void renderControlsHelp();
extern void renderMiniMap();
extern void renderLoadingScreen();
extern void renderSettingsMenu();
extern void toggleSettings();
extern bool isSettingsOpen();

#endif