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

// ==================== KONSTANTA ====================
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Museum Virtual 3D CR7 - Madeira";

// ==================== VARIABEL GLOBAL ====================
int currentScene = 1;        // 0: Exterior, 1: Interior
bool isRunning = true;
bool isPaused = false;
float deltaTime = 0.016f;
int lastTime = 0;
int fps = 0;
int frameCount = 0;
float fpsTimer = 0;

// Variabel untuk keyboard state
bool keys[256] = {false};
bool isNightMode = false;

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

// ==================== INISIALISASI ====================

// main.cpp - initGL()
void initGL() {
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // ===== INIT TEXTURE =====
    initTextures();
    
    // ===== INIT LIGHTING (PASTIKAN INI DIPANGGIL) =====
    initLighting();  // <-- HARUS ADA
    
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
    std::cout << "========================================" << std::endl;
}

// ==================== RENDER UTAMA ====================

// main.cpp - Di bagian atas
#include "museum_layout.h"  // Pastikan ini sudah ada

// Di dalam renderScene(), pastikan currentScene berfungsi:
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    setupCamera();
    setupLighting();
    
    if (currentScene == 0) {
        renderExterior();
    } else {
        renderInterior();
    }
    
    renderAnimations();
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
    
    // Background HUD - Top Bar
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
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
    glRasterPos2f(WINDOW_WIDTH - 250, WINDOW_HEIGHT - 30);
    std::string scene = "Scene: " + std::string(currentScene == 0 ? "EXTERIOR" : "INTERIOR");
    for (char c : scene) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    
    // Camera mode
    glColor3f(0.5f, 1.0f, 0.5f);
    glRasterPos2f(20, WINDOW_HEIGHT - 55);
    std::string cam = "Camera: " + getCameraModeString();
    for (char c : cam) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Night mode status
    glColor3f(0.8f, 0.8f, 1.0f);
    glRasterPos2f(WINDOW_WIDTH - 180, WINDOW_HEIGHT - 55);
    std::string night = "Night Mode: " + std::string(getNightModeStatus() ? "ON" : "OFF");
    for (char c : night) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
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
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Background menu - Bottom Left
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(10, 10);
    glVertex2f(200, 10);
    glVertex2f(200, 130);
    glVertex2f(10, 130);
    glEnd();
    
    glColor3f(0.8f, 0.8f, 0.8f);
    glRasterPos2f(15, 120);
    std::string controls = "CONTROLS:";
    for (char c : controls) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glColor3f(0.6f, 0.6f, 0.6f);
    glRasterPos2f(15, 105);
    std::string w = "WASD - Move";
    for (char c : w) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 90);
    std::string m = "Mouse - Look";
    for (char c : m) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 75);
    std::string e = "E - Enter/Exit Museum";
    for (char c : e) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 60);
    std::string q = "Q - Exit (Interior)";
    for (char c : q) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 45);
    std::string a = "A - Auto Tour";
    for (char c : a) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 30);
    std::string t = "T - Night Mode";
    for (char c : t) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    glRasterPos2f(15, 15);
    std::string sp = "Space - Celebration!";
    for (char c : sp) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// ==================== UPDATE SCENE ====================

// main.cpp - Tambahkan di bagian updateScene()

void updateScene() {
    if (isPaused) return;
    
    // Handle continuous key presses
    if (keys['w'] || keys['W']) moveCamera(FORWARD, deltaTime);
    if (keys['s'] || keys['S']) moveCamera(BACKWARD, deltaTime);
    if (keys['a']) moveCamera(LEFT, deltaTime);
    if (keys['d']) moveCamera(RIGHT, deltaTime);
    
    // ===== UPDATE ANIMASI PINTU =====
    updateDoorAnimation(deltaTime);
    
    // ===== CEK JIKA PLAYER DEKAT DENGAN PINTU DAN PINTU TERBUKA =====
    // Jika pintu terbuka dan player di depan pintu, bisa masuk
    // (Optional: Auto-enter jika pintu terbuka dan player mendekat)
    
    updateAnimations(deltaTime);
    updateInteractions(deltaTime);
    updateCamera(deltaTime);
    updateLighting(deltaTime);
}

// ==================== TIMER & IDLE ====================

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

// ==================== CALLBACK FUNGSI ====================

void reshape(int w, int h) {
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
            // ===== LOGIKA PINTU DAN MASUK MUSEUM =====
            if (currentScene == 0) {
                // Di EXTERIOR - Buka/Tutup pintu
                toggleDoor();
                if (doorOpen) {
                    std::cout << ">>> Door is OPEN! Press E again to enter..." << std::endl;
                } else {
                    std::cout << ">>> Door is CLOSED!" << std::endl;
                }
            } else {
                // Di INTERIOR - Keluar museum
                currentScene = 0;
                doorOpen = false;
                doorAnimation = 0.0f;
                std::cout << ">>> Exiting Museum..." << std::endl;
                resetCamera();
            }
            break;
            
        case 'q':
        case 'Q':
            if (currentScene == 1) {
                currentScene = 0;
                doorOpen = false;
                doorAnimation = 0.0f;
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