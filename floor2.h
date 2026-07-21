// floor2.h
#ifndef FLOOR2_H
#define FLOOR2_H

#include "objects.h"

extern void initFloor2();
extern void renderFloor2();
extern void renderStairs(float x, float y, float z);
extern void renderCafe();
extern void renderExhibitionRoom();
extern bool isOnFloor2();
extern void setOnFloor2(bool value);

// Deklarasi variabel global
extern bool onFloor2;

#endif