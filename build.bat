@echo off
echo === Building game ===

g++ ^
main.cpp ^
core/*.cpp ^
entity/*.cpp ^
world/*.cpp ^
console/*.cpp ^
-o game.exe ^
-std=c++17 ^
-Wall

if %errorlevel% neq 0 (
    echo BUILD FAILED
    pause
    exit /b
)

echo BUILD SUCCESS
pause