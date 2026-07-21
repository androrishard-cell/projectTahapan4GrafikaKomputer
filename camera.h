// camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <math.h>

#define CAM_FIRST_PERSON 0
#define CAM_ORBIT 1
#define CAM_FREE_FLY 2

// Movement directions
#define FORWARD 0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

extern void initCamera();
extern void setupCamera();
extern void updateCamera(float deltaTime);
extern void setCameraMode(int mode);
extern void setCameraModeFirstPerson();
extern void setCameraModeOrbit();
extern void setCameraModeFreeFly();
extern void moveCamera(int direction, float speed);
extern void rotateCamera(float dx, float dy);
extern void resetCamera();
extern int getCurrentCameraMode();
extern std::string getCameraModeString();

#endif