// textures.cpp
#include "textures.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#include <wingdi.h>
#endif

static GLuint textures[24];
static bool texturesLoaded = false;

// ==================== LOAD TEXTURE DARI FILE ====================

void loadTextureFromFile(const char* filename, int id) {
    #ifdef _WIN32
    // Untuk Windows - menggunakan FreeImage atau stb_image
    // Sementara kita buat texture procedural
    std::cout << "Loading texture: " << filename << std::endl;
    #endif
    
    // Buat texture procedural sebagai placeholder
    unsigned char data[64 * 64 * 3];
    for (int i = 0; i < 64 * 64 * 3; i++) {
        data[i] = (unsigned char)(rand() % 256);
    }
    
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// ==================== GENERATE TEXTURE PROCEDURAL ====================

void generateMarbleTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = sin(i * 0.05f) * cos(j * 0.05f) + sin((i + j) * 0.03f) * 0.5f;
            unsigned char val = (unsigned char)(180 + 75 * noise);
            int idx = (i * size + j) * 3;
            data[idx] = val;
            data[idx+1] = val * 0.85f;
            data[idx+2] = val * 0.7f;
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void generateGoldTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = sin(i * 0.1f + j * 0.05f) * cos(j * 0.08f - i * 0.03f);
            unsigned char r = (unsigned char)(200 + 55 * noise);
            unsigned char g = (unsigned char)(170 + 55 * noise);
            unsigned char b = (unsigned char)(80 + 30 * noise);
            int idx = (i * size + j) * 3;
            data[idx] = r;
            data[idx+1] = g;
            data[idx+2] = b;
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void generateBronzeTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = ((float)rand() / RAND_MAX - 0.5f) * 30.0f;
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(150 + noise);
            data[idx+1] = (unsigned char)(110 + noise);
            data[idx+2] = (unsigned char)(60 + noise);
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void generatePavementTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool isBlack = ((i / 16) + (j / 16)) % 2 == 0;
            int idx = (i * size + j) * 3;
            if (isBlack) {
                data[idx] = 60; data[idx+1] = 55; data[idx+2] = 45;
            } else {
                data[idx] = 200; data[idx+1] = 190; data[idx+2] = 170;
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void generateJerseyTexture(GLuint texID, int size, unsigned char r, unsigned char g, unsigned char b) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = (i * size + j) * 3;
            // Pola garis vertikal
            if (j % 16 < 4) {
                data[idx] = (unsigned char)(r * 0.8f);
                data[idx+1] = (unsigned char)(g * 0.8f);
                data[idx+2] = (unsigned char)(b * 0.8f);
            } else {
                data[idx] = r;
                data[idx+1] = g;
                data[idx+2] = b;
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void initTextures() {
    if (texturesLoaded) return;
    
    glGenTextures(24, textures);
    
    // Texture yang sudah ada
    generateMarbleTexture(textures[0], 256);   // FLOOR
    generateMarbleTexture(textures[1], 256);   // WALL
    generateMarbleTexture(textures[2], 256);   // BUILDING
    generateMarbleTexture(textures[3], 256);   // ROOF
    generateMarbleTexture(textures[4], 128);   // GLASS
    generateGoldTexture(textures[5], 256);     // GOLD
    generateBronzeTexture(textures[6], 256);   // BRONZE
    generateMarbleTexture(textures[7], 256);   // MARBLE
    generateMarbleTexture(textures[8], 256);   // WOOD
    generateMarbleTexture(textures[9], 128);   // LEAVES
    generateJerseyTexture(textures[10], 256, 200, 50, 50); // JERSEY
    generateMarbleTexture(textures[11], 256);  // BANNER
    generateMarbleTexture(textures[12], 256);  // SKYBOX
    generateMarbleTexture(textures[13], 256);  // GRASS
    generateMarbleTexture(textures[14], 256);  // METAL
    generateMarbleTexture(textures[15], 256);  // BALL
    generateMarbleTexture(textures[16], 256);  // TIMELINE
    generateMarbleTexture(textures[17], 256);  // PHOTO
    generateMarbleTexture(textures[18], 256);  // PANEL
    
    // Texture baru
    generateMarbleTexture(textures[19], 256);  // JERSEY_MU (Merah)
    generateMarbleTexture(textures[20], 256);  // JERSEY_RM (Putih)
    generateMarbleTexture(textures[21], 256);  // JERSEY_JUVE (Hitam/Putih)
    generateMarbleTexture(textures[22], 256);  // JERSEY_PORTUGAL (Merah/Hijau)
    generatePavementTexture(textures[23], 256); // PAVEMENT
    
    texturesLoaded = true;
    std::cout << "Textures initialized: 24 textures" << std::endl;
}

void bindTexture(int id) {
    if (id >= 0 && id < 24 && texturesLoaded) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[id]);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}