@echo off
echo ========================================
echo  MUSEUM VIRTUAL 3D CR7 - COMPILING...
echo ========================================

echo Compiling main.cpp...
g++ -c main.cpp -o main.o

echo Compiling camera.cpp...
g++ -c camera.cpp -o camera.o

echo Compiling lighting.cpp...
g++ -c lighting.cpp -o lighting.o

echo Compiling textures.cpp...
g++ -c textures.cpp -o textures.o

echo Compiling objects.cpp...
g++ -c objects.cpp -o objects.o

echo Compiling animations.cpp...
g++ -c animations.cpp -o animations.o

echo Compiling interactions.cpp...
g++ -c interactions.cpp -o interactions.o

echo Compiling museum_layout.cpp...
g++ -c museum_layout.cpp -o museum_layout.o

echo Linking...

REM Coba opsi 1: -lglut32 (untuk glut32.dll)
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lglut32 -g

if exist museum_cr7.exe goto success

REM Coba opsi 2: -lfreeglut (untuk freeglut)
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lfreeglut -g

if exist museum_cr7.exe goto success

REM Coba opsi 3: -lglut (tanpa angka)
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -lglut -g

if exist museum_cr7.exe goto success

REM Coba opsi 4: link langsung ke file .a
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -g "C:/msys64/ucrt64/lib/libglut.a"

if exist museum_cr7.exe goto success

REM Coba opsi 5: link langsung ke file .a (nama berbeda)
g++ main.o camera.o lighting.o textures.o objects.o animations.o interactions.o museum_layout.o -o museum_cr7.exe -lopengl32 -lglu32 -g "C:/msys64/ucrt64/lib/libfreeglut.a"

if exist museum_cr7.exe goto success

:fail
echo ========================================
echo  COMPILE FAILED!
echo  Please check your GLUT installation.
echo ========================================
goto end

:success
echo ========================================
echo  COMPILE SUCCESS!
echo  Run: museum_cr7.exe
echo ========================================

:end
pause