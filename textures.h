// textures.h
#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glut.h>

// Texture IDs
#define TEXTURE_FLOOR 1
#define TEXTURE_WALL 2
#define TEXTURE_BUILDING 3
#define TEXTURE_ROOF 4
#define TEXTURE_GLASS 5
#define TEXTURE_GOLD 6
#define TEXTURE_BRONZE 7
#define TEXTURE_MARBLE 8
#define TEXTURE_WOOD 9
#define TEXTURE_LEAVES 10
#define TEXTURE_JERSEY 11
#define TEXTURE_BANNER 12
#define TEXTURE_SKYBOX 13
#define TEXTURE_GRASS 14

extern void initTextures();
extern void bindTexture(int id);

#endif