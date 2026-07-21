// museum_layout.cpp
#include "museum_layout.h"
#include "objects.h"
#include "animations.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

void initMuseumLayout() {}

// ==================== EKSTERIOR MUSEUM ====================

void renderExterior() {
    // ===== SKYBOX =====
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glScalef(60, 30, 60);
    glDisable(GL_LIGHTING);
    bindTexture(TEXTURE_SKYBOX);
    drawCube(1, 1, 1);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ===== GROUND =====
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(50, 0.2f, 40);
    bindTexture(TEXTURE_GRASS);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== JALAN SETAPAK =====
    glPushMatrix();
    glTranslatef(0, 0.01f, -7);
    glScalef(6, 0.05f, 3);
    bindTexture(TEXTURE_FLOOR);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== AREA PLAZA DEPAN =====
    glPushMatrix();
    glTranslatef(0, 0.01f, -3);
    glScalef(12, 0.05f, 4);
    bindTexture(TEXTURE_FLOOR);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== GEDUNG MUSEUM =====
    // Struktur utama
    glPushMatrix();
    glTranslatef(0, 3.0f, 0);
    glScalef(16, 6, 12);
    bindTexture(TEXTURE_BUILDING);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Atap (dengan kemiringan)
    glPushMatrix();
    glTranslatef(0, 6.5f, 0);
    glScalef(17, 0.8f, 13);
    bindTexture(TEXTURE_ROOF);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Ornamen atap depan
    glPushMatrix();
    glTranslatef(0, 6.8f, 6.2f);
    glScalef(14, 0.3f, 0.8f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== PILAR-PILAR DEPAN =====
    float pillarPos[] = {-5.5f, -3.5f, -1.5f, 1.5f, 3.5f, 5.5f};
    for (int i = 0; i < 6; i++) {
        // Pilar utama
        glPushMatrix();
        glTranslatef(pillarPos[i], 0.5f, 6.2f);
        drawPillar(0.35f, 6.0f);
        glPopMatrix();
        
        // Kapital pilar (hiasan atas)
        glPushMatrix();
        glTranslatef(pillarPos[i], 3.5f, 6.2f);
        glScalef(0.8f, 0.15f, 0.8f);
        bindTexture(TEXTURE_GOLD);
        drawCube(1, 1, 1);
        glPopMatrix();
        
        // Basis pilar
        glPushMatrix();
        glTranslatef(pillarPos[i], 0.1f, 6.2f);
        glScalef(0.8f, 0.15f, 0.8f);
        bindTexture(TEXTURE_MARBLE);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ===== PINTU UTAMA =====
    // Bingkai pintu (marmer)
    glPushMatrix();
    glTranslatef(0, 1.8f, 6.1f);
    glScalef(3.0f, 3.6f, 0.4f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Pintu kiri
    glPushMatrix();
    glTranslatef(-0.8f, 1.8f, 6.3f);
    glScalef(0.9f, 3.2f, 0.1f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Pintu kanan
    glPushMatrix();
    glTranslatef(0.8f, 1.8f, 6.3f);
    glScalef(0.9f, 3.2f, 0.1f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Handle pintu (emas)
    glPushMatrix();
    glTranslatef(-0.4f, 1.8f, 6.4f);
    glScalef(0.05f, 0.2f, 0.05f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4f, 1.8f, 6.4f);
    glScalef(0.05f, 0.2f, 0.05f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== JENDELA DEPAN =====
    float windowX[] = {-4.8f, -2.8f, 2.8f, 4.8f};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            // Kaca jendela
            glPushMatrix();
            glTranslatef(windowX[i], 2.2f + j * 2.5f, 6.1f);
            glScalef(1.2f, 1.8f, 0.05f);
            bindTexture(TEXTURE_GLASS);
            drawCube(1, 1, 1);
            glPopMatrix();
            
            // Bingkai jendela
            glPushMatrix();
            glTranslatef(windowX[i], 2.2f + j * 2.5f, 6.15f);
            glScalef(1.3f, 1.9f, 0.02f);
            glColor4f(0.7f, 0.7f, 0.7f, 0.3f);
            drawCube(1, 1, 1);
            glColor4f(1, 1, 1, 1);
            glPopMatrix();
        }
    }
    
    // ===== LOGO MUSEUM CR7 =====
    // Banner besar di atas pintu
    glPushMatrix();
    glTranslatef(0, 5.2f, 6.3f);
    glScalef(5, 1.2f, 0.1f);
    bindTexture(TEXTURE_BANNER);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== PATUNG CR7 (Pose SIUUU) =====
    glPushMatrix();
    glTranslatef(-4, 0.2f, -4);
    glRotatef(getStatueAngle(), 0, 1, 0);
    glScalef(1.0f, 1.0f, 1.0f);
    drawCR7CelebrationPose();
    glPopMatrix();
    
    // ===== POHON-POHON DI TAMAN =====
    float treePos[][2] = {
        {9, -3}, {-9, -3}, {7, -7}, {-7, -7}, 
        {10, -5}, {-10, -5}, {8, -9}, {-8, -9}
    };
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(treePos[i][0], 0, treePos[i][1]);
        drawTree(2.5f + (i % 3) * 0.3f, 1.8f + (i % 2) * 0.5f);
        glPopMatrix();
    }
    
    // ===== LAMPU TAMAN =====
    float lampPos[][2] = {{-6, -3}, {6, -3}, {-5, -7}, {5, -7}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(lampPos[i][0], 0, lampPos[i][1]);
        drawGardenLamp();
        glPopMatrix();
    }
    
    // ===== BANGKU TAMAN =====
    glPushMatrix();
    glTranslatef(-7, 0, -2);
    drawBench();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, 0, -2);
    drawBench();
    glPopMatrix();
}

// ==================== INTERIOR MUSEUM ====================

void renderInterior() {
    // ===== LANTAI =====
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawFloor(14, 14);
    glPopMatrix();
    
    // ===== DINDING =====
    drawWalls(14, 5.5f, 14);
    
    // ===== PLAFON =====
    glPushMatrix();
    glTranslatef(0, 5.5f, 0);
    glScalef(14, 0.1f, 14);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // ===== PILAR INTERIOR =====
    float pillarPos[][2] = {{-4.5f, -4.5f}, {4.5f, -4.5f}, {-4.5f, 4.5f}, {4.5f, 4.5f}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(pillarPos[i][0], 0, pillarPos[i][1]);
        drawPillar(0.4f, 5.5f);
        glPopMatrix();
    }
    
    // ===== CHANDELIER =====
    glPushMatrix();
    glTranslatef(0, 5.3f, 0);
    drawChandelier();
    glPopMatrix();
    
    // ============================================================
    // SECTION 1: ANDORINHA (Masa Kecil Ronaldo)
    // ============================================================
    glPushMatrix();
    glTranslatef(-4.5f, 3.0f, -4.5f);
    drawSectionPanel("ANDORINHA", 2.5f, 3.5f);
    glPopMatrix();
    
    // Kamar masa kecil
    glPushMatrix();
    glTranslatef(-4.5f, 0.3f, -5.5f);
    glScalef(0.8f, 0.8f, 0.8f);
    drawChildhoodRoom();
    glPopMatrix();
    
    // Foto masa kecil
    glPushMatrix();
    glTranslatef(-4.5f, 1.5f, -5.2f);
    glScalef(0.5f, 0.6f, 0.5f);
    drawMomentPhoto();
    glPopMatrix();
    
    // ============================================================
    // SECTION 2: SPORTING CP
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 3.0f, -4.5f);
    drawSectionPanel("SPORTING CP", 2.5f, 3.5f);
    glPopMatrix();
    
    // Jersey Sporting
    glPushMatrix();
    glTranslatef(0, 2.0f, -5.5f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawJersey(1.2f, 1.6f);
    glPopMatrix();
    
    // Sepatu pertama
    glPushMatrix();
    glTranslatef(0, 0.5f, -5.5f);
    drawFirstBoots();
    glPopMatrix();
    
    // ============================================================
    // SECTION 3: MANCHESTER UNITED
    // ============================================================
    glPushMatrix();
    glTranslatef(4.5f, 3.0f, -4.5f);
    drawSectionPanel("MAN UTD", 2.5f, 3.5f);
    glPopMatrix();
    
    // Jersey MU
    glPushMatrix();
    glTranslatef(4.5f, 2.0f, -5.5f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawJersey(1.2f, 1.6f);
    glPopMatrix();
    
    // Ballon d'Or 2008
    glPushMatrix();
    glTranslatef(4.5f, 0.5f, -5.5f);
    glScalef(0.6f, 0.6f, 0.6f);
    drawBallonDor();
    glPopMatrix();
    
    // ============================================================
    // AREA TROFI UTAMA (Pusat Museum)
    // ============================================================
    // 5 Ballon d'Or
    float trophyX[] = {-2.0f, -1.0f, 0, 1.0f, 2.0f};
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(trophyX[i], 0.5f, 0);
        glRotatef(getTrophyRotation(), 0, 1, 0);
        glScalef(0.5f, 0.5f, 0.5f);
        drawBallonDor();
        glPopMatrix();
        
        // Label tahun
        glPushMatrix();
        glTranslatef(trophyX[i], 0.1f, 0);
        glScalef(0.2f, 0.02f, 0.01f);
        bindTexture(TEXTURE_GOLD);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // 4 Golden Boots
    float bootX[] = {-1.5f, -0.5f, 0.5f, 1.5f};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(bootX[i], 0.5f, 1.5f);
        glRotatef(getTrophyRotation() * 0.8f, 0, 1, 0);
        glScalef(0.5f, 0.5f, 0.5f);
        drawGoldenBoot();
        glPopMatrix();
    }
    
    // 5 UCL Trophies
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(-2.0f + i * 1.0f, 0.5f, -0.5f);
        glScalef(0.5f, 0.5f, 0.5f);
        drawUCLTrophy();
        glPopMatrix();
    }
    
    // ============================================================
    // SECTION 4: REAL MADRID
    // ============================================================
    glPushMatrix();
    glTranslatef(-4.5f, 3.0f, 4.5f);
    drawSectionPanel("REAL MADRID", 2.5f, 3.5f);
    glPopMatrix();
    
    // Jersey RM
    glPushMatrix();
    glTranslatef(-4.5f, 2.0f, 5.5f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawJersey(1.2f, 1.6f);
    glPopMatrix();
    
    // ============================================================
    // SECTION 5: JUVENTUS
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 3.0f, 4.5f);
    drawSectionPanel("JUVENTUS", 2.5f, 3.5f);
    glPopMatrix();
    
    // Jersey Juventus
    glPushMatrix();
    glTranslatef(0, 2.0f, 5.5f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawJersey(1.2f, 1.6f);
    glPopMatrix();
    
    // ============================================================
    // SECTION 6: AL-NASSR
    // ============================================================
    glPushMatrix();
    glTranslatef(4.5f, 3.0f, 4.5f);
    drawSectionPanel("AL-NASSR", 2.5f, 3.5f);
    glPopMatrix();
    
    // Jersey Al-Nassr
    glPushMatrix();
    glTranslatef(4.5f, 2.0f, 5.5f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawJersey(1.2f, 1.6f);
    glPopMatrix();
    
    // ============================================================
    // TIMELINE KARIER
    // ============================================================
    float timelineX[] = {-3.0f, -2.0f, -1.0f, 0, 1.0f, 2.0f, 3.0f};
    const char* years[] = {"1985", "1992", "2003", "2008", "2013", "2016", "2021"};
    const char* events[] = {"Born", "Sporting", "MU", "1st BdO", "RM", "Euro", "Juventus"};
    for (int i = 0; i < 7; i++) {
        glPushMatrix();
        glTranslatef(timelineX[i], 4.5f, -2.0f);
        drawTimelinePanel(years[i]);
        glPopMatrix();
        
        // Label event
        glPushMatrix();
        glTranslatef(timelineX[i], 3.8f, -2.0f);
        glScalef(0.3f, 0.02f, 0.01f);
        bindTexture(TEXTURE_GOLD);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ============================================================
    // WALL OF FAME - 26 BOLA HAT-TRICK
    // ============================================================
    for (int i = 0; i < 26; i++) {
        int row = i / 6;
        int col = i % 6;
        glPushMatrix();
        glTranslatef(-4.5f + col * 1.2f, 4.2f - row * 0.9f, -5.8f);
        glScalef(0.25f, 0.25f, 0.25f);
        drawHatTrickBall();
        glPopMatrix();
        
        // Label nomor
        glPushMatrix();
        glTranslatef(-4.5f + col * 1.2f, 3.7f - row * 0.9f, -5.8f);
        glScalef(0.05f, 0.02f, 0.01f);
        bindTexture(TEXTURE_GOLD);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // ============================================================
    // WALL OF FAME - 10 FOTO MOMEN KARIR
    // ============================================================
    float photoX[] = {-4.5f, -3.5f, -2.5f, -1.5f, -0.5f, 0.5f, 1.5f, 2.5f, 3.5f, 4.5f};
    for (int i = 0; i < 10; i++) {
        glPushMatrix();
        glTranslatef(photoX[i], 2.5f, -5.8f);
        glScalef(0.6f, 0.8f, 0.6f);
        drawMomentPhoto();
        glPopMatrix();
    }
    
    // ============================================================
    // INTERACTIVE ZONE (AI Photo Booth)
    // ============================================================
    glPushMatrix();
    glTranslatef(-2.5f, 1.5f, 5.0f);
    glScalef(0.8f, 0.8f, 0.8f);
    drawInteractiveZone();
    glPopMatrix();
    
    // ============================================================
    // YOUTUBE STUDIO
    // ============================================================
    glPushMatrix();
    glTranslatef(2.5f, 1.5f, 5.0f);
    glScalef(0.8f, 0.8f, 0.8f);
    drawYouTubeStudio();
    glPopMatrix();
    
    // ============================================================
    // SOUVENIR SHOP
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 1.5f, 5.5f);
    glScalef(0.9f, 0.9f, 0.9f);
    drawSouvenirShop();
    glPopMatrix();
    
    // ============================================================
    // PATUNG LILIN CR7
    // ============================================================
    glPushMatrix();
    glTranslatef(0, 0.5f, 3.0f);
    glScalef(0.7f, 0.7f, 0.7f);
    drawWaxFigure();
    glPopMatrix();
}