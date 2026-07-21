// main.cpp
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

#include "camera.h"
#include "lighting.h"
#include "textures.h"
#include "objects.h"
#include "animations.h"
#include "interactions.h"
#include "museum_layout.h"
#include "sound.h"
#include "ui.h"
#include "floor2.h"

// ==================== VARIABEL GLOBAL ====================
int currentScene = 0;
bool isRunning = true;
bool isPaused = false;
float deltaTime = 0.016f;
int lastTime = 0;
int fps = 0;
int frameCount = 0;
float fpsTimer = 0;
bool keys[256] = {false};

int selectedArea = 0;
const char* areas[] = {"Main Hall", "Trophy Room", "Wall of Fame", "Timeline", "Souvenir"};

// Window size
int windowWidth = 1024;
int windowHeight = 768;

// ==================== DEKLARASI FUNGSI ====================
void initGL();
void renderScene();
void renderHUD();
void renderMenu();
void updateScene();
void reshape(int w, int h);
void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void timer(int value);
void idle();
void focusOnCollection();
void teleportToArea(int area);

// ==================== IMPLEMENTASI FUNGSI ====================

void initGL() {
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glViewport(0, 0, windowWidth, windowHeight);
    
    initTextures();
    initLighting();
    initCamera();
    initAnimations();
    initInteractions();
    initMuseumLayout();
    
    currentScene = 0;
    resetCamera();
    
    std::cout << "========================================" << std::endl;
    std::cout << "  MUSEUM VIRTUAL 3D CR7 - MADEIRA" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Press H or F1 for Help" << std::endl;
    std::cout << "Press E to Enter Museum" << std::endl;
    std::cout << "Press M to toggle Sound" << std::endl;
    std::cout << "Press B to toggle Floor 2" << std::endl;
    std::cout << "========================================" << std::endl;
}

void renderHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background HUD - Top Bar
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0, windowHeight - 70);
    glVertex2f(windowWidth, windowHeight - 70);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();
    
    // Title
    glColor3f(1.0f, 0.8f, 0.2f);
    glRasterPos2f(20, windowHeight - 30);
    std::string title = "MUSEUM VIRTUAL 3D CR7 - MADEIRA";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Scene info
    glColor3f(0.7f, 0.9f, 1.0f);
    glRasterPos2f(windowWidth - 250, windowHeight - 30);
    std::string scene = "Scene: " + std::string(currentScene == 0 ? "EXTERIOR" : "INTERIOR");
    for (char c : scene) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Camera mode
    glColor3f(0.5f, 1.0f, 0.5f);
    glRasterPos2f(20, windowHeight - 55);
    std::string cam = "Camera: " + getCameraModeString();
    for (char c : cam) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Night mode status
    glColor3f(0.8f, 0.8f, 1.0f);
    glRasterPos2f(windowWidth - 180, windowHeight - 55);
    std::string night = "Night Mode: " + std::string(getNightModeStatus() ? "ON" : "OFF");
    for (char c : night) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Floor status
    glColor3f(0.8f, 1.0f, 0.8f);
    glRasterPos2f(windowWidth - 350, windowHeight - 55);
    std::string floor = "Floor: " + std::string(onFloor2 ? "2" : "1");
    for (char c : floor) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // FPS
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(windowWidth - 80, 20);
    std::string fpsStr = "FPS: " + std::to_string(fps);
    for (char c : fpsStr) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Pause indicator
    if (isPaused) {
        glColor3f(1.0f, 0.2f, 0.2f);
        glRasterPos2f(windowWidth/2 - 50, windowHeight/2);
        std::string pause = "PAUSED";
        for (char c : pause) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderMenu() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background menu - Bottom Left
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(10, 10);
    glVertex2f(210, 10);
    glVertex2f(210, 150);
    glVertex2f(10, 150);
    glEnd();
    
    glColor3f(0.8f, 0.8f, 0.8f);
    glRasterPos2f(15, 140);
    std::string controls = "CONTROLS:";
    for (char c : controls) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glColor3f(0.6f, 0.6f, 0.6f);
    glRasterPos2f(15, 125);
    std::string w = "WASD - Move";
    for (char c : w) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 110);
    std::string m = "Mouse - Look";
    for (char c : m) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 95);
    std::string e = "E - Enter/Exit";
    for (char c : e) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 80);
    std::string t = "T - Night Mode";
    for (char c : t) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 65);
    std::string sp = "Space - Celebrate!";
    for (char c : sp) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 50);
    std::string b = "B - Floor 2";
    for (char c : b) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 35);
    std::string m2 = "M - Sound";
    for (char c : m2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 20);
    std::string h = "H - Help";
    for (char c : h) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    setupCamera();
    setupLighting();
    
    if (currentScene == 0) {
        renderExterior();
    } else {
        renderInterior();
        if (onFloor2) {
            renderFloor2();
        }
    }
    
    renderAnimations();
    renderUI();
    renderHUD();
    renderMenu();
    
    glutSwapBuffers();
}

void updateScene() {
    if (isPaused) return;
    
    // Handle continuous key presses
    if (keys['w'] || keys['W']) {
        moveCamera(FORWARD, deltaTime);
    }
    if (keys['s'] || keys['S']) {
        moveCamera(BACKWARD, deltaTime);
    }
    if (keys['a']) {
        moveCamera(LEFT, deltaTime);
    }
    if (keys['d']) {
        moveCamera(RIGHT, deltaTime);
    }
    
    updateDoorAnimation(deltaTime);
    updateAnimations(deltaTime);
    updateInteractions(deltaTime);
    updateCamera(deltaTime);
    updateLighting(deltaTime);
    updateUI(deltaTime);
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    
    if (isPaused && key != 27) return;
    
    switch (key) {
        case 27: // ESC
            togglePause();
            isPaused = !isPaused;
            break;
            
        case 'h':
        case 'H':
            showHelp();
            break;
            
        case '1':
            setCameraMode(CAM_FIRST_PERSON);
            std::cout << "Camera: First Person" << std::endl;
            break;
            
        case '2':
            setCameraMode(CAM_ORBIT);
            std::cout << "Camera: Orbit" << std::endl;
            break;
            
        case '3':
            setCameraMode(CAM_FREE_FLY);
            std::cout << "Camera: Free Fly" << std::endl;
            break;
            
        case 'e':
        case 'E':
            if (currentScene == 0) {
                currentScene = 1;
                std::cout << ">>> Entering Museum..." << std::endl;
                resetCamera();
            } else {
                currentScene = 0;
                std::cout << ">>> Exiting Museum..." << std::endl;
                resetCamera();
            }
            break;
            
        case 'q':
        case 'Q':
            if (currentScene == 1) {
                currentScene = 0;
                std::cout << ">>> Exiting Museum..." << std::endl;
                resetCamera();
            }
            break;
            
        case 'a':
        case 'A':
            toggleAutoTour();
            break;
            
        case 't':
        case 'T':
            toggleNightMode();
            break;
            
        case 'r':
        case 'R':
            resetCamera();
            std::cout << "Camera Reset" << std::endl;
            break;
            
        case ' ':
            triggerCelebration();
            std::cout << ">>> CELEBRATION! SIUUU!" << std::endl;
            break;
            
        case 'f':
        case 'F':
            glutFullScreen();
            break;
            
        case 'm':
        case 'M':
            toggleSound();
            showNotification(isSoundEnabled() ? "Sound ON" : "Sound OFF", 1.5f);
            break;
            
        case 'v':
        case 'V':
            toggleSettings();
            break;
            
        case 'b':
        case 'B':
            onFloor2 = !onFloor2;
            showNotification(onFloor2 ? "Floor 2" : "Floor 1", 1.5f);
            break;
            
        default:
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            showHelp();
            break;
            
        case GLUT_KEY_F2:
            toggleAutoTour();
            break;
            
        case GLUT_KEY_F3:
            toggleNightMode();
            break;
            
        case GLUT_KEY_F4:
            isPaused = !isPaused;
            break;
            
        case GLUT_KEY_F5:
            resetCamera();
            break;
            
        case GLUT_KEY_F11:
            glutFullScreen();
            break;
            
        case GLUT_KEY_UP:
            if (getCurrentCameraMode() == CAM_FREE_FLY) {
                moveCamera(UP, deltaTime);
            }
            break;
            
        case GLUT_KEY_DOWN:
            if (getCurrentCameraMode() == CAM_FREE_FLY) {
                moveCamera(DOWN, deltaTime);
            }
            break;
            
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    handleMouseClick(button, state, x, y);
}

void motion(int x, int y) {
    handleMouseMotion(x, y);
}

void timer(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentTime - lastTime) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    lastTime = currentTime;
    
    frameCount++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0f) {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = 0;
    }
    
    updateScene();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void idle() {
    glutPostRedisplay();
}

void focusOnCollection() {
    showNotification("Focusing on collection...", 1.5f);
}

void teleportToArea(int area) {
    showNotification("Teleported to " + std::string(areas[area]), 1.5f);
}

// ==================== MAIN ====================

int main(int argc, char** argv) {
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("MUSEUM VIRTUAL 3D CR7 - MADEIRA");
    
    initGL();
    initSound();
    initUI();
    initFloor2();
    playBackgroundMusic();
    showNotification("Welcome to Museum CR7 - Madeira!", 3.0f);
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glutIdleFunc(idle);
    glutTimerFunc(16, timer, 0);
    
    glutMainLoop();
    return 0;
}