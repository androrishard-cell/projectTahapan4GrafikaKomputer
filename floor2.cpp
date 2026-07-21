// floor2.cpp
#include "floor2.h"
#include "objects.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

bool onFloor2 = false;
static float stairAnimation = 0.0f;

void initFloor2() {
    std::cout << "Floor 2 initialized" << std::endl;
}

bool isOnFloor2() {
    return onFloor2;
}

void setOnFloor2(bool value) {
    onFloor2 = value;
}

void renderStairs(float x, float y, float z) {
    int numSteps = 10;
    float stepWidth = 1.5f;
    float stepHeight = 0.2f;
    float stepDepth = 0.3f;
    
    for (int i = 0; i < numSteps; i++) {
        glPushMatrix();
        glTranslatef(x + i * stepDepth, y + i * stepHeight, z);
        glScalef(stepWidth, stepHeight, stepDepth);
        bindTexture(TEXTURE_MARBLE);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
}

void renderExhibitionRoom() {
    // Lantai
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(8, 0.05f, 8);
    bindTexture(TEXTURE_PAVEMENT);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Dinding
    glPushMatrix();
    glTranslatef(0, 2.5f, -4);
    glScalef(8, 5, 0.2f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-4, 2.5f, 0);
    glScalef(0.2f, 5, 8);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4, 2.5f, 0);
    glScalef(0.2f, 5, 8);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Plafon
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(8, 0.1f, 8);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Pajangan di dinding
    for (int i = -3; i <= 3; i++) {
        glPushMatrix();
        glTranslatef(i * 0.8f, 2.5f, -3.8f);
        glScalef(0.5f, 0.7f, 0.02f);
        bindTexture(TEXTURE_PHOTO);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // Lampu
    glPushMatrix();
    glTranslatef(0, 4.8f, 0);
    drawChandelier();
    glPopMatrix();
}

void renderCafe() {
    // Lantai
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(6, 0.05f, 6);
    bindTexture(TEXTURE_PAVEMENT);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Meja
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * 1.5f, 0.5f, j * 1.5f);
            glScalef(0.8f, 0.05f, 0.8f);
            bindTexture(TEXTURE_WOOD);
            drawCube(1, 1, 1);
            glPopMatrix();
            
            // Kursi
            glPushMatrix();
            glTranslatef(i * 1.5f + 0.6f, 0.3f, j * 1.5f);
            glScalef(0.3f, 0.3f, 0.3f);
            bindTexture(TEXTURE_METAL);
            drawCube(1, 1, 1);
            glPopMatrix();
        }
    }
    
    // Counter
    glPushMatrix();
    glTranslatef(-2.5f, 0.5f, 0);
    glScalef(1.5f, 0.5f, 2);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Lampu gantung kecil
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(i * 2.0f, 4.8f, 0);
        glScalef(0.3f, 0.2f, 0.3f);
        glColor4f(1.0f, 0.9f, 0.5f, 0.8f);
        drawSphere(0.5f, 8, 8);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
}

void renderFloor2() {
    if (!onFloor2) return;
    
    // Render ruang pameran
    glPushMatrix();
    glTranslatef(-2.5f, 0, 0);
    renderExhibitionRoom();
    glPopMatrix();
    
    // Render kafe
    glPushMatrix();
    glTranslatef(3.5f, 0, 0);
    renderCafe();
    glPopMatrix();
    
    // Tangga
    glPushMatrix();
    glTranslatef(0, 0, 4);
    renderStairs(0, 0, 0);
    glPopMatrix();
}