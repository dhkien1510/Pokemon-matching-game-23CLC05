#pragma once
#include <iostream>

#include "graphic.h"

using namespace std;

#define BOARDWIDTH 8
#define BOARDHEIGTH 5

struct Tile {
	int x, y;
	char value = ' ';
	bool isEmpty = false;
	bool isSelected = false;
    bool isLocked = false;
    bool isHinted = false;
	void drawBox(int, char[][41]);
    void deleteBox();
};

struct NodeTile {
    int x, y;
    char value;
    bool isSelected = false;
    bool isLocked = false;
    bool isHinted = false;
    bool isEmpty = false;
    NodeTile *next;
    void drawBox(int);
    void deleteBox();
};
