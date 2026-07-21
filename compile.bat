@echo off
echo ========================================
echo  MUSEUM VIRTUAL 3D CR7 - COMPILING...
echo ========================================

echo Cleaning old files...
del *.o 2>nul
del museum_cr7.exe 2>nul

echo Compiling...
g++ -c main.cpp -o main.o
g++ -c camera.cpp -o camera.o
g++ -c lighting.cpp -o lighting.o
g++ -c textures.cpp -o textures.o
g++ -c objects.cpp -o objects.o
g++ -c animations.cpp -o animations.o
g++ -c interactions.cpp -o interactions.o
g++ -c museum_layout.cpp -o museum_layout.o
g++ -c sound.cpp -o sound.o
g++ -c ui.cpp -o ui.o
g++ -c floor2.cpp -o floor2.o

echo Linking...
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o sound.o ui.o floor2.o -o museum_cr7.exe -lopengl32 -lglu32 -lfreeglut -lwinmm

if exist museum_cr7.exe goto success

echo Trying alternative...
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lfreeglut

if exist museum_cr7.exe goto success

:fail
echo ========================================
echo  COMPILE FAILED!
echo ========================================
goto end

:success
echo ========================================
echo  COMPILE SUCCESS!
echo  Run: museum_cr7.exe
echo ========================================

:end
pause