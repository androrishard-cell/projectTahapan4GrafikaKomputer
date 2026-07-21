// objects.cpp
#include "objects.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

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

// ==================== OBJEK MUSEUM ====================

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
    drawTrophy(0.8f);
}

void drawGoldenBoot() {
    glPushMatrix();
    glScalef(0.8f, 0.8f, 0.8f);
    
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

void drawJersey(float w, float h) {
    glPushMatrix();
    glScalef(w, h, 0.05f);
    bindTexture(TEXTURE_JERSEY);
    drawCube(1, 1, 1);
    glPopMatrix();
}

void drawPillar(float radius, float height) {
    glPushMatrix();
    bindTexture(TEXTURE_MARBLE);
    drawCylinder(radius, height, 16);
    glPopMatrix();
}

void drawWall(float w, float h, float d) {
    glPushMatrix();
    bindTexture(TEXTURE_WALL);
    drawCube(w, h, d);
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