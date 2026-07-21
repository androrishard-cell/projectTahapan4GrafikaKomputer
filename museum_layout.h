// museum_layout.h
#ifndef MUSEUM_LAYOUT_H
#define MUSEUM_LAYOUT_H

#include <GL/glut.h>

extern void initMuseumLayout();
extern void renderExterior();
extern void renderInterior();

// Fungsi pintu
extern void toggleDoor();
extern void updateDoorAnimation(float deltaTime);
extern void drawDoor(float x, float y, float z);
extern bool isDoorOpen();

// Variabel pintu
extern float doorAnimation;
extern bool doorOpen;

// ===== FUNGSI MATAHARI (TAMBAHKAN INI) =====
extern void drawSun(float x, float y, float z, float radius);
extern void drawSunRays(float x, float y, float z, float radius);

#endif