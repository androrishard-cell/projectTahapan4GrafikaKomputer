@echo off
echo ========================================
echo  MUSEUM VIRTUAL 3D CR7 - COMPILING...
echo ========================================

g++ -c main.cpp -o main.o -I"C:\Program Files\CodeBlocks\MinGW\include"
g++ -c camera.cpp -o camera.o
g++ -c lighting.cpp -o lighting.o
g++ -c textures.cpp -o textures.o
g++ -c objects.cpp -o objects.o
g++ -c animations.cpp -o animations.o
g++ -c interactions.cpp -o interactions.o
g++ -c museum_layout.cpp -o museum_layout.o

g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lglut32 -g

if exist museum_cr7.exe (
    echo ========================================
    echo  COMPILE SUCCESS!
    echo  Run: museum_cr7.exe
    echo ========================================
) else (
    echo ========================================
    echo  COMPILE FAILED!
    echo ========================================
)

pause