#pragma once
#include <iostream>
#include <conio.h>
#include "utility.h"
#include "struct.h"
#include "graphic.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13
#define H_KEY 104

using namespace std;

NodeTile *createNodeTile(int x, int y, char value);

void addTail(NodeTile *&head, int x, int y, char value);

NodeTile *goToNode(NodeTile **board, int x, int y);

void renderBoard(NodeTile** board, int theme);

void deleteNode(NodeTile **board, int x, int y);

NodeTile **generateAdvancedBoard(int &m, int &n);

int checkIMatchYAxis(NodeTile **board, int y1, int y2, int x);

int checkIMatchXAxis(NodeTile **board, int x1, int x2, int y);

bool checkLMatch(NodeTile **board, int x1, int y1, int x2, int y2);

int checkZAndUMatch(NodeTile **board, int m, int n, int x1, int y1, int x2, int y2);

bool checkforMatch(NodeTile **board, int m, int n, int x1, int y1, int x2, int y2);

void getInput(NodeTile **board, int m, int n, int &xPos, int &yPos, int &numLocked, char c);

bool clearChoices(NodeTile **board, int x1, int y1, int x2, int y2, int &numLocked, bool check);

bool checkMatching(NodeTile **board, int m, int n, int &numLocked, int theme, int &score, int &streak);

void suggestMove(NodeTile **board, int m, int n);

bool checkForAvailableMove(NodeTile **board, int m, int n);

void advancedMode(int theme);

void deleteBoard(NodeTile ** board, int height);



