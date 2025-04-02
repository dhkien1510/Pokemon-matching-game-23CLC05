#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>

#include "utility.h"

using namespace std;

void getBackground(char bg[][41]);

void renderHiddenImage(char bg[][41], int x1, int y1, int theme);

void matchColorBox(int x, int y, int state, int theme);

void renderInstruction(int theme, int score, int streak);

int startGame(int theme);

int gameState(int theme, int state, int score, int streak);

int checkTheme(int theme, int &highLight, int &word);
