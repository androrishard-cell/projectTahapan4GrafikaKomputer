// camera.cpp
#include "camera.h"
#include "interactions.h"
#include <iostream>
#include <string>
#include <cmath>

// Camera state
static struct {
    float eyeX, eyeY, eyeZ;
    float centerX, centerY, centerZ;
    float upX, upY, upZ;
    float yaw;
    float pitch;
    float radius;
    int mode;
    float speed;
    float mouseSensitivity;
    bool isMoving;
} camera;

void initCamera() {
    camera.eyeX = 0.0f;
    camera.eyeY = 2.0f;
    camera.eyeZ = 18.0f;
    camera.centerX = 0.0f;
    camera.centerY = 1.0f;
    camera.centerZ = 0.0f;
    camera.upX = 0.0f;
    camera.upY = 1.0f;
    camera.upZ = 0.0f;
    camera.yaw = 0.0f;
    camera.pitch = 0.0f;
    camera.radius = 18.0f;
    camera.mode = CAM_FIRST_PERSON;
    camera.speed = 3.0f;
    camera.mouseSensitivity = 0.15f;
    camera.isMoving = false;
}

void setupCamera() {
    if (camera.mode == CAM_ORBIT) {
        float rad = camera.radius;
        float theta = camera.yaw * 3.14159f / 180.0f;
        float phi = camera.pitch * 3.14159f / 180.0f;
        
        camera.eyeX = camera.centerX + rad * cos(theta) * cos(phi);
        camera.eyeY = camera.centerY + rad * sin(phi);
        camera.eyeZ = camera.centerZ + rad * sin(theta) * cos(phi);
    }
    
    gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ,
              camera.centerX, camera.centerY, camera.centerZ,
              camera.upX, camera.upY, camera.upZ);
}

void updateCamera(float deltaTime) {
    float yawRad = camera.yaw * 3.14159f / 180.0f;
    float pitchRad = camera.pitch * 3.14159f / 180.0f;
    
    camera.centerX = camera.eyeX + cos(pitchRad) * sin(yawRad);
    camera.centerY = camera.eyeY + sin(pitchRad);
    camera.centerZ = camera.eyeZ + cos(pitchRad) * cos(yawRad);
}

void setCameraMode(int mode) {
    camera.mode = mode;
    if (mode == CAM_ORBIT) {
        camera.radius = sqrt(pow(camera.eyeX - camera.centerX, 2) + 
                            pow(camera.eyeY - camera.centerY, 2) + 
                            pow(camera.eyeZ - camera.centerZ, 2));
    }
    std::cout << "Camera Mode: " << getCameraModeString() << std::endl;
}

void setCameraModeFirstPerson() { 
    setCameraMode(CAM_FIRST_PERSON); 
}

void setCameraModeOrbit() { 
    setCameraMode(CAM_ORBIT); 
}

void setCameraModeFreeFly() { 
    setCameraMode(CAM_FREE_FLY); 
}

void moveCamera(int direction, float speed) {
    if (speed <= 0) speed = camera.speed;
    float moveSpeed = speed * 2.5f;
    float yawRad = camera.yaw * 3.14159f / 180.0f;
    float pitchRad = camera.pitch * 3.14159f / 180.0f;
    
    float forwardX = cos(pitchRad) * sin(yawRad);
    float forwardZ = cos(pitchRad) * cos(yawRad);
    float forwardY = sin(pitchRad);
    
    float rightX = cos(yawRad);
    float rightZ = -sin(yawRad);
    
    float newX = camera.eyeX;
    float newY = camera.eyeY;
    float newZ = camera.eyeZ;
    
    switch (direction) {
        case FORWARD:
            newX += forwardX * moveSpeed;
            newY += forwardY * moveSpeed;
            newZ += forwardZ * moveSpeed;
            break;
        case BACKWARD:
            newX -= forwardX * moveSpeed;
            newY -= forwardY * moveSpeed;
            newZ -= forwardZ * moveSpeed;
            break;
        case LEFT:
            newX -= rightX * moveSpeed;
            newZ -= rightZ * moveSpeed;
            break;
        case RIGHT:
            newX += rightX * moveSpeed;
            newZ += rightZ * moveSpeed;
            break;
        case UP:
            newY += moveSpeed;
            break;
        case DOWN:
            newY -= moveSpeed;
            break;
    }
    
    checkCollisions(&newX, &newY, &newZ);
    
    camera.eyeX = newX;
    camera.eyeY = newY;
    camera.eyeZ = newZ;
    
    updateCamera(0);
}

// ===== PERBAIKAN UTAMA: MOUSE CONTROL =====
// Mouse ke KANAN = View ke KANAN
// Mouse ke KIRI = View ke KIRI
void rotateCamera(float dx, float dy) {
    float sens = camera.mouseSensitivity;
    
    // ===== HORIZONTAL =====
    // dx > 0 (mouse ke kanan) -> yaw positif (view ke kanan)
    // dx < 0 (mouse ke kiri) -> yaw negatif (view ke kiri)
    camera.yaw += dx * sens;  // <-- PASTIKAN INI + (TANDA PLUS)
    
    // ===== VERTIKAL =====
    // dy > 0 (mouse ke bawah) -> pitch negatif (view ke bawah)
    // dy < 0 (mouse ke atas) -> pitch positif (view ke atas)
    camera.pitch -= dy * sens;  // <-- PASTIKAN INI - (TANDA MINUS)
    
    // Clamp pitch agar tidak terbalik
    if (camera.pitch > 89.0f) camera.pitch = 89.0f;
    if (camera.pitch < -89.0f) camera.pitch = -89.0f;
    
    updateCamera(0);
}

void resetCamera() {
    camera.eyeX = 0.0f;
    camera.eyeY = 2.0f;
    camera.eyeZ = 18.0f;
    camera.centerX = 0.0f;
    camera.centerY = 1.0f;
    camera.centerZ = 0.0f;
    camera.yaw = 0.0f;
    camera.pitch = 0.0f;
    camera.radius = 18.0f;
    updateCamera(0);
    std::cout << "Camera Reset" << std::endl;
}

int getCurrentCameraMode() { 
    return camera.mode; 
}

std::string getCameraModeString() {
    switch (camera.mode) {
        case CAM_FIRST_PERSON: return "First Person";
        case CAM_ORBIT: return "Orbit";
        case CAM_FREE_FLY: return "Free Fly";
        default: return "Unknown";
    }
}