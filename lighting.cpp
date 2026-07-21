// lighting.cpp
#include "lighting.h"
#include <iostream>

static bool nightMode = false;
static float lightAngle = 0.0f;

void initLighting() {
    // Ambient light
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    // Light 0 - Main light (diffuse + specular)
    GLfloat lightPos0[] = {5.0f, 10.0f, 5.0f, 1.0f};
    GLfloat diffuse0[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat specular0[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glEnable(GL_LIGHT0);
    
    // Light 1 - Spotlight
    GLfloat lightPos1[] = {-3.0f, 8.0f, 0.0f, 1.0f};
    GLfloat spotDir[] = {1.0f, -1.0f, 0.0f};
    GLfloat diffuse1[] = {0.6f, 0.6f, 0.8f, 1.0f};
    GLfloat specular1[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);
    glEnable(GL_LIGHT1);
    
    // Light 2 - Fill light
    GLfloat lightPos2[] = {-5.0f, 5.0f, -5.0f, 1.0f};
    GLfloat diffuse2[] = {0.3f, 0.3f, 0.4f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    glEnable(GL_LIGHT2);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    std::cout << "Lighting initialized" << std::endl;
}

void setupLighting() {
    if (nightMode) {
        // Night mode - reduce ambient and diffuse
        GLfloat ambientLight[] = {0.05f, 0.05f, 0.1f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        
        GLfloat diffuse0[] = {0.2f, 0.2f, 0.3f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        
        GLfloat diffuse1[] = {0.15f, 0.15f, 0.3f, 1.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    } else {
        // Day mode
        GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        
        GLfloat diffuse0[] = {0.8f, 0.8f, 0.8f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        
        GLfloat diffuse1[] = {0.6f, 0.6f, 0.8f, 1.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    }
}

void updateLighting(float deltaTime) {
    // Move spotlight
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