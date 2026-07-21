// lighting.cpp
#include "lighting.h"
#include <iostream>
#include <cmath>  // TAMBAHKAN INI untuk sin dan cos

static bool nightMode = false;
static float lightAngle = 0.0f;

// lighting.cpp
void initLighting() {
    // ===== AMBIENT LIGHT (Cahaya dasar yang terang) =====
    GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 1.0f};  // DITINGKATKAN
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    // ===== LIGHT 0 - Cahaya utama dari atas =====
    GLfloat lightPos0[] = {0.0f, 20.0f, 0.0f, 1.0f};
    GLfloat diffuse0[] = {1.0f, 1.0f, 1.0f, 1.0f};  // TERANG
    GLfloat specular0[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glEnable(GL_LIGHT0);
    
    // ===== LIGHT 1 - Cahaya dari samping =====
    GLfloat lightPos1[] = {15.0f, 10.0f, 15.0f, 1.0f};
    GLfloat diffuse1[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glEnable(GL_LIGHT1);
    
    // ===== LIGHT 2 - Cahaya dari belakang =====
    GLfloat lightPos2[] = {-15.0f, 10.0f, -15.0f, 1.0f};
    GLfloat diffuse2[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    glEnable(GL_LIGHT2);
    
    // ===== ENABLE LIGHTING =====
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // Material properties
    GLfloat matSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat matShininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    
    std::cout << "Lighting initialized" << std::endl;
}

void setupLighting() {
    if (nightMode) {
        GLfloat ambientLight[] = {0.05f, 0.05f, 0.1f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        
        GLfloat diffuse0[] = {0.2f, 0.2f, 0.3f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        
        GLfloat diffuse1[] = {0.15f, 0.15f, 0.3f, 1.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    } else {
        GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        
        GLfloat diffuse0[] = {0.8f, 0.8f, 0.8f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        
        GLfloat diffuse1[] = {0.6f, 0.6f, 0.8f, 1.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    }
}

void updateLighting(float deltaTime) {
    lightAngle += deltaTime * 20.0f;
    if (lightAngle > 360.0f) lightAngle -= 360.0f;
    
    float rad = lightAngle * 3.14159f / 180.0f;
    float x = cos(rad) * 5.0f;
    float z = sin(rad) * 5.0f;
    
    GLfloat lightPos1[] = {x, 8.0f, z, 1.0f};
    GLfloat spotDir[] = {-x, -2.0f, -z};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
}

void toggleNightMode() {
    nightMode = !nightMode;
    std::cout << "Night Mode: " << (nightMode ? "ON" : "OFF") << std::endl;
}

bool getNightModeStatus() { return nightMode; }