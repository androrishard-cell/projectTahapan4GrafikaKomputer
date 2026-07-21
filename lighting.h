// lighting.h
#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL/glut.h>

extern void initLighting();
extern void setupLighting();
extern void updateLighting(float deltaTime);
extern void toggleNightMode();
extern bool getNightModeStatus();

#endif