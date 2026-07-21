// museum_layout.cpp
#include "museum_layout.h"
#include "objects.h"
#include "animations.h"
#include "textures.h"
#include <GL/gl.h>
#include <GL/glu.h>

void initMuseumLayout() {
    // Nothing to init here
}

void renderExterior() {
    // Skybox
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(50, 30, 50);
    bindTexture(TEXTURE_SKYBOX);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Ground
    glPushMatrix();
    glTranslatef(0, -0.1f, 0);
    glScalef(40, 0.2f, 40);
    bindTexture(TEXTURE_GRASS);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Museum Building
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawMuseumBuilding();
    glPopMatrix();
    
    // CR7 Statue
    glPushMatrix();
    glTranslatef(-3, 0.2f, -7);
    glRotatef(getStatueAngle(), 0, 1, 0);
    drawCR7Statue();
    glPopMatrix();
    
    // Trees
    glPushMatrix();
    glTranslatef(8, 0, -6);
    drawTree(2.0f, 1.5f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8, 0, -6);
    drawTree(2.0f, 1.5f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8, 0, -10);
    drawTree(1.5f, 1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8, 0, -10);
    drawTree(1.5f, 1.0f);
    glPopMatrix();
    
    // Path
    glPushMatrix();
    glTranslatef(0, 0.01f, -3.5f);
    glScalef(2, 0.05f, 4);
    bindTexture(TEXTURE_FLOOR);
    drawCube(1, 1, 1);
    glPopMatrix();
    
    // Entrance banner
    glPushMatrix();
    glTranslatef(0, 3.5f, 6.1f);
    drawBanner(4, 2);
    glPopMatrix();
}

void renderInterior() {
    // Floor
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawFloor(12, 12);
    glPopMatrix();
    
    // Walls
    // Back wall
    glPushMatrix();
    glTranslatef(0, 2.5f, -6);
    drawWall(12, 5, 0.2f);
    glPopMatrix();
    
    // Left wall
    glPushMatrix();
    glTranslatef(-6, 2.5f, 0);
    drawWall(0.2f, 5, 12);
    glPopMatrix();
    
    // Right wall
    glPushMatrix();
    glTranslatef(6, 2.5f, 0);
    drawWall(0.2f, 5, 12);
    glPopMatrix();
    
    // Front wall (with entrance)
    glPushMatrix();
    glTranslatef(0, 2.5f, 6);
    drawWall(4, 5, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.5f, 2.5f, 6);
    drawWall(3, 5, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-4.5f, 2.5f, 6);
    drawWall(3, 5, 0.2f);
    glPopMatrix();
    
    // Ceiling
    glPushMatrix();
    glTranslatef(0, 5, 0);
    drawWall(12, 0.2f, 12);
    glPopMatrix();
    
    // Pillars
    glPushMatrix();
    glTranslatef(-4.5f, 0, -4.5f);
    drawPillar(0.3f, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.5f, 0, -4.5f);
    drawPillar(0.3f, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-4.5f, 0, 4.5f);
    drawPillar(0.3f, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.5f, 0, 4.5f);
    drawPillar(0.3f, 5);
    glPopMatrix();
    
    // Trophy display
    glPushMatrix();
    glTranslatef(0, 0.5f, -3);
    glRotatef(getTrophyRotation(), 0, 1, 0);
    drawBallonDor();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, 0.5f, -3);
    glRotatef(getTrophyRotation(), 0, 1, 0);
    drawGoldenBoot();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2, 0.5f, -3);
    glRotatef(getTrophyRotation(), 0, 1, 0);
    drawGoldenBoot();
    glPopMatrix();
    
    // Jersey display
    glPushMatrix();
    glTranslatef(-3, 2.5f, 0);
    drawJersey(1.5f, 2.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3, 2.5f, 0);
    drawJersey(1.5f, 2.0f);
    glPopMatrix();
    
    // Banners on walls
    glPushMatrix();
    glTranslatef(0, 4.5f, -6);
    drawBanner(3, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-5.9f, 2.5f, 0);
    glRotatef(90, 0, 1, 0);
    drawBanner(3, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(5.9f, 2.5f, 0);
    glRotatef(-90, 0, 1, 0);
    drawBanner(3, 1);
    glPopMatrix();
}