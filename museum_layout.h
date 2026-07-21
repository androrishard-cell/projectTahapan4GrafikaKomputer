// museum_layout.h
#ifndef MUSEUM_LAYOUT_H
#define MUSEUM_LAYOUT_H

extern void initMuseumLayout();
extern void renderExterior();
extern void renderInterior();

// ===== FUNGSI PINTU =====
extern void toggleDoor();
extern void updateDoorAnimation(float deltaTime);
extern void drawDoor(float x, float y, float z);
extern bool isDoorOpen();

// ===== VARIABEL PINTU (Deklarasikan di sini) =====
extern float doorAnimation;
extern bool doorOpen;

#endif