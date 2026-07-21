// interactions.h
#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include <GL/glut.h>
#include <vector>
#include <string>

struct BoundingBox {
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
};

struct GameObject {
    float x, y, z;
    float width, height, depth;
    BoundingBox bbox;
    bool isSolid;
    char name[50];
};

extern void initInteractions();
extern void checkCollisions(float* x, float* y, float* z);
extern void handleMouseClick(int button, int state, int x, int y);
extern void handleMouseMotion(int x, int y);
extern void updateInteractions(float deltaTime);
extern void showHelp();
extern void togglePause();

#endif