// textures.h
#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glut.h>

// Texture IDs
#define TEXTURE_FLOOR 0
#define TEXTURE_WALL 1
#define TEXTURE_BUILDING 2
#define TEXTURE_ROOF 3
#define TEXTURE_GLASS 4
#define TEXTURE_GOLD 5
#define TEXTURE_BRONZE 6
#define TEXTURE_MARBLE 7
#define TEXTURE_WOOD 8
#define TEXTURE_LEAVES 9
#define TEXTURE_JERSEY 10
#define TEXTURE_BANNER 11
#define TEXTURE_SKYBOX 12
#define TEXTURE_GRASS 13
#define TEXTURE_METAL 14
#define TEXTURE_BALL 15
#define TEXTURE_TIMELINE 16
#define TEXTURE_PHOTO 17
#define TEXTURE_PANEL 18

extern void initTextures();
extern void bindTexture(int id);

#endif