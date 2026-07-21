// animations.cpp
#include "animations.h"
#include "objects.h"
#include "textures.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

static struct {
    float trophyRotation;
    float ballRotation;
    float statueAngle;
    float spotlightAngle;
    float doorOpen;
    float photoIndex;
    float celebrationTimer;
    float autoTourProgress;
    bool isAutoTour;
    bool isNightMode;
    bool isDoorOpen;
    float rainIntensity;
} anim;

static std::vector<Particle> dustParticles;
static std::vector<Particle> rainParticles;
static std::vector<Particle> celebrationParticles;

void initAnimations() {
    anim.trophyRotation = 0.0f;
    anim.ballRotation = 0.0f;
    anim.statueAngle = 0.0f;
    anim.spotlightAngle = 0.0f;
    anim.doorOpen = 0.0f;
    anim.photoIndex = 0.0f;
    anim.celebrationTimer = 0.0f;
    anim.autoTourProgress = 0.0f;
    anim.isAutoTour = false;
    anim.isNightMode = false;
    anim.isDoorOpen = false;
    anim.rainIntensity = 0.3f;
    
    // Dust particles
    dustParticles.clear();
    for (int i = 0; i < 50; i++) {
        Particle p;
        p.x = (rand() % 200 - 100) / 10.0f;
        p.y = (rand() % 20) / 10.0f + 0.5f;
        p.z = (rand() % 200 - 100) / 10.0f;
        p.vx = (rand() % 20 - 10) / 1000.0f;
        p.vy = (rand() % 20 - 10) / 1000.0f;
        p.vz = (rand() % 20 - 10) / 1000.0f;
        p.life = rand() % 100 / 100.0f;
        p.maxLife = 2.0f + (rand() % 30) / 10.0f;
        p.active = true;
        dustParticles.push_back(p);
    }
    
    // Rain particles
    rainParticles.clear();
    for (int i = 0; i < 400; i++) {
        Particle p;
        p.x = (rand() % 400 - 200) / 10.0f;
        p.y = (rand() % 40) / 10.0f + 2.0f;
        p.z = (rand() % 400 - 200) / 10.0f;
        p.vx = (rand() % 10 - 5) / 100.0f;
        p.vy = -(rand() % 15 + 10) / 100.0f;
        p.vz = (rand() % 10 - 5) / 100.0f;
        p.life = 0;
        p.maxLife = 1.0f;
        p.active = true;
        rainParticles.push_back(p);
    }
    
    // Celebration particles
    celebrationParticles.clear();
    for (int i = 0; i < 100; i++) {
        Particle p;
        p.x = 0; p.y = 0; p.z = 0;
        p.vx = (rand() % 40 - 20) / 100.0f;
        p.vy = (rand() % 30 + 10) / 100.0f;
        p.vz = (rand() % 40 - 20) / 100.0f;
        p.life = 0;
        p.maxLife = 2.0f + (rand() % 20) / 10.0f;
        p.active = false;
        celebrationParticles.push_back(p);
    }
    
    std::cout << "Animations initialized: 10 animations" << std::endl;
}

void updateAnimations(float deltaTime) {
    // 1. Trophy Rotation
    anim.trophyRotation += deltaTime * 30.0f;
    if (anim.trophyRotation > 360.0f) anim.trophyRotation -= 360.0f;
    
    // 2. Ball Rotation
    anim.ballRotation += deltaTime * 45.0f;
    if (anim.ballRotation > 360.0f) anim.ballRotation -= 360.0f;
    
    // 3. Statue Idle
    anim.statueAngle = sin(glutGet(GLUT_ELAPSED_TIME) / 1000.0f * 0.5f) * 2.0f;
    
    // 4. Spotlight Moving
    anim.spotlightAngle += deltaTime * 15.0f;
    if (anim.spotlightAngle > 360.0f) anim.spotlightAngle -= 360.0f;
    
    // 5. Door Animation
    if (anim.isDoorOpen && anim.doorOpen < 1.0f) {
        anim.doorOpen += deltaTime * 1.5f;
        if (anim.doorOpen > 1.0f) anim.doorOpen = 1.0f;
    } else if (!anim.isDoorOpen && anim.doorOpen > 0.0f) {
        anim.doorOpen -= deltaTime * 1.5f;
        if (anim.doorOpen < 0.0f) anim.doorOpen = 0.0f;
    }
    
    // 6. Slideshow
    static float photoTimer = 0;
    photoTimer += deltaTime;
    if (photoTimer > 5.0f) {
        photoTimer = 0.0f;
        anim.photoIndex = fmod(anim.photoIndex + 1.0f, 10.0f);
    }
    
    // 7. Celebration
    if (anim.celebrationTimer > 0) {
        anim.celebrationTimer -= deltaTime;
        for (auto& p : celebrationParticles) {
            if (!p.active && rand() % 100 < 5) {
                p.active = true;
                p.x = (rand() % 40 - 20) / 10.0f;
                p.y = (rand() % 20) / 10.0f;
                p.z = (rand() % 40 - 20) / 10.0f;
                p.vx = (rand() % 40 - 20) / 100.0f;
                p.vy = (rand() % 30 + 10) / 100.0f;
                p.vz = (rand() % 40 - 20) / 100.0f;
                p.life = p.maxLife;
            }
        }
    }
    
    // 8. Dust particles
    for (auto& p : dustParticles) {
        p.x += p.vx * deltaTime;
        p.y += p.vy * deltaTime;
        p.z += p.vz * deltaTime;
        p.life += deltaTime;
        if (p.life > p.maxLife) {
            p.x = (rand() % 200 - 100) / 10.0f;
            p.y = (rand() % 20) / 10.0f + 0.5f;
            p.z = (rand() % 200 - 100) / 10.0f;
            p.life = 0;
        }
    }
    
    // 9. Rain
    if (anim.rainIntensity > 0) {
        for (auto& p : rainParticles) {
            p.x += p.vx * deltaTime * 10;
            p.y += p.vy * deltaTime * 10;
            p.z += p.vz * deltaTime * 10;
            if (p.y < 0) {
                p.x = (rand() % 400 - 200) / 10.0f;
                p.y = (rand() % 40) / 10.0f + 2.0f;
                p.z = (rand() % 400 - 200) / 10.0f;
            }
        }
    }
    
    // 10. Auto Tour
    if (anim.isAutoTour) {
        anim.autoTourProgress += deltaTime * 0.05f;
        if (anim.autoTourProgress > 1.0f) anim.autoTourProgress = 0.0f;
    }
}

void renderAnimations() {
    // Render dust particles
    glDisable(GL_LIGHTING);
    glColor4f(0.8f, 0.8f, 0.8f, 0.3f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (const auto& p : dustParticles) {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    
    // Render rain
    if (anim.rainIntensity > 0) {
        glColor4f(0.6f, 0.7f, 0.9f, 0.3f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        for (const auto& p : rainParticles) {
            if (p.y > 0) {
                glVertex3f(p.x, p.y, p.z);
                glVertex3f(p.x + p.vx * 0.1f, p.y + p.vy * 0.1f, p.z + p.vz * 0.1f);
            }
        }
        glEnd();
    }
    
    // Render celebration
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    for (const auto& p : celebrationParticles) {
        if (p.active && p.life > 0) {
            float r = (sin(p.life * 2.0f) + 1.0f) * 0.5f;
            float g = (cos(p.life * 1.5f) + 1.0f) * 0.5f;
            float b = (sin(p.life * 2.5f + 1.0f) + 1.0f) * 0.5f;
            glColor3f(r, g, b);
            glVertex3f(p.x, p.y, p.z);
        }
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void toggleAutoTour() {
    anim.isAutoTour = !anim.isAutoTour;
    std::cout << "Auto Tour: " << (anim.isAutoTour ? "ON" : "OFF") << std::endl;
}

void triggerCelebration() {
    anim.celebrationTimer = 3.0f;
    for (auto& p : celebrationParticles) {
        p.active = true;
        p.x = (rand() % 40 - 20) / 10.0f;
        p.y = (rand() % 20) / 10.0f;
        p.z = (rand() % 40 - 20) / 10.0f;
        p.vx = (rand() % 40 - 20) / 100.0f;
        p.vy = (rand() % 30 + 10) / 100.0f;
        p.vz = (rand() % 40 - 20) / 100.0f;
        p.life = p.maxLife;
    }
}

bool getAutoTourStatus() { return anim.isAutoTour; }
float getTrophyRotation() { return anim.trophyRotation; }
float getBallRotation() { return anim.ballRotation; }
float getStatueAngle() {
    return anim.statueAngle;
}