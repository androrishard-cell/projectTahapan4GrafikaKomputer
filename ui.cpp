// ui.cpp
#include "ui.h"
#include "camera.h"
#include "museum_layout.h"
#include "sound.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // TAMBAHKAN INI untuk remove_if

using namespace std;

static vector<Notification> notifications;
static bool settingsOpen = false;
static bool loadingComplete = false;
static float loadingProgress = 0.0f;
static int selectedOption = 0;

// Kontrol hints
static ControlHint controls[] = {
    {"WASD", "Move", 10, 80},
    {"Mouse", "Look", 10, 60},
    {"E", "Enter/Exit", 10, 40},
    {"Q", "Exit (Interior)", 10, 20},
    {"A", "Auto Tour", 10, 0},
    {"T", "Night Mode", 10, -20},
    {"Space", "Celebration!", 10, -40},
    {"R", "Reset Camera", 10, -60},
    {"H/F1", "Help", 10, -80},
    {"ESC", "Pause", 10, -100}
};

void initUI() {
    loadingProgress = 0.0f;
    loadingComplete = false;
    cout << "UI initialized" << endl;
}

void showNotification(const string& text, float duration) {
    Notification notif;
    notif.text = text;
    notif.timer = duration;
    notif.maxTimer = duration;
    notif.active = true;
    notifications.push_back(notif);
    cout << "📢 " << text << endl;
}

void updateUI(float deltaTime) {
    // Update loading
    if (!loadingComplete && loadingProgress < 1.0f) {
        loadingProgress += deltaTime * 0.5f;
        if (loadingProgress >= 1.0f) {
            loadingProgress = 1.0f;
            loadingComplete = true;
            showNotification("Welcome to Museum CR7!", 3.0f);
        }
    }
    
    // Update notifications
    for (auto& notif : notifications) {
        if (notif.active) {
            notif.timer -= deltaTime;
            if (notif.timer <= 0) {
                notif.active = false;
            }
        }
    }
    
    // Hapus notifikasi yang sudah tidak aktif
    notifications.erase(
        remove_if(notifications.begin(), notifications.end(),
            [](const Notification& n) { return !n.active; }),
        notifications.end()
    );
}

void renderMiniMap() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background minimap
    glColor4f(0, 0, 0, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(870, 10);
    glVertex2f(1010, 10);
    glVertex2f(1010, 150);
    glVertex2f(870, 150);
    glEnd();
    
    // Border
    glColor4f(0.5f, 0.5f, 0.5f, 0.8f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(870, 10);
    glVertex2f(1010, 10);
    glVertex2f(1010, 150);
    glVertex2f(870, 150);
    glEnd();
    
    // Label
    glColor4f(1, 1, 1, 1);
    glRasterPos2f(875, 140);
    string label = "MINIMAP";
    for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Simbol player
    glColor4f(0, 1, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(935, 75);
    glVertex2f(945, 75);
    glVertex2f(945, 85);
    glVertex2f(935, 85);
    glEnd();
    
    // Titik objek
    glColor4f(0.8f, 0.8f, 0.8f, 0.5f);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(900, 30); // Trofi
    glVertex2f(950, 30); // Wall of Fame
    glVertex2f(980, 30); // Timeline
    glVertex2f(900, 60); // Souvenir
    glVertex2f(950, 60); // Exit
    glEnd();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderControlsHelp() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background
    glColor4f(0, 0, 0, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(10, 10);
    glVertex2f(200, 10);
    glVertex2f(200, 300);
    glVertex2f(10, 300);
    glEnd();
    
    // Title
    glColor4f(1, 0.8f, 0.2f, 1);
    glRasterPos2f(15, 290);
    string title = "CONTROLS:";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    // Controls
    glColor4f(0.8f, 0.8f, 0.8f, 1);
    int yPos = 270;
    for (int i = 0; i < 10; i++) {
        glRasterPos2f(15, yPos);
        string text = controls[i].key + " - " + controls[i].action;
        for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        yPos -= 20;
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderNotifications() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    int yPos = 700;
    for (const auto& notif : notifications) {
        if (!notif.active) continue;
        
        float alpha = 1.0f;
        if (notif.timer < 0.5f) {
            alpha = notif.timer / 0.5f;
        }
        
        glColor4f(0, 0, 0, 0.6f * alpha);
        glBegin(GL_QUADS);
        glVertex2f(10, yPos - 5);
        glVertex2f(500, yPos - 5);
        glVertex2f(500, yPos + 25);
        glVertex2f(10, yPos + 25);
        glEnd();
        
        glColor4f(1, 1, 0.5f, alpha);
        glRasterPos2f(20, yPos + 5);
        for (char c : notif.text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        
        yPos -= 35;
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderLoadingScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background
    glColor4f(0.1f, 0.1f, 0.15f, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1024, 0);
    glVertex2f(1024, 768);
    glVertex2f(0, 768);
    glEnd();
    
    // Title - Ganti GLUT_BITMAP_HELVETICA_24 dengan 18
    glColor4f(1, 0.8f, 0.2f, 1);
    glRasterPos2f(250, 450);
    string title = "MUSEUM VIRTUAL 3D CR7 - MADEIRA";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Loading text
    glColor4f(1, 1, 1, 1);
    glRasterPos2f(430, 350);
    string loading = "LOADING...";
    for (char c : loading) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Progress bar background
    glColor4f(0.3f, 0.3f, 0.3f, 1);
    glBegin(GL_QUADS);
    glVertex2f(300, 300);
    glVertex2f(724, 300);
    glVertex2f(724, 330);
    glVertex2f(300, 330);
    glEnd();
    
    // Progress bar
    glColor4f(1, 0.8f, 0.2f, 1);
    glBegin(GL_QUADS);
    glVertex2f(300, 300);
    glVertex2f(300 + 424 * loadingProgress, 300);
    glVertex2f(300 + 424 * loadingProgress, 330);
    glVertex2f(300, 330);
    glEnd();
    
    // Percentage
    glColor4f(1, 1, 1, 1);
    glRasterPos2f(490, 280);
    string percent = to_string((int)(loadingProgress * 100)) + "%";
    for (char c : percent) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderSettingsMenu() {
    if (!settingsOpen) return;
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background overlay
    glColor4f(0, 0, 0, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1024, 0);
    glVertex2f(1024, 768);
    glVertex2f(0, 768);
    glEnd();
    
    // Settings panel
    glColor4f(0.2f, 0.2f, 0.3f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(262, 134);
    glVertex2f(762, 134);
    glVertex2f(762, 634);
    glVertex2f(262, 634);
    glEnd();
    
    // Border
    glColor4f(0.5f, 0.5f, 0.5f, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(262, 134);
    glVertex2f(762, 134);
    glVertex2f(762, 634);
    glVertex2f(262, 634);
    glEnd();
    
    // Title - Ganti 24 dengan 18
    glColor4f(1, 0.8f, 0.2f, 1);
    glRasterPos2f(380, 600);
    string title = "SETTINGS";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Options
    const char* options[] = {
        "Sound: ",
        "Volume: ",
        "Brightness: ",
        "Mouse Sensitivity: ",
        "Controls",
        "Back"
    };
    
    int yPos = 540;
    for (int i = 0; i < 6; i++) {
        if (i == selectedOption) {
            glColor4f(1, 0.8f, 0.2f, 1);
        } else {
            glColor4f(0.8f, 0.8f, 0.8f, 1);
        }
        glRasterPos2f(300, yPos);
        string text = options[i];
        if (i == 0) text += isSoundEnabled() ? "ON" : "OFF";
        if (i == 1) text += "50%";
        if (i == 2) text += "70%";
        if (i == 3) text += "0.15";
        // Ganti GLUT_BITMAP_HELVETICA_14 dengan 12
        for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        yPos -= 50;
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderUI() {
    if (!loadingComplete) {
        renderLoadingScreen();
        return;
    }
    
    renderMiniMap();
    renderControlsHelp();
    renderNotifications();
    renderSettingsMenu();
}

void toggleSettings() {
    settingsOpen = !settingsOpen;
    if (settingsOpen) {
        showNotification("Settings Opened", 1.5f);
    }
}

bool isSettingsOpen() {
    return settingsOpen;
}