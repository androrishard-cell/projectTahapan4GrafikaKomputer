// museum_layout.cpp
#include "museum_layout.h"
#include "objects.h"
#include "animations.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

// ===== VARIABEL GLOBAL =====
float doorAnimation = 0.0f;
bool doorOpen = false;
static float doorSpeed = 2.0f;

void initMuseumLayout() {
    doorAnimation = 0.0f;
    doorOpen = false;
    srand(time(NULL));
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
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(4.0f, 5.0f, 0.6f);
    glColor4f(0.6f, 0.5f, 0.4f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
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

// ===== FUNGSI MATAHARI =====
void drawSun(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glColor4f(1.0f, 0.9f, 0.4f, 0.08f);
    glPushMatrix();
    glScalef(radius * 8.0f, radius * 8.0f, radius * 8.0f);
    drawSphere(1.0f, 12, 12);
    glPopMatrix();
    
    glColor4f(1.0f, 0.85f, 0.3f, 0.15f);
    glPushMatrix();
    glScalef(radius * 5.0f, radius * 5.0f, radius * 5.0f);
    drawSphere(1.0f, 12, 12);
    glPopMatrix();
    
    glColor4f(1.0f, 0.8f, 0.2f, 0.3f);
    glPushMatrix();
    glScalef(radius * 3.0f, radius * 3.0f, radius * 3.0f);
    drawSphere(1.0f, 12, 12);
    glPopMatrix();
    
    glColor4f(1.0f, 0.9f, 0.5f, 0.5f);
    glPushMatrix();
    glScalef(radius * 1.8f, radius * 1.8f, radius * 1.8f);
    drawSphere(1.0f, 16, 16);
    glPopMatrix();
    
    glColor4f(1.0f, 0.95f, 0.6f, 1.0f);
    glPushMatrix();
    glScalef(radius, radius, radius);
    drawSphere(1.0f, 20, 20);
    glPopMatrix();
    
    glColor4f(1.0f, 1.0f, 0.9f, 0.8f);
    glPushMatrix();
    glScalef(radius * 0.6f, radius * 0.6f, radius * 0.6f);
    drawSphere(1.0f, 20, 20);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void drawSunRays(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    int numRays = 12;
    float rayLength = radius * 3.0f;
    
    for (int i = 0; i < numRays; i++) {
        float angle = i * (360.0f / numRays) * 3.14159f / 180.0f;
        float nextAngle = (i + 1) * (360.0f / numRays) * 3.14159f / 180.0f;
        
        glColor4f(1.0f, 0.9f, 0.3f, 0.15f);
        glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(angle) * rayLength, sin(angle) * rayLength * 0.6f, 0);
        glVertex3f(cos(nextAngle) * rayLength, sin(nextAngle) * rayLength * 0.6f, 0);
        glEnd();
        
        glColor4f(1.0f, 0.95f, 0.5f, 0.1f);
        glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(angle + 0.05f) * rayLength * 1.3f, sin(angle + 0.05f) * rayLength * 0.6f * 1.3f, 0);
        glVertex3f(cos(nextAngle - 0.05f) * rayLength * 1.3f, sin(nextAngle - 0.05f) * rayLength * 0.6f * 1.3f, 0);
        glEnd();
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

// ============================================================
// ===== EKSTERIOR MUSEUM =====
// ============================================================

// museum_layout.cpp - Bagian renderExterior yang diperbaiki

void renderExterior() {
    // ============================================================
    // ===== SKYBOX (Langit dengan gradasi natural) =====
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glScalef(80, 40, 80);
    glDisable(GL_LIGHTING);
    
    // Gradasi langit 5 lapis (lebih natural)
    glBegin(GL_QUADS);
    // Lapis 1: Puncak (biru tua)
    glColor4f(0.05f, 0.15f, 0.5f, 1.0f);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    
    // Lapis 2: Atas (biru sedang)
    glColor4f(0.1f, 0.3f, 0.7f, 1.0f);
    glVertex3f(-1, 0.6f, -1);
    glVertex3f(1, 0.6f, -1);
    glVertex3f(1, 0.6f, 1);
    glVertex3f(-1, 0.6f, 1);
    
    // Lapis 3: Tengah (biru cerah)
    glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
    glVertex3f(-1, 0.2f, -1);
    glVertex3f(1, 0.2f, -1);
    glVertex3f(1, 0.2f, 1);
    glVertex3f(-1, 0.2f, 1);
    
    // Lapis 4: Bawah (biru muda)
    glColor4f(0.6f, 0.8f, 1.0f, 1.0f);
    glVertex3f(-1, -0.2f, -1);
    glVertex3f(1, -0.2f, -1);
    glVertex3f(1, -0.2f, 1);
    glVertex3f(-1, -0.2f, 1);
    
    // Lapis 5: Horizon (putih kebiruan)
    glColor4f(0.85f, 0.9f, 1.0f, 1.0f);
    glVertex3f(-1, -0.6f, -1);
    glVertex3f(1, -0.6f, -1);
    glVertex3f(1, -0.6f, 1);
    glVertex3f(-1, -0.6f, 1);
    
    // Lapis 6: Horizon bawah (putih)
    glColor4f(0.95f, 0.97f, 1.0f, 1.0f);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ============================================================
    // ===== MATAHARI (Natural dengan posisi di langit) =====
    // ============================================================
    // Posisi matahari di langit (kanan atas)
    float sunX = 20.0f;
    float sunY = 12.0f;
    float sunZ = -15.0f;
    float sunRadius = 2.0f;
    
    // Sinar matahari (di belakang)
    drawSunRays(sunX, sunY, sunZ, sunRadius);
    
    // Matahari (di atas sinar)
    drawSun(sunX, sunY, sunZ, sunRadius);
    
    // ============================================================
    // ===== AWAN 3D (Natural dengan berbagai ukuran) =====
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glScalef(80, 40, 80);
    glDisable(GL_LIGHTING);
    
    // Awan besar dan kecil dengan posisi natural
    struct CloudData {
        float x, y, z;
        float size;
        float opacity;
    };
    
    CloudData clouds[] = {
        // Awan besar
        {-18, 6, -8, 3.5, 0.9},
        {12, 7, -5, 4.0, 0.85},
        {-8, 8, 3, 3.0, 0.9},
        {22, 5, -10, 3.5, 0.8},
        {-22, 6, 6, 3.0, 0.85},
        
        // Awan sedang
        {5, 9, -18, 2.5, 0.8},
        {15, 8, 8, 2.0, 0.75},
        {-12, 7, 10, 2.5, 0.8},
        {0, 10, -22, 2.0, 0.7},
        {-25, 5, -12, 2.5, 0.75},
        
        // Awan kecil
        {8, 6, -12, 1.5, 0.7},
        {-5, 9, 0, 1.8, 0.7},
        {18, 7, 12, 1.5, 0.65},
        {-15, 8, -5, 1.8, 0.7},
        {3, 5, 8, 1.5, 0.65}
    };
    
    for (int c = 0; c < 15; c++) {
        float cx = clouds[c].x;
        float cy = clouds[c].y;
        float cz = clouds[c].z;
        float size = clouds[c].size;
        float opacity = clouds[c].opacity;
        
        glPushMatrix();
        glTranslatef(cx, cy, cz);
        
        // Warna awan (putih dengan transparansi)
        glColor4f(1.0f, 1.0f, 1.0f, opacity);
        
        // Sphere utama (pusat)
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(size, size * 0.35f, size * 0.25f);
        drawSphere(1.0f, 12, 12);
        glPopMatrix();
        
        // Sphere kiri bawah
        glPushMatrix();
        glTranslatef(-size * 0.7f, -size * 0.05f, 0);
        glScalef(size * 0.5f, size * 0.3f, size * 0.2f);
        drawSphere(1.0f, 10, 10);
        glPopMatrix();
        
        // Sphere kanan bawah
        glPushMatrix();
        glTranslatef(size * 0.7f, -size * 0.05f, 0);
        glScalef(size * 0.5f, size * 0.3f, size * 0.2f);
        drawSphere(1.0f, 10, 10);
        glPopMatrix();
        
        // Sphere atas
        glPushMatrix();
        glTranslatef(0, size * 0.25f, 0);
        glScalef(size * 0.4f, size * 0.25f, size * 0.15f);
        drawSphere(1.0f, 10, 10);
        glPopMatrix();
        
        // Sphere kiri atas
        glPushMatrix();
        glTranslatef(-size * 0.4f, size * 0.15f, 0);
        glScalef(size * 0.3f, size * 0.2f, size * 0.15f);
        drawSphere(1.0f, 10, 10);
        glPopMatrix();
        
        // Sphere kanan atas
        glPushMatrix();
        glTranslatef(size * 0.4f, size * 0.15f, 0);
        glScalef(size * 0.3f, size * 0.2f, size * 0.15f);
        drawSphere(1.0f, 10, 10);
        glPopMatrix();
        
        glPopMatrix();
    }
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ============================================================
    // ===== GROUND / RUMPUT (Natural dengan gradasi) =====
    // ============================================================
    // Lapisan rumput utama (hijau gelap)
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(60, 0.2f, 50);
    glColor4f(0.1f, 0.4f, 0.05f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Lapisan rumput kedua (hijau sedang)
    glPushMatrix();
    glTranslatef(0, -0.05f, 0);
    glScalef(58, 0.05f, 48);
    glColor4f(0.15f, 0.5f, 0.08f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Lapisan rumput ketiga (hijau terang)
    glPushMatrix();
    glTranslatef(0, -0.02f, 0);
    glScalef(55, 0.03f, 45);
    glColor4f(0.2f, 0.55f, 0.1f, 0.5f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== TEKSTUR RUMPUT (Rumput-rumput kecil) =====
    glPushMatrix();
    glTranslatef(0, -0.01f, 0);
    glDisable(GL_LIGHTING);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 500; i++) {
        float x = (rand() % 600 - 300) / 10.0f;
        float z = (rand() % 500 - 250) / 10.0f;
        float green = 0.2f + (rand() % 50) / 100.0f;
        glColor4f(0.1f, green, 0.05f, 0.5f + (rand() % 30) / 100.0f);
        glVertex3f(x, 0.01f, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ===== AREA PLAZA (Portuguese Pavement) =====
    glPushMatrix();
    glTranslatef(0, 0.02f, -3);
    glScalef(22, 0.05f, 10);
    glColor4f(0.75f, 0.7f, 0.55f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== POLA LANTAI PLAZA =====
    for (int i = -10; i <= 10; i++) {
        for (int j = -5; j <= 5; j++) {
            if ((i + j) % 2 == 0) {
                glPushMatrix();
                glTranslatef(i * 0.7f, 0.04f, j * 0.7f - 2);
                glScalef(0.6f, 0.02f, 0.6f);
                glColor4f(0.3f, 0.25f, 0.2f, 0.4f);
                drawCube(1, 1, 1);
                glPopMatrix();
            }
        }
    }
    
    // ============================================================
    // ===== GEDUNG MUSEUM =====
    // ============================================================
    // Badan gedung
    glPushMatrix();
    glTranslatef(0, 6.0f, 0);
    glScalef(18, 12, 14);
    glColor4f(0.92f, 0.88f, 0.82f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== GARIS HORIZONTAL =====
    for (int floor = 0; floor < 3; floor++) {
        glPushMatrix();
        glTranslatef(0, 2.0f + floor * 4.0f, 7.1f);
        glScalef(17.5f, 0.04f, 0.1f);
        glColor4f(0.8f, 0.75f, 0.68f, 1.0f);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ===== ATAP =====
    glPushMatrix();
    glTranslatef(0, 12.5f, 0);
    glScalef(19, 0.6f, 15);
    glColor4f(0.7f, 0.65f, 0.6f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== ORNAMEN ATAP =====
    glPushMatrix();
    glTranslatef(0, 12.8f, 7.3f);
    glScalef(17, 0.2f, 1.0f);
    glColor4f(0.8f, 0.75f, 0.68f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== PILAR DEPAN =====
    float pillarPos[] = {-6.5f, -4.0f, -1.5f, 1.5f, 4.0f, 6.5f};
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(pillarPos[i], 2.0f, 7.2f);
        glScalef(0.7f, 8.5f, 0.7f);
        glColor4f(0.93f, 0.9f, 0.85f, 1.0f);
        drawCube(1, 1, 1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(pillarPos[i], 6.8f, 7.2f);
        glScalef(1.0f, 0.4f, 1.0f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(pillarPos[i], 0.3f, 7.2f);
        glScalef(0.9f, 0.4f, 0.9f);
        glColor4f(0.85f, 0.8f, 0.7f, 1.0f);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ===== PINTU =====
    drawDoor(0, 2.5f, 7.2f);
    
    // ===== JENDELA =====
    float windowX1[] = {-5.5f, -3.5f, 3.5f, 5.5f};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(windowX1[i], 1.8f, 7.3f);
        glScalef(1.4f, 2.0f, 0.05f);
        glColor4f(0.3f, 0.6f, 0.8f, 0.35f);
        drawCube(1, 1, 1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(windowX1[i], 1.8f, 7.35f);
        glScalef(1.6f, 2.2f, 0.02f);
        glColor4f(0.85f, 0.82f, 0.78f, 0.8f);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ===== LOGO CR7 =====
    glPushMatrix();
    glTranslatef(0, 9.0f, 7.4f);
    glScalef(7.0f, 1.8f, 0.15f);
    glColor4f(0.8f, 0.15f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 9.0f, 7.5f);
    glScalef(7.2f, 2.0f, 0.02f);
    glColor4f(0.9f, 0.75f, 0.1f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 9.0f, 7.55f);
    glScalef(3.0f, 0.8f, 0.02f);
    glColor4f(1.0f, 0.9f, 0.2f, 1.0f);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== PATUNG CR7 =====
    glPushMatrix();
    glTranslatef(-5.0f, 0.2f, -4.5f);
    glRotatef(getStatueAngle(), 0, 1, 0);
    glScalef(1.3f, 1.3f, 1.3f);
    drawCR7CelebrationPose();
    glPopMatrix();
    
    // ===== POHON =====
    float palmPos[][2] = {{9, -2}, {-9, -2}, {10, -5}, {-10, -5}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(palmPos[i][0], 0, palmPos[i][1]);
        drawPalmTree(4.5f + (i % 2) * 0.5f);
        glPopMatrix();
    }
    
    // Pohon rindang
    float treePos[][2] = {
        {11, -7}, {-11, -7}, {12, -3}, {-12, -3},
        {8, -9}, {-8, -9}, {10, -10}, {-10, -10}
    };
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(treePos[i][0], 0, treePos[i][1]);
        drawTree(3.5f + (i % 3) * 0.3f, 2.5f + (i % 2) * 0.5f);
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
    
    // ===== BANGKU =====
    float benchPos[][2] = {{-8.5f, -2}, {8.5f, -2}, {-8.0f, -6}, {8.0f, -6}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(benchPos[i][0], 0, benchPos[i][1]);
        drawBench();
        glPopMatrix();
    }
    
    // ===== TAMAN BUNGA =====
    float flowerPos[][2] = {
        {-5, -7}, {-3, -7}, {3, -7}, {5, -7},
        {-4, -8}, {4, -8}, {-6, -6}, {6, -6}
    };
    float flowerColors[][3] = {
        {0.9f, 0.2f, 0.2f}, {0.9f, 0.4f, 0.1f}, {0.9f, 0.9f, 0.1f},
        {0.8f, 0.1f, 0.8f}, {0.1f, 0.8f, 0.1f}, {0.9f, 0.5f, 0.1f},
        {0.8f, 0.2f, 0.6f}, {0.2f, 0.4f, 0.9f}
    };
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(flowerPos[i][0], 0.05f, flowerPos[i][1]);
        glScalef(0.4f, 0.15f, 0.4f);
        glColor4f(flowerColors[i][0], flowerColors[i][1], flowerColors[i][2], 1.0f);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
}

// museum_layout.cpp - Tambahkan fungsi renderInterior() di bagian akhir

void renderInterior() {
    // ===== LANTAI (Portuguese Pavement) =====
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(14, 0.05f, 14);
    glColor4f(0.7f, 0.6f, 0.4f, 1.0f);
    drawCube(1, 1, 1);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // ===== POLA LANTAI =====
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
    }
    
    // ===== CHANDELIER =====
    glPushMatrix();
    glTranslatef(0, 5.8f, 0);
    drawChandelier();
    glPopMatrix();
}