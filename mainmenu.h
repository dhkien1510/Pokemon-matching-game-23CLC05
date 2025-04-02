#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <mmsystem.h> //to insert sound
#include <cstdlib> //system "cls" clearscreen
#pragma comment(lib, "winmm.lib")

#include "utility.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

using namespace std;

int changeThemeColour(int theme);

int updateTheme(int theme, int check);

int mainMenu(int theme);

