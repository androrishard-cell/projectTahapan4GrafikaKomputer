@echo off
echo ========================================
echo  MUSEUM VIRTUAL 3D CR7 - COMPILING...
echo ========================================

echo Compiling...
g++ -c main.cpp -o main.o
g++ -c camera.cpp -o camera.o
g++ -c lighting.cpp -o lighting.o
g++ -c textures.cpp -o textures.o
g++ -c objects.cpp -o objects.o
g++ -c animations.cpp -o animations.o
g++ -c interactions.cpp -o interactions.o
g++ -c museum_layout.cpp -o museum_layout.o

echo Linking...
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lfreeglut

if exist museum_cr7.exe (
    echo ========================================
    echo  COMPILE SUCCESS!
    echo  Run: museum_cr7.exe
    echo ========================================
) else (
    echo ========================================
    echo  COMPILE FAILED! Trying alternative...
    echo ========================================
    g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lglut
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
)

pause