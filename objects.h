// objects.h
#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>

extern void drawCube(float w, float h, float d);
extern void drawSphere(float radius, int slices, int stacks);
extern void drawCylinder(float radius, float height, int segments);
extern void drawCone(float radius, float height, int segments);
extern void drawTorus(float innerRadius, float outerRadius, int sides, int rings);
extern void drawQuad(float w, float h);

// Museum objects
extern void drawMuseumBuilding();
extern void drawCR7Statue();
extern void drawTrophy(float scale);
extern void drawBallonDor();
extern void drawGoldenBoot();
extern void drawJersey(float w, float h);
extern void drawPillar(float radius, float height);
extern void drawWall(float w, float h, float d);
extern void drawFloor(float w, float d);
extern void drawTree(float trunkHeight, float crownRadius);
extern void drawBanner(float w, float h);

#endif