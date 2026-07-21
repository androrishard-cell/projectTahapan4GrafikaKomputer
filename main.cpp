// main.cpp
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "camera.h"
#include "lighting.h"
#include "textures.h"
#include "objects.h"
#include "animations.h"
#include "interactions.h"
#include "museum_layout.h"

// ==================== KONSTANTA ====================
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Museum Virtual 3D CR7 - Madeira";

// ==================== VARIABEL GLOBAL ====================
int currentScene = 0;        // 0: Exterior, 1: Interior
bool isRunning = true;
bool isPaused = false;
float deltaTime = 0.016f;
int lastTime = 0;
int fps = 0;
int frameCount = 0;
float fpsTimer = 0;

// ==================== DEKLARASI FUNGSI ====================
void initGL();
void renderScene();
void renderHUD();
void renderMenu();
void updateScene();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void timer(int value);
void idle();

// ==================== INISIALISASI ====================

void initGL() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Setup viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Inisialisasi komponen
    initTextures();
    initLighting();
    initCamera();
    initAnimations();
    initInteractions();
    initMuseumLayout();
    
    std::cout << "========================================" << std::endl;
    std::cout << "  MUSEUM VIRTUAL 3D CR7 - MADEIRA" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Press H or F1 for Help" << std::endl;
    std::cout << "========================================" << std::endl;
}

// ==================== RENDER UTAMA ====================

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Setup kamera
    setupCamera();
    
    // Setup pencahayaan
    setupLighting();
    
    // Render berdasarkan scene
    if (currentScene == 0) {
        renderExterior();
    } else {
        renderInterior();
    }
    
    // Render animasi
    renderAnimations();
    
    // Render interaksi & HUD
    renderHUD();
    renderMenu();
    
    glutSwapBuffers();
}

// ==================== RENDER HUD ====================

void renderHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background HUD
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    // Top bar
    glVertex2f(0, WINDOW_HEIGHT - 70);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT - 70);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT);
    glEnd();
    
    // Title
    glColor3f(1.0f, 0.8f, 0.2f);
    glRasterPos2f(20, WINDOW_HEIGHT - 30);
    std::string title = "MUSEUM VIRTUAL 3D CR7 - MADEIRA";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Scene info
    glColor3f(0.7f, 0.9f, 1.0f);
    glRasterPos2f(WINDOW_WIDTH - 300, WINDOW_HEIGHT - 30);
    std::string scene = "Scene: " + std::string(currentScene == 0 ? "EXTERIOR" : "INTERIOR");
    for (char c : scene) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Camera mode
    glColor3f(0.5f, 1.0f, 0.5f);
    glRasterPos2f(20, WINDOW_HEIGHT - 55);
    std::string cam = "Camera: " + getCameraModeString();
    for (char c : cam) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    // Night mode status
    glColor3f(0.8f, 0.8f, 1.0f);
    glRasterPos2f(WINDOW_WIDTH - 180, WINDOW_HEIGHT - 55);
    std::string night = "Night Mode: " + std::string(getNightModeStatus() ? "ON" : "OFF");
    for (char c : night) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    // FPS
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(WINDOW_WIDTH - 80, 20);
    std::string fpsStr = "FPS: " + std::to_string(fps);
    for (char c : fpsStr) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Pause indicator
    if (isPaused) {
        glColor3f(1.0f, 0.2f, 0.2f);
        glRasterPos2f(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT/2);
        std::string pause = "PAUSED";
        for (char c : pause) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_24, c);
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderMenu() {
    // Menu sederhana di pojok kiri bawah
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background menu
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(10, 10);
    glVertex2f(200, 10);
    glVertex2f(200, 110);
    glVertex2f(10, 110);
    glEnd();
    
    // Kontrol
    glColor3f(0.8f, 0.8f, 0.8f);
    glRasterPos2f(15, 95);
    std::string controls = "CONTROLS:";
    for (char c : controls) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glColor3f(0.6f, 0.6f, 0.6f);
    glRasterPos2f(15, 80);
    std::string w = "WASD - Move";
    for (char c : w) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 65);
    std::string m = "Mouse - Look";
    for (char c : m) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 50);
    std::string e = "E - Open Door";
    for (char c : e) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 35);
    std::string h = "H - Help";
    for (char c : h) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 20);
    std::string esc = "ESC - Pause";
    for (char c : esc) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// ==================== UPDATE SCENE ====================

void updateScene() {
    if (isPaused) return;
    
    // Update animasi
    updateAnimations(deltaTime);
    
    // Update interaksi
    updateInteractions(deltaTime);
    
    // Update camera
    updateCamera(deltaTime);
    
    // Update lighting
    updateLighting(deltaTime);
}

// ==================== TIMER & IDLE ====================

void timer(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentTime - lastTime) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    lastTime = currentTime;
    
    // FPS counter
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
    // Nothing to do here, timer handles updates
}

// ==================== CALLBACK FUNGSI ====================

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (isPaused && key != 27) return;
    
    switch (key) {
        case 27: // ESC
            if (isPaused) {
                isPaused = false;
                glutSetCursor(GLUT_CURSOR_INHERIT);
            } else {
                isPaused = true;
                glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
            }
            break;
            
        case 'h':
        case 'H':
            showHelp();
            break;
            
        case '1':
            setCameraMode(CAM_FIRST_PERSON);
            break;
            
        case '2':
            setCameraMode(CAM_ORBIT);
            break;
            
        case '3':
            setCameraMode(CAM_FREE_FLY);
            break;
            
        case 'e':
        case 'E':
            if (currentScene == 0) {
                currentScene = 1;
                std::cout << "Entering Museum..." << std::endl;
            } else {
                currentScene = 0;
                std::cout << "Exiting Museum..." << std::endl;
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
            break;
            
        case ' ':
            triggerCelebration();
            break;
            
        case 'f':
        case 'F':
            glutFullScreenToggle();
            break;
            
        case 'w': case 'W':
            moveCamera(FORWARD, deltaTime);
            break;
            
        case 's': case 'S':
            moveCamera(BACKWARD, deltaTime);
            break;
            
        case 'a':
            moveCamera(LEFT, deltaTime);
            break;
            
        case 'd':
            moveCamera(RIGHT, deltaTime);
            break;
            
        case 'q': case 'Q':
            if (currentScene == 1) {
                currentScene = 0;
                std::cout << "Exiting Museum..." << std::endl;
            }
            break;
            
        default:
            break;
    }
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
            glutFullScreenToggle();
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

// ==================== MAIN ====================

int main(int argc, char** argv) {
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    
    initGL();
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glutIdleFunc(idle);
    glutTimerFunc(16, timer, 0);
    
    glutMainLoop();
    return 0;
}