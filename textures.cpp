// textures.cpp
#include "textures.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

static GLuint textures[20];
static bool texturesLoaded = false;

// ==================== DEKLARASI FUNGSI ====================
void generateCheckerTexture(GLuint texID, int size, unsigned char r1, unsigned char g1, unsigned char b1,
                            unsigned char r2, unsigned char g2, unsigned char b2);
void generateMarbleTexture(GLuint texID, int size);
void generateGoldTexture(GLuint texID, int size);
void generateWoodTexture(GLuint texID, int size);
void generateGrassTexture(GLuint texID, int size);
void generateSkyboxTexture(GLuint texID, int size);
void generateBronzeTexture(GLuint texID, int size);
void generateMetalTexture(GLuint texID, int size);
void generateBallTexture(GLuint texID, int size);
void generateTimelineTexture(GLuint texID, int size);
void generatePhotoTexture(GLuint texID, int size);
void generatePanelTexture(GLuint texID, int size);

// ==================== IMPLEMENTASI ====================

void generateCheckerTexture(GLuint texID, int size, unsigned char r1, unsigned char g1, unsigned char b1,
                            unsigned char r2, unsigned char g2, unsigned char b2) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool isBlack = ((i / (size/8)) + (j / (size/8))) % 2 == 0;
            int idx = (i * size + j) * 3;
            if (isBlack) {
                data[idx] = r1; data[idx+1] = g1; data[idx+2] = b1;
            } else {
                data[idx] = r2; data[idx+1] = g2; data[idx+2] = b2;
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

void generateWoodTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = sin(i * 0.2f + j * 0.01f) * 0.3f + sin(i * 0.05f - j * 0.02f) * 0.3f;
            unsigned char val = (unsigned char)(140 + 80 * noise);
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(val * 1.1f);
            data[idx+1] = (unsigned char)(val * 0.85f);
            data[idx+2] = (unsigned char)(val * 0.6f);
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

void generateGrassTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = ((float)rand() / RAND_MAX - 0.5f) * 0.3f;
            unsigned char g = (unsigned char)(120 + 80 * (sin(i * 0.1f) * cos(j * 0.1f) * 0.5f + 0.5f) + 50 * noise);
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(g * 0.8f);
            data[idx+1] = g;
            data[idx+2] = (unsigned char)(g * 0.6f);
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

void generateSkyboxTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float sky = (float)i / size;
            unsigned char r = (unsigned char)(30 + 100 * sky);
            unsigned char g = (unsigned char)(80 + 150 * sky);
            unsigned char b = (unsigned char)(150 + 100 * sky);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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

void generateMetalTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = ((float)rand() / RAND_MAX - 0.5f) * 30.0f;
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(180 + noise);
            data[idx+1] = (unsigned char)(180 + noise);
            data[idx+2] = (unsigned char)(190 + noise);
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

void generateBallTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float dist = sqrt(pow((float)i/size - 0.5f, 2) + pow((float)j/size - 0.5f, 2));
            int idx = (i * size + j) * 3;
            if (dist < 0.4f) {
                data[idx] = 255; data[idx+1] = 255; data[idx+2] = 255;
            } else {
                data[idx] = 50; data[idx+1] = 50; data[idx+2] = 50;
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
}

void generateTimelineTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = (i * size + j) * 3;
            if (i < size/2) {
                data[idx] = 200; data[idx+1] = 180; data[idx+2] = 150;
            } else {
                data[idx] = 150; data[idx+1] = 130; data[idx+2] = 100;
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
}

void generatePhotoTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float noise = ((float)rand() / RAND_MAX - 0.5f) * 20.0f;
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(150 + noise);
            data[idx+1] = (unsigned char)(120 + noise);
            data[idx+2] = (unsigned char)(100 + noise);
        }
    }
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
}

void generatePanelTexture(GLuint texID, int size) {
    unsigned char* data = new unsigned char[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = (i * size + j) * 3;
            if ((i + j) % 4 < 2) {
                data[idx] = 180; data[idx+1] = 160; data[idx+2] = 130;
            } else {
                data[idx] = 160; data[idx+1] = 140; data[idx+2] = 110;
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

// ==================== INISIALISASI ====================

// textures.cpp - Ganti dengan texture warna solid

void initTextures() {
    if (texturesLoaded) return;
    
    glGenTextures(20, textures);
    
    // Buat texture warna solid untuk setiap ID
    for (int i = 0; i < 20; i++) {
        unsigned char data[3] = {
            (unsigned char)(100 + rand() % 155),
            (unsigned char)(100 + rand() % 155),
            (unsigned char)(100 + rand() % 155)
        };
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
    texturesLoaded = true;
    std::cout << "Textures initialized (procedural)" << std::endl;
}

void bindTexture(int id) {
    if (id >= 0 && id < 20 && texturesLoaded) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[id]);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}