// interactions.cpp
#include "interactions.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

// Forward declarations untuk fungsi dari camera.h
extern int getCurrentCameraMode();
extern void setCameraMode(int mode);
extern std::string getCameraModeString();
extern void rotateCamera(float dx, float dy);

static std::vector<GameObject> gameObjects;
static bool gamePaused = false;

void initInteractions() {
    GameObject obj;
    
    // Museum building
    strcpy(obj.name, "Museum");
    obj.x = 0; obj.y = 0; obj.z = 0;
    obj.width = 18; obj.height = 12; obj.depth = 14;
    obj.bbox.minX = obj.x - obj.width/2;
    obj.bbox.maxX = obj.x + obj.width/2;
    obj.bbox.minY = obj.y - obj.height/2;
    obj.bbox.maxY = obj.y + obj.height/2;
    obj.bbox.minZ = obj.z - obj.depth/2;
    obj.bbox.maxZ = obj.z + obj.depth/2;
    obj.isSolid = true;
    gameObjects.push_back(obj);
    
    // CR7 Statue
    strcpy(obj.name, "CR7 Statue");
    obj.x = -4; obj.y = 0; obj.z = -8;
    obj.width = 2; obj.height = 3.5; obj.depth = 2;
    obj.bbox.minX = obj.x - obj.width/2;
    obj.bbox.maxX = obj.x + obj.width/2;
    obj.bbox.minY = obj.y - obj.height/2;
    obj.bbox.maxY = obj.y + obj.height/2;
    obj.bbox.minZ = obj.z - obj.depth/2;
    obj.bbox.maxZ = obj.z + obj.depth/2;
    obj.isSolid = true;
    gameObjects.push_back(obj);
    
    // Trees
    for (int i = 0; i < 2; i++) {
        strcpy(obj.name, "Tree");
        obj.x = (i == 0) ? 8 : -8;
        obj.y = 0;
        obj.z = -6;
        obj.width = 2; obj.height = 4; obj.depth = 2;
        obj.bbox.minX = obj.x - obj.width/2;
        obj.bbox.maxX = obj.x + obj.width/2;
        obj.bbox.minY = obj.y - obj.height/2;
        obj.bbox.maxY = obj.y + obj.height/2;
        obj.bbox.minZ = obj.z - obj.depth/2;
        obj.bbox.maxZ = obj.z + obj.depth/2;
        obj.isSolid = true;
        gameObjects.push_back(obj);
    }
    
    std::cout << "Interactions initialized with " << gameObjects.size() << " objects" << std::endl;
}

void checkCollisions(float* x, float* y, float* z) {
    BoundingBox playerBox;
    float radius = 0.4f;
    float height = 0.9f;
    playerBox.minX = *x - radius;
    playerBox.maxX = *x + radius;
    playerBox.minY = *y - height;
    playerBox.maxY = *y + height;
    playerBox.minZ = *z - radius;
    playerBox.maxZ = *z + radius;
    
    for (const auto& obj : gameObjects) {
        if (!obj.isSolid) continue;
        
        const BoundingBox& box = obj.bbox;
        
        if (playerBox.minX < box.maxX && playerBox.maxX > box.minX &&
            playerBox.minY < box.maxY && playerBox.maxY > box.minY &&
            playerBox.minZ < box.maxZ && playerBox.maxZ > box.minZ) {
            
            float overlapX = 0, overlapZ = 0;
            
            if (playerBox.maxX > box.minX && playerBox.maxX < box.maxX) {
                overlapX = box.minX - playerBox.maxX - 0.01f;
            } else if (playerBox.minX < box.maxX && playerBox.minX > box.minX) {
                overlapX = box.maxX - playerBox.minX + 0.01f;
            }
            
            if (playerBox.maxZ > box.minZ && playerBox.maxZ < box.maxZ) {
                overlapZ = box.minZ - playerBox.maxZ - 0.01f;
            } else if (playerBox.minZ < box.maxZ && playerBox.minZ > box.minZ) {
                overlapZ = box.maxZ - playerBox.minZ + 0.01f;
            }
            
            if (fabs(overlapX) < fabs(overlapZ)) {
                *x += overlapX;
            } else {
                *z += overlapZ;
            }
        }
    }
}

void handleMouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            std::cout << "Click at: " << x << ", " << y << std::endl;
        } else if (button == GLUT_RIGHT_BUTTON) {
            int mode = getCurrentCameraMode();
            setCameraMode((mode + 1) % 3);
            std::cout << "Camera Mode: " << getCameraModeString() << std::endl;
        }
    }
}

void handleMouseMotion(int x, int y) {
    static int lastX = -1, lastY = -1;
    if (lastX == -1) { lastX = x; lastY = y; return; }
    
    int dx = x - lastX;
    int dy = y - lastY;
    lastX = x;
    lastY = y;
    
    rotateCamera(dx, dy);
}

void updateInteractions(float deltaTime) {}

void showHelp() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  MUSEUM VIRTUAL 3D CR7 - HELP" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  CONTROLS:" << std::endl;
    std::cout << "  WASD    - Move camera" << std::endl;
    std::cout << "  Mouse   - Look around" << std::endl;
    std::cout << "  1       - First Person Camera" << std::endl;
    std::cout << "  2       - Orbit Camera" << std::endl;
    std::cout << "  3       - Free Fly Camera" << std::endl;
    std::cout << "  E       - Enter/Exit Museum" << std::endl;
    std::cout << "  Q       - Exit Museum (Interior)" << std::endl;
    std::cout << "  A       - Auto Tour" << std::endl;
    std::cout << "  T       - Night Mode" << std::endl;
    std::cout << "  Space   - Celebration!" << std::endl;
    std::cout << "  R       - Reset Camera" << std::endl;
    std::cout << "  F       - Fullscreen" << std::endl;
    std::cout << "  ESC     - Pause" << std::endl;
    std::cout << "  H / F1  - This Help" << std::endl;
    std::cout << "  Right Mouse - Switch Camera" << std::endl;
    std::cout << "========================================" << std::endl;
}

void togglePause() {
    gamePaused = !gamePaused;
    std::cout << "Game: " << (gamePaused ? "PAUSED" : "RESUMED") << std::endl;
}

bool isGamePaused() { return gamePaused; }