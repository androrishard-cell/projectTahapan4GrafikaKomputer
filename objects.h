// objects.h
#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>

// Primitif dasar
extern void drawCube(float w, float h, float d);
extern void drawSphere(float radius, int slices, int stacks);
extern void drawCylinder(float radius, float height, int segments);
extern void drawCone(float radius, float height, int segments);
extern void drawTorus(float innerRadius, float outerRadius, int sides, int rings);
extern void drawQuad(float w, float h);

// Objek Museum
extern void drawMuseumBuilding();
extern void drawCR7Statue();
extern void drawCR7CelebrationPose();
extern void drawTrophy(float scale);
extern void drawBallonDor();
extern void drawGoldenBoot();
extern void drawUCLTrophy();
extern void drawJersey(float w, float h);
extern void drawPillar(float radius, float height);
extern void drawWall(float w, float h, float d);
extern void drawWalls(float width, float height, float depth);
extern void drawFloor(float w, float d);
extern void drawTree(float trunkHeight, float crownRadius);
extern void drawPalmTree(float height);  // TAMBAHKAN
extern void drawBanner(float w, float h);
extern void drawGardenLamp();
extern void drawBench();
extern void drawChandelier();

// Objek Interior baru
extern void drawSectionPanel(const char* text, float w, float h);
extern void drawChildhoodRoom();
extern void drawFirstBoots();
extern void drawHatTrickBall();
extern void drawMomentPhoto();
extern void drawInteractiveZone();
extern void drawYouTubeStudio();
extern void drawSouvenirShop();
extern void drawWaxFigure();
extern void drawTimelinePanel(const char* year);

#endif