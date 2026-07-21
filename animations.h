// animations.h
#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <GL/glut.h>
#include <vector>

struct Particle {
    float x, y, z;
    float vx, vy, vz;
    float life;
    float maxLife;
    bool active;
};

extern void initAnimations();
extern void updateAnimations(float deltaTime);
extern void renderAnimations();
extern void toggleAutoTour();
extern void toggleNightMode();
extern void triggerCelebration();
extern bool getAutoTourStatus();
extern bool getNightModeStatus();
extern float getTrophyRotation();
extern float getBallRotation();

#endif