// interactions.cpp
#include "interactions.h"
#include "camera.h"
#include "animations.h"
#include <iostream>
#include <cmath>

static std::vector<GameObject> gameObjects;
static bool helpVisible = false;
static bool gamePaused = false;

void initInteractions() {
    GameObject obj;
    
    // Museum building
    strcpy(obj.name, "Museum");
    obj.x = 0; obj.y = 0; obj.z = 0;
    obj.width = 16; obj.height = 10; obj.depth = 12;
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
    obj.width = 1.5; obj.height = 3; obj.depth = 1.5;
    obj.bbox.minX = obj.x - obj.width/2;
    obj.bbox.maxX = obj.x + obj.width/2;
    obj.bbox.minY = obj.y - obj.height/2;
    obj.bbox.maxY = obj.y + obj.height/2;
    obj.bbox.minZ = obj.z - obj.depth/2;
    obj.bbox.maxZ = obj.z + obj.depth/2;
    obj.isSolid = true;
    gameObjects.push_back(obj);
    
    std::cout << "Interactions initialized with " << gameObjects.size() << " objects" << std::endl;
}

void checkCollisions(float* x, float* y, float* z) {
    BoundingBox playerBox;
    playerBox.minX = *x - 0.3f;
    playerBox.maxX = *x + 0.3f;
    playerBox.minY = *y - 0.9f;
    playerBox.maxY = *y + 0.9f;
    playerBox.minZ = *z - 0.3f;
    playerBox.maxZ = *z + 0.3f;
    
    for (const auto& obj : gameObjects) {
        if (!obj.isSolid) continue;
        
        const BoundingBox& box = obj.bbox;
        
        if (playerBox.minX < box.maxX && playerBox.maxX > box.minX &&
            playerBox.minY < box.maxY && playerBox.maxY > box.minY &&
            playerBox.minZ < box.maxZ && playerBox.maxZ > box.minZ) {
            
            // Push player out
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
        switch (button) {
            case GLUT_LEFT_BUTTON:
                std::cout << "Click at: " << x << ", " << y << std::endl;
                break;
            case GLUT_RIGHT_BUTTON:
                // Switch camera mode
                int mode = getCurrentCameraMode();
                setCameraMode((mode + 1) % 3);
                break;
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

void updateInteractions(float deltaTime) {
    // Update collision objects if needed
}

void showHelp() {
    helpVisible = !helpVisible;
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
    std::cout << "  A       - Auto Tour" << std::endl;
    std::cout << "  T       - Night Mode" << std::endl;
    std::cout << "  Space   - Celebration!" << std::endl;
    std::cout << "  R       - Reset Camera" << std::endl;
    std::cout << "  F       - Fullscreen" << std::endl;
    std::cout << "  ESC     - Pause" << std::endl;
    std::cout << "  H / F1  - This Help" << std::endl;
    std::cout << "========================================" << std::endl;
}

void togglePause() {
    gamePaused = !gamePaused;
    std::cout << "Game: " << (gamePaused ? "PAUSED" : "RESUMED") << std::endl;
}