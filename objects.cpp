// objects.cpp
#include "objects.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <cstring>

// ==================== PRIMITIF DASAR ====================

void drawCube(float w, float h, float d) {
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-w/2, -h/2, d/2);
    glTexCoord2f(1, 0); glVertex3f(w/2, -h/2, d/2);
    glTexCoord2f(1, 1); glVertex3f(w/2, h/2, d/2);
    glTexCoord2f(0, 1); glVertex3f(-w/2, h/2, d/2);
    // Back
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(-w/2, -h/2, -d/2);
    glTexCoord2f(1, 0); glVertex3f(-w/2, h/2, -d/2);
    glTexCoord2f(1, 1); glVertex3f(w/2, h/2, -d/2);
    glTexCoord2f(0, 1); glVertex3f(w/2, -h/2, -d/2);
    // Left
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-w/2, -h/2, -d/2);
    glTexCoord2f(1, 0); glVertex3f(-w/2, -h/2, d/2);
    glTexCoord2f(1, 1); glVertex3f(-w/2, h/2, d/2);
    glTexCoord2f(0, 1); glVertex3f(-w/2, h/2, -d/2);
    // Right
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(w/2, -h/2, -d/2);
    glTexCoord2f(1, 0); glVertex3f(w/2, h/2, -d/2);
    glTexCoord2f(1, 1); glVertex3f(w/2, h/2, d/2);
    glTexCoord2f(0, 1); glVertex3f(w/2, -h/2, d/2);
    // Top
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-w/2, h/2, -d/2);
    glTexCoord2f(1, 0); glVertex3f(w/2, h/2, -d/2);
    glTexCoord2f(1, 1); glVertex3f(w/2, h/2, d/2);
    glTexCoord2f(0, 1); glVertex3f(-w/2, h/2, d/2);
    // Bottom
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(-w/2, -h/2, -d/2);
    glTexCoord2f(1, 0); glVertex3f(-w/2, -h/2, d/2);
    glTexCoord2f(1, 1); glVertex3f(w/2, -h/2, d/2);
    glTexCoord2f(0, 1); glVertex3f(w/2, -h/2, -d/2);
    glEnd();
}

void drawSphere(float radius, int slices, int stacks) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, radius, slices, stacks);
    gluDeleteQuadric(quad);
}

void drawCylinder(float radius, float height, int segments) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluCylinder(quad, radius, radius, height, segments, 1);
    gluDeleteQuadric(quad);
}

void drawCone(float radius, float height, int segments) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluCylinder(quad, radius, 0, height, segments, 1);
    gluDeleteQuadric(quad);
}

void drawTorus(float innerRadius, float outerRadius, int sides, int rings) {
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
}

void drawQuad(float w, float h) {
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-w/2, -h/2, 0);
    glTexCoord2f(1, 0); glVertex3f(w/2, -h/2, 0);
    glTexCoord2f(1, 1); glVertex3f(w/2, h/2, 0);
    glTexCoord2f(0, 1); glVertex3f(-w/2, h/2, 0);
    glEnd();
}

// ==================== OBJEK DASAR MUSEUM ====================

void drawMuseumBuilding() {
    // Main building
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(15, 10, 12);
    bindTexture(TEXTURE_BUILDING);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Roof
    glPushMatrix();
    glTranslatef(0, 10, 0);
    glScalef(16, 1, 13);
    bindTexture(TEXTURE_ROOF);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Glass windows
    for (int i = -6; i <= 6; i += 4) {
        glPushMatrix();
        glTranslatef(i, 5, 6.1f);
        glScalef(1.5f, 2.5f, 0.1f);
        bindTexture(TEXTURE_GLASS);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
}

// ==================== PATUNG CR7 ====================

void drawCR7Statue() {
    // Body
    glPushMatrix();
    glTranslatef(0, 1.5f, 0);
    glScalef(0.5f, 2.5f, 0.5f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 16);
    glPopMatrix();
    
    // Head
    glPushMatrix();
    glTranslatef(0, 3.5f, 0);
    bindTexture(TEXTURE_BRONZE);
    drawSphere(0.5f, 16, 16);
    glPopMatrix();
    
    // Arms
    glPushMatrix();
    glTranslatef(0.8f, 2.5f, 0);
    glRotatef(-30, 0, 0, 1);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.1f, 0.8f, 8);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.8f, 2.5f, 0);
    glRotatef(30, 0, 0, 1);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.1f, 0.8f, 8);
    glPopMatrix();
    
    // Legs
    glPushMatrix();
    glTranslatef(0.25f, 0.2f, 0);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.15f, 1, 8);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.25f, 0.2f, 0);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.15f, 1, 8);
    glPopMatrix();
    
    // Base
    glPushMatrix();
    glTranslatef(0, -0.2f, 0);
    glScalef(1.5f, 0.2f, 1.5f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawCR7CelebrationPose() {
    // Body
    glPushMatrix();
    glTranslatef(0, 1.8f, 0);
    glScalef(0.5f, 2.4f, 0.4f);
    bindTexture(TEXTURE_BRONZE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Head
    glPushMatrix();
    glTranslatef(0, 3.2f, 0);
    bindTexture(TEXTURE_BRONZE);
    drawSphere(0.4f, 20, 20);
    glPopMatrix();
    
    // Hair
    glPushMatrix();
    glTranslatef(0, 3.3f, 0);
    glScalef(0.35f, 0.06f, 0.4f);
    bindTexture(TEXTURE_WALL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Right arm (raised - SIUUU pose)
    glPushMatrix();
    glTranslatef(0.5f, 2.8f, 0);
    glRotatef(-60, 0, 0, 1);
    glRotatef(15, 0, 1, 0);
    glScalef(0.08f, 0.9f, 0.08f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Right fist
    glPushMatrix();
    glTranslatef(0.9f, 3.4f, 0.1f);
    glScalef(0.08f, 0.08f, 0.08f);
    bindTexture(TEXTURE_BRONZE);
    drawSphere(0.5f, 8, 8);
    glPopMatrix();
    
    // Left arm
    glPushMatrix();
    glTranslatef(-0.5f, 2.4f, 0);
    glRotatef(30, 0, 0, 1);
    glRotatef(-10, 0, 1, 0);
    glScalef(0.08f, 0.7f, 0.08f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Right leg
    glPushMatrix();
    glTranslatef(0.25f, 0.3f, 0.15f);
    glScalef(0.1f, 1.0f, 0.1f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Left leg
    glPushMatrix();
    glTranslatef(-0.25f, 0.3f, -0.15f);
    glScalef(0.1f, 1.0f, 0.1f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Shoes
    glPushMatrix();
    glTranslatef(0.25f, 0.05f, 0.2f);
    glScalef(0.15f, 0.05f, 0.15f);
    bindTexture(TEXTURE_BALL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.25f, 0.05f, -0.2f);
    glScalef(0.15f, 0.05f, 0.15f);
    bindTexture(TEXTURE_BALL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Base
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(1.2f, 0.1f, 1.0f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Plaque
    glPushMatrix();
    glTranslatef(0, -0.2f, 0.7f);
    glScalef(0.7f, 0.05f, 0.02f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
}

// ==================== TROFI ====================

void drawTrophy(float scale) {
    glPushMatrix();
    glScalef(scale, scale, scale);
    
    // Base
    glPushMatrix();
    glTranslatef(0, 0, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.5f, 0.3f, 16);
    glPopMatrix();
    
    // Stem
    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.1f, 0.8f, 8);
    glPopMatrix();
    
    // Cup
    glPushMatrix();
    glTranslatef(0, 1.1f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.3f, 0.4f, 16);
    glPopMatrix();
    
    // Handles
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef((i == 0 ? 0.4f : -0.4f), 0.9f, 0);
        glRotatef(i == 0 ? 90 : -90, 0, 0, 1);
        bindTexture(TEXTURE_GOLD);
        drawTorus(0.05f, 0.15f, 8, 8);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawBallonDor() {
    glPushMatrix();
    glScalef(0.7f, 0.7f, 0.7f);
    
    // Base with year
    glPushMatrix();
    glTranslatef(0, 0, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.4f, 0.2f, 16);
    glPopMatrix();
    
    // Stem
    glPushMatrix();
    glTranslatef(0, 0.4f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.08f, 0.6f, 8);
    glPopMatrix();
    
    // Ball
    glPushMatrix();
    glTranslatef(0, 0.9f, 0);
    bindTexture(TEXTURE_GOLD);
    drawSphere(0.3f, 16, 16);
    glPopMatrix();
    
    // Star decoration
    glPushMatrix();
    glTranslatef(0, 0.9f, 0.3f);
    glScalef(0.05f, 0.05f, 0.05f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPopMatrix();
}

void drawGoldenBoot() {
    glPushMatrix();
    glScalef(0.7f, 0.7f, 0.7f);
    
    // Base
    glPushMatrix();
    glTranslatef(0, 0, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.4f, 0.2f, 16);
    glPopMatrix();
    
    // Boot
    glPushMatrix();
    glTranslatef(0, 0.4f, 0.2f);
    glRotatef(-20, 0, 0, 1);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.15f, 0.6f, 8);
    glPopMatrix();
    
    // Boot top
    glPushMatrix();
    glTranslatef(0, 0.9f, 0.1f);
    glRotatef(-30, 0, 0, 1);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.2f, 0.1f, 8);
    glPopMatrix();
    
    glPopMatrix();
}

void drawUCLTrophy() {
    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.6f);
    
    // Base
    glPushMatrix();
    glTranslatef(0, 0, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.5f, 0.2f, 16);
    glPopMatrix();
    
    // Stem
    glPushMatrix();
    glTranslatef(0, 0.4f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.08f, 0.8f, 8);
    glPopMatrix();
    
    // Cup (Big Ears)
    glPushMatrix();
    glTranslatef(0, 1.0f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.35f, 0.5f, 16);
    glPopMatrix();
    
    // Big Ears handles
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef((i == 0 ? 0.5f : -0.5f), 0.8f, 0);
        glRotatef(i == 0 ? 90 : -90, 0, 0, 1);
        bindTexture(TEXTURE_GOLD);
        drawTorus(0.05f, 0.2f, 8, 8);
        glPopMatrix();
    }
    
    glPopMatrix();
}

// ==================== OBJEK INTERIOR ====================

void drawJersey(float w, float h) {
    glPushMatrix();
    glScalef(w, h, 0.05f);
    bindTexture(TEXTURE_JERSEY);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawPillar(float radius, float height) {
    // Base
    glPushMatrix();
    glTranslatef(0, 0, 0);
    bindTexture(TEXTURE_MARBLE);
    drawCylinder(radius + 0.1f, 0.2f, 16);
    glPopMatrix();
    
    // Pillar body
    glPushMatrix();
    glTranslatef(0, height/2, 0);
    bindTexture(TEXTURE_MARBLE);
    drawCylinder(radius, height - 0.4f, 16);
    glPopMatrix();
    
    // Capital (top decoration)
    glPushMatrix();
    glTranslatef(0, height - 0.1f, 0);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(radius + 0.15f, 0.2f, 16);
    glPopMatrix();
}

void drawWall(float w, float h, float d) {
    glPushMatrix();
    bindTexture(TEXTURE_WALL);
    drawCube(w, h, d);
    glPopMatrix();
}

void drawWalls(float width, float height, float depth) {
    // Back wall
    glPushMatrix();
    glTranslatef(0, height/2, -depth/2);
    drawWall(width, height, 0.2f);
    glPopMatrix();
    
    // Left wall
    glPushMatrix();
    glTranslatef(-width/2, height/2, 0);
    drawWall(0.2f, height, depth);
    glPopMatrix();
    
    // Right wall
    glPushMatrix();
    glTranslatef(width/2, height/2, 0);
    drawWall(0.2f, height, depth);
    glPopMatrix();
    
    // Front wall (with entrance area)
    glPushMatrix();
    glTranslatef(0, height/2, depth/2);
    drawWall(width, height, 0.2f);
    glPopMatrix();
}

void drawFloor(float w, float d) {
    glPushMatrix();
    glTranslatef(0, -0.05f, 0);
    glScalef(w, 0.1f, d);
    bindTexture(TEXTURE_FLOOR);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawTree(float trunkHeight, float crownRadius) {
    // Trunk
    glPushMatrix();
    glTranslatef(0, trunkHeight/2, 0);
    bindTexture(TEXTURE_WOOD);
    drawCylinder(0.15f, trunkHeight, 8);
    glPopMatrix();
    
    // Crown
    glPushMatrix();
    glTranslatef(0, trunkHeight + crownRadius * 0.5f, 0);
    bindTexture(TEXTURE_LEAVES);
    drawSphere(crownRadius, 12, 12);
    glPopMatrix();
}

void drawBanner(float w, float h) {
    glPushMatrix();
    bindTexture(TEXTURE_BANNER);
    drawQuad(w, h);
    glPopMatrix();
}

void drawGardenLamp() {
    // Pole
    glPushMatrix();
    glTranslatef(0, 1.5f, 0);
    glScalef(0.08f, 1.5f, 0.08f);
    bindTexture(TEXTURE_METAL);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Lamp
    glPushMatrix();
    glTranslatef(0, 2.3f, 0);
    glScalef(0.3f, 0.2f, 0.3f);
    glColor4f(1.0f, 0.9f, 0.6f, 0.8f);
    drawSphere(0.5f, 8, 8);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}

void drawBench() {
    // Seat
    glPushMatrix();
    glScalef(0.8f, 0.1f, 0.3f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Legs
    glPushMatrix();
    glTranslatef(-0.35f, -0.15f, 0);
    glScalef(0.05f, 0.3f, 0.05f);
    bindTexture(TEXTURE_METAL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.35f, -0.15f, 0);
    glScalef(0.05f, 0.3f, 0.05f);
    bindTexture(TEXTURE_METAL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Backrest
    glPushMatrix();
    glTranslatef(0, 0.3f, -0.15f);
    glScalef(0.8f, 0.4f, 0.05f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawChandelier() {
    // Main rod
    glPushMatrix();
    glTranslatef(0, -0.5f, 0);
    glScalef(0.04f, 0.6f, 0.04f);
    bindTexture(TEXTURE_GOLD);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Main ring
    glPushMatrix();
    glTranslatef(0, -0.8f, 0);
    glScalef(1.2f, 0.05f, 1.2f);
    bindTexture(TEXTURE_GOLD);
    drawTorus(0.04f, 0.6f, 12, 12);
    glPopMatrix();
    
    // Second ring
    glPushMatrix();
    glTranslatef(0, -1.0f, 0);
    glScalef(0.8f, 0.04f, 0.8f);
    bindTexture(TEXTURE_GOLD);
    drawTorus(0.03f, 0.4f, 12, 12);
    glPopMatrix();
    
    // Lamps
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.14159f / 180.0f;
        float x = cos(angle) * 0.9f;
        float z = sin(angle) * 0.9f;
        
        // Chain
        glPushMatrix();
        glTranslatef(x, -0.7f, z);
        glScalef(0.02f, 0.3f, 0.02f);
        bindTexture(TEXTURE_GOLD);
        drawCube(1, 1, 1);
        glPopMatrix();
        
        // Lamp
        glPushMatrix();
        glTranslatef(x, -1.1f, z);
        glScalef(0.15f, 0.2f, 0.15f);
        glColor4f(1.0f, 0.9f, 0.5f, 0.9f);
        drawSphere(0.5f, 8, 8);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // Center lamp
    glPushMatrix();
    glTranslatef(0, -1.1f, 0);
    glScalef(0.2f, 0.25f, 0.2f);
    glColor4f(1.0f, 0.8f, 0.4f, 0.9f);
    drawSphere(0.5f, 8, 8);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}

// ==================== OBJEK INTERIOR BARU ====================

void drawSectionPanel(const char* text, float w, float h) {
    // Panel background
    glPushMatrix();
    glScalef(w, h, 0.05f);
    bindTexture(TEXTURE_PANEL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Gold border
    glPushMatrix();
    glTranslatef(0, 0, 0.03f);
    glScalef(w + 0.1f, h + 0.1f, 0.01f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawChildhoodRoom() {
    // Bed
    glPushMatrix();
    glTranslatef(0, 0.2f, 0);
    glScalef(0.8f, 0.1f, 0.5f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Pillow
    glPushMatrix();
    glTranslatef(0, 0.3f, -0.15f);
    glScalef(0.2f, 0.05f, 0.15f);
    bindTexture(TEXTURE_JERSEY);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Small table
    glPushMatrix();
    glTranslatef(0.5f, 0.1f, 0.3f);
    glScalef(0.3f, 0.05f, 0.2f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawFirstBoots() {
    // First boots
    glPushMatrix();
    glTranslatef(-0.2f, 0.05f, 0);
    glScalef(0.08f, 0.05f, 0.15f);
    bindTexture(TEXTURE_BALL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.2f, 0.05f, 0);
    glScalef(0.08f, 0.05f, 0.15f);
    bindTexture(TEXTURE_BALL);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawHatTrickBall() {
    glPushMatrix();
    glScalef(0.3f, 0.3f, 0.3f);
    bindTexture(TEXTURE_BALL);
    drawSphere(0.5f, 12, 12);
    glPopMatrix();
}

void drawMomentPhoto() {
    // Photo
    glPushMatrix();
    glScalef(0.7f, 0.9f, 0.02f);
    bindTexture(TEXTURE_PHOTO);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Gold frame
    glPushMatrix();
    glTranslatef(0, 0, 0.01f);
    glScalef(0.75f, 0.95f, 0.01f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawInteractiveZone() {
    // Screen
    glPushMatrix();
    glScalef(1.5f, 1.0f, 0.05f);
    bindTexture(TEXTURE_GLASS);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Frame
    glPushMatrix();
    glTranslatef(0, 0, 0.03f);
    glScalef(1.6f, 1.1f, 0.01f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Base
    glPushMatrix();
    glTranslatef(0, -0.6f, 0);
    glScalef(0.6f, 0.1f, 0.3f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawYouTubeStudio() {
    // Desk
    glPushMatrix();
    glTranslatef(0, 0.4f, 0);
    glScalef(1.0f, 0.05f, 0.6f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Screen
    glPushMatrix();
    glTranslatef(0, 0.6f, 0.3f);
    glScalef(0.6f, 0.4f, 0.02f);
    bindTexture(TEXTURE_GLASS);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Chair
    glPushMatrix();
    glTranslatef(0, 0.1f, -0.3f);
    glScalef(0.4f, 0.1f, 0.4f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawSouvenirShop() {
    // Counter
    glPushMatrix();
    glTranslatef(0, 0.4f, 0);
    glScalef(1.2f, 0.3f, 0.5f);
    bindTexture(TEXTURE_WOOD);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Shelves
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(i * 0.5f, 0.7f, 0);
        glScalef(0.3f, 0.1f, 0.3f);
        bindTexture(TEXTURE_WOOD);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
    
    // Mini jerseys
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(i * 0.5f, 0.8f, 0.1f);
        glScalef(0.15f, 0.2f, 0.02f);
        bindTexture(TEXTURE_JERSEY);
        drawCube(1, 1, 1);
        glPopMatrix();
    }
}

void drawWaxFigure() {
    // Body
    glPushMatrix();
    glTranslatef(0, 1.5f, 0);
    glScalef(0.5f, 2.2f, 0.4f);
    bindTexture(TEXTURE_BRONZE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Head
    glPushMatrix();
    glTranslatef(0, 2.8f, 0);
    bindTexture(TEXTURE_BRONZE);
    drawSphere(0.35f, 20, 20);
    glPopMatrix();
    
    // Hair
    glPushMatrix();
    glTranslatef(0, 2.9f, 0);
    glScalef(0.3f, 0.06f, 0.35f);
    bindTexture(TEXTURE_WALL);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Arms
    glPushMatrix();
    glTranslatef(0.5f, 2.2f, 0);
    glRotatef(-30, 0, 0, 1);
    glScalef(0.08f, 0.8f, 0.08f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5f, 2.2f, 0);
    glRotatef(20, 0, 0, 1);
    glScalef(0.08f, 0.8f, 0.08f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Legs
    glPushMatrix();
    glTranslatef(0.2f, 0.3f, 0);
    glScalef(0.1f, 0.9f, 0.1f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2f, 0.3f, 0);
    glScalef(0.1f, 0.9f, 0.1f);
    bindTexture(TEXTURE_BRONZE);
    drawCylinder(0.5f, 1, 8);
    glPopMatrix();
    
    // Base
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(0.9f, 0.08f, 0.9f);
    bindTexture(TEXTURE_MARBLE);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawTimelinePanel(const char* year) {
    // Panel
    glPushMatrix();
    glScalef(0.6f, 0.5f, 0.05f);
    bindTexture(TEXTURE_TIMELINE);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Gold border
    glPushMatrix();
    glTranslatef(0, 0, 0.03f);
    glScalef(0.65f, 0.55f, 0.01f);
    bindTexture(TEXTURE_GOLD);
    drawCube(1, 1, 1);
    glPopMatrix();
}
// objects.cpp - Tambahkan fungsi ini di bagian setelah drawTree

void drawPalmTree(float height) {
    // Batang (melengkung)
    glPushMatrix();
    glTranslatef(0, height/2, 0);
    glScalef(0.12f, height, 0.12f);
    glColor4f(0.5f, 0.35f, 0.15f, 1.0f);
    drawCylinder(0.5f, 1, 8);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
    
    // Daun palem (5 daun)
    for (int i = 0; i < 5; i++) {
        float angle = i * 72.0f * 3.14159f / 180.0f;
        glPushMatrix();
        glTranslatef(0, height, 0);
        glRotatef(30, 1, 0, 0);
        glRotatef(angle * 180.0f / 3.14159f, 0, 1, 0);
        glScalef(0.02f, 0.8f, 0.8f);
        glColor4f(0.1f, 0.5f, 0.1f, 1.0f);
        drawCube(1, 1, 1);
        glColor4f(1, 1, 1, 1);
        glPopMatrix();
    }
    
    // Buah kelapa (opsional)
    glPushMatrix();
    glTranslatef(0, height - 0.1f, 0);
    glScalef(0.1f, 0.1f, 0.1f);
    glColor4f(0.4f, 0.3f, 0.1f, 1.0f);
    drawSphere(0.5f, 6, 6);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}