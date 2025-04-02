#pragma once
#include <iostream>
#include <conio.h>

#include "player.h"
#include "graphic.h"
#include "struct.h"
#include "utility.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13
#define H_KEY 104

using namespace std;

Tile** generateBoard(int &m, int &n);

void renderBoard(Tile** board, int theme, char bg[][41]);

int checkIMatchYAxis(Tile **board, int y1, int y2, int x);

int checkIMatchXAxis(Tile **board, int x1, int x2, int y);

bool checkLMatch(Tile **board, int x1, int y1, int x2, int y2);

bool checkZAndUMatch(Tile **board, int m, int n, int x1, int y1, int x2, int y2);

void getInput(Tile **board, int m, int n, int &xPos, int &yPos, int &numLocked, char c);

bool clearChoices(Tile **board, int x1, int y1, int x2, int y2, int &numLocked, bool check);

bool checkforMatch(Tile **board, int m, int n, int x1, int y1, int x2, int y2);

bool checkMatching(Tile **board, int m, int n, int &numLocked, int theme, int &score, int &streak);

void shuffleBoard(Tile **board, int m, int n);

bool checkForAvailableMove(Tile **board, int m, int n);

void suggestMove(Tile **board, int m, int n);

void normalMode(int theme, player &p);

void deleteBoard(Tile ** board, int height);

