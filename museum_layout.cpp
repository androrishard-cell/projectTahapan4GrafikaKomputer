// museum_layout.cpp
#include "museum_layout.h"
#include "objects.h"
#include "animations.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>

// ===== DEFINISI VARIABEL GLOBAL =====
float doorAnimation = 0.0f;
bool doorOpen = false;
static float doorSpeed = 2.0f;

void initMuseumLayout() {
    doorAnimation = 0.0f;
    doorOpen = false;
}

// ===== FUNGSI PINTU =====

void toggleDoor() {
    doorOpen = !doorOpen;
    std::cout << "Door: " << (doorOpen ? "OPEN" : "CLOSED") << std::endl;
}

bool isDoorOpen() {
    return doorOpen;
}

void updateDoorAnimation(float deltaTime) {
    if (doorOpen && doorAnimation < 1.0f) {
        doorAnimation += deltaTime * doorSpeed;
        if (doorAnimation > 1.0f) doorAnimation = 1.0f;
    } else if (!doorOpen && doorAnimation > 0.0f) {
        doorAnimation -= deltaTime * doorSpeed;
        if (doorAnimation < 0.0f) doorAnimation = 0.0f;
    }
}

void drawDoor(float x, float y, float z) {
    // ===== BINGKAI PINTU =====
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(4.0f, 5.0f, 0.6f);
    glColor4f(0.6f, 0.5f, 0.4f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PINTU KIRI (BERPUTAR) =====
    glPushMatrix();
    glTranslatef(x - 0.8f, y, z + 0.2f);
    float angle = -doorAnimation * 90.0f;
    glTranslatef(0.8f, 0, 0);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(-0.8f, 0, 0);
    glScalef(1.5f, 4.5f, 0.15f);
    glColor4f(0.4f, 0.25f, 0.15f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PINTU KANAN (BERPUTAR) =====
    glPushMatrix();
    glTranslatef(x + 0.8f, y, z + 0.2f);
    float angle2 = doorAnimation * 90.0f;
    glTranslatef(-0.8f, 0, 0);
    glRotatef(angle2, 0, 1, 0);
    glTranslatef(0.8f, 0, 0);
    glScalef(1.5f, 4.5f, 0.15f);
    glColor4f(0.4f, 0.25f, 0.15f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== HANDLE PINTU (EMAS) =====
    glPushMatrix();
    glTranslatef(x - 0.4f, y, z + 0.5f);
    glScalef(0.08f, 0.3f, 0.08f);
    glColor4f(0.9f, 0.7f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(x + 0.4f, y, z + 0.5f);
    glScalef(0.08f, 0.3f, 0.08f);
    glColor4f(0.9f, 0.7f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}

// ==================== EKSTERIOR MUSEUM ====================

void renderExterior() {
    // ===== SKYBOX =====
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glScalef(80, 40, 80);
    glDisable(GL_LIGHTING);
    glColor4f(0.5f, 0.7f, 1.0f, 1.0f);
    drawCube(1, 1, 1);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ===== GROUND / RUMPUT =====
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(60, 0.2f, 50);
    glColor4f(0.2f, 0.6f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== AREA PLAZA DEPAN =====
    glPushMatrix();
    glTranslatef(0, 0.01f, -3);
    glScalef(20, 0.05f, 8);
    glColor4f(0.8f, 0.7f, 0.5f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== GEDUNG MUSEUM =====
    glPushMatrix();
    glTranslatef(0, 6.0f, 0);
    glScalef(18, 12, 14);
    glColor4f(0.95f, 0.92f, 0.85f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== ATAP =====
    glPushMatrix();
    glTranslatef(0, 12.5f, 0);
    glScalef(19, 0.5f, 15);
    glColor4f(0.7f, 0.65f, 0.6f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== ORNAMEN ATAP =====
    glPushMatrix();
    glTranslatef(0, 12.8f, 7.2f);
    glScalef(16, 0.3f, 1.2f);
    glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PILAR DEPAN =====
    float pillarPos[] = {-6.5f, -4.0f, -1.5f, 1.5f, 4.0f, 6.5f};
    for (int i = 0; i < 6; i++) {
        // Pilar utama
        glPushMatrix();
        glTranslatef(pillarPos[i], 2.0f, 7.0f);
        glScalef(0.6f, 8.0f, 0.6f);
        glColor4f(0.95f, 0.92f, 0.85f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
        
        // Kapital pilar
        glPushMatrix();
        glTranslatef(pillarPos[i], 6.5f, 7.0f);
        glScalef(0.9f, 0.4f, 0.9f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
        
        // Basis pilar
        glPushMatrix();
        glTranslatef(pillarPos[i], 0.3f, 7.0f);
        glScalef(0.8f, 0.4f, 0.8f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== PINTU UTAMA (DENGAN ANIMASI) =====
    drawDoor(0, 2.5f, 7.2f);
    
    // ===== JENDELA LANTAI 1 =====
    float windowX1[] = {-5.5f, -3.5f, 3.5f, 5.5f};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(windowX1[i], 1.5f, 7.2f);
        glScalef(1.2f, 1.8f, 0.05f);
        glColor4f(0.4f, 0.6f, 0.8f, 0.5f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(windowX1[i], 1.5f, 7.25f);
        glScalef(1.4f, 2.0f, 0.02f);
        glColor4f(0.7f, 0.65f, 0.6f, 0.5f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== JENDELA LANTAI 2 =====
    float windowX2[] = {-6.0f, -4.0f, -2.0f, 2.0f, 4.0f, 6.0f};
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(windowX2[i], 4.5f, 7.2f);
        glScalef(1.0f, 1.5f, 0.05f);
        glColor4f(0.4f, 0.6f, 0.8f, 0.4f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== JENDELA LANTAI 3 =====
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(windowX2[i], 7.5f, 7.2f);
        glScalef(1.0f, 1.5f, 0.05f);
        glColor4f(0.4f, 0.6f, 0.8f, 0.4f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== LOGO MUSEUM CR7 =====
    glPushMatrix();
    glTranslatef(0, 8.5f, 7.3f);
    glScalef(6.0f, 1.5f, 0.1f);
    glColor4f(0.8f, 0.2f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 8.5f, 7.4f);
    glScalef(4.0f, 0.8f, 0.02f);
    glColor4f(1.0f, 0.85f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PATUNG CR7 =====
    glPushMatrix();
    glTranslatef(-4.5f, 0.2f, -4.0f);
    glRotatef(getStatueAngle(), 0, 1, 0);
    glScalef(1.2f, 1.2f, 1.2f);
    drawCR7CelebrationPose();
    glPopMatrix();
    
    // ===== POHON =====
    float treePos[][2] = {
        {10, -2}, {-10, -2}, {9, -6}, {-9, -6}, 
        {11, -4}, {-11, -4}, {8, -8}, {-8, -8},
        {12, -1}, {-12, -1}
    };
    for (int i = 0; i < 10; i++) {
        glPushMatrix();
        glTranslatef(treePos[i][0], 0, treePos[i][1]);
        if (i < 4) {
            drawPalmTree(3.0f + (i % 3) * 0.5f);
        } else {
            drawTree(2.5f + (i % 3) * 0.3f, 1.8f + (i % 2) * 0.5f);
        }
        glPopMatrix();
    }
    
    // ===== LAMPU TAMAN =====
    float lampPos[][2] = {{-7, -3}, {7, -3}, {-6, -7}, {6, -7}, {-8, -5}, {8, -5}};
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(lampPos[i][0], 0, lampPos[i][1]);
        drawGardenLamp();
        glPopMatrix();
    }
    
    // ===== BANGKU TAMAN =====
    glPushMatrix();
    glTranslatef(-8, 0, -2);
    drawBench();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8, 0, -2);
    drawBench();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-7.5f, 0, -6);
    drawBench();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.5f, 0, -6);
    drawBench();
    glPopMatrix();
    
    // ===== TAMAN BUNGA =====
    float flowerPos[][2] = {
        {-5, -6}, {-3, -6}, {3, -6}, {5, -6},
        {-4, -7}, {4, -7}, {-6, -5}, {6, -5}
    };
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(flowerPos[i][0], 0.05f, flowerPos[i][1]);
        glScalef(0.3f, 0.1f, 0.3f);
        glColor4f(0.9f, 0.2f, 0.2f + (i * 0.05f), 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
}

// ==================== INTERIOR MUSEUM ====================

void renderInterior() {
    // ===== LANTAI =====
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(14, 0.05f, 14);
    glColor4f(0.7f, 0.6f, 0.4f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== POLA LANTAI (Calçada Portuguesa) =====
    for (int i = -6; i <= 6; i++) {
        for (int j = -6; j <= 6; j++) {
            if ((i + j) % 2 == 0) {
                glPushMatrix();
                glTranslatef(i * 0.6f, 0.03f, j * 0.6f);
                glScalef(0.5f, 0.02f, 0.5f);
                glColor4f(0.3f, 0.25f, 0.2f, 0.5f);
                drawCube(1, 1, 1);
                glColor4f(1, 1, 1, 1);
                glPopMatrix();
            }
        }
    }
    
    // ===== DINDING =====
    // Belakang
    glPushMatrix();
    glTranslatef(0, 3.0f, -6.8f);
    glScalef(14, 6, 0.2f);
    glColor4f(0.95f, 0.92f, 0.85f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // Kiri
    glPushMatrix();
    glTranslatef(-6.8f, 3.0f, 0);
    glScalef(0.2f, 6, 14);
    glColor4f(0.95f, 0.92f, 0.85f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // Kanan
    glPushMatrix();
    glTranslatef(6.8f, 3.0f, 0);
    glScalef(0.2f, 6, 14);
    glColor4f(0.95f, 0.92f, 0.85f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PLAFON =====
    glPushMatrix();
    glTranslatef(0, 6.0f, 0);
    glScalef(14, 0.1f, 14);
    glColor4f(0.9f, 0.88f, 0.85f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PILAR =====
    float pillarPos[][2] = {{-4.5f, -4.5f}, {4.5f, -4.5f}, {-4.5f, 4.5f}, {4.5f, 4.5f}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(pillarPos[i][0], 0, pillarPos[i][1]);
        glScalef(0.5f, 6.0f, 0.5f);
        glColor4f(0.9f, 0.85f, 0.8f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
        
        // Kapital pilar
        glPushMatrix();
        glTranslatef(pillarPos[i][0], 6.0f, pillarPos[i][1]);
        glScalef(0.7f, 0.2f, 0.7f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
        
        // Basis pilar
        glPushMatrix();
        glTranslatef(pillarPos[i][0], 0.1f, pillarPos[i][1]);
        glScalef(0.6f, 0.2f, 0.6f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== CHANDELIER =====
    glPushMatrix();
    glTranslatef(0, 5.8f, 0);
    drawChandelier();
    glPopMatrix();
    
    // ===== SECTION 1: ANDORINHA =====
    glPushMatrix();
    glTranslatef(-4.5f, 3.5f, -4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(0.8f, 0.2f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== SECTION 2: SPORTING CP =====
    glPushMatrix();
    glTranslatef(0, 3.5f, -4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(0.1f, 0.5f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== SECTION 3: MANCHESTER UNITED =====
    glPushMatrix();
    glTranslatef(4.5f, 3.5f, -4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(0.8f, 0.1f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== AREA TROFI =====
    // 5 Ballon d'Or
    float trophyX[] = {-2.0f, -1.0f, 0, 1.0f, 2.0f};
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(trophyX[i], 0.5f, 0);
        glRotatef(getTrophyRotation(), 0, 1, 0);
        glScalef(0.5f, 0.5f, 0.5f);
        drawBallonDor();
        glPopMatrix();
    }
    
    // ===== SECTION 4: REAL MADRID =====
    glPushMatrix();
    glTranslatef(-4.5f, 3.5f, 4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== SECTION 5: JUVENTUS =====
    glPushMatrix();
    glTranslatef(0, 3.5f, 4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== SECTION 6: AL-NASSR =====
    glPushMatrix();
    glTranslatef(4.5f, 3.5f, 4.5f);
    glScalef(2.5f, 3.5f, 0.05f);
    glColor4f(0.9f, 0.7f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== TIMELINE =====
    float timelineX[] = {-3.0f, -2.0f, -1.0f, 0, 1.0f, 2.0f, 3.0f};
    for (int i = 0; i < 7; i++) {
        glPushMatrix();
        glTranslatef(timelineX[i], 5.0f, -2.0f);
        glScalef(0.6f, 0.5f, 0.05f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== WALL OF FAME - 26 BOLA =====
    for (int i = 0; i < 26; i++) {
        int row = i / 6;
        int col = i % 6;
        glPushMatrix();
        glTranslatef(-4.5f + col * 1.2f, 4.5f - row * 0.9f, -6.5f);
        glScalef(0.25f, 0.25f, 0.25f);
        glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
        drawSphere(0.5f, 8, 8);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== WALL OF FAME - 10 FOTO =====
    float photoX[] = {-4.5f, -3.5f, -2.5f, -1.5f, -0.5f, 0.5f, 1.5f, 2.5f, 3.5f, 4.5f};
    for (int i = 0; i < 10; i++) {
        glPushMatrix();
        glTranslatef(photoX[i], 2.5f, -6.5f);
        glScalef(0.6f, 0.8f, 0.02f);
        glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // ===== INTERACTIVE ZONE =====
    glPushMatrix();
    glTranslatef(-2.5f, 1.5f, 5.5f);
    glScalef(1.5f, 1.0f, 0.05f);
    glColor4f(0.2f, 0.4f, 0.8f, 0.5f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== YOUTUBE STUDIO =====
    glPushMatrix();
    glTranslatef(2.5f, 1.5f, 5.5f);
    glScalef(1.5f, 1.0f, 0.05f);
    glColor4f(0.8f, 0.1f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== SOUVENIR SHOP =====
    glPushMatrix();
    glTranslatef(0, 1.5f, 6.0f);
    glScalef(2.0f, 1.5f, 0.05f);
    glColor4f(0.8f, 0.6f, 0.3f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== PATUNG LILIN =====
    glPushMatrix();
    glTranslatef(0, 0.5f, 3.0f);
    glScalef(0.8f, 0.8f, 0.8f);
    drawWaxFigure();
    glPopMatrix();
}