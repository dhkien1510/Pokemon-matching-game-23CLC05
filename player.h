#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <iomanip>

#include "graphic.h"
#include "utility.h"

using namespace std;

struct player {
	string name = "";
	int point, streak;
	int state; //0 - normal mode, 1 - advanced mode
	string password = "";
};

int createPlayerInfo(player &p, int &check);

bool comparePoints(const player& p1, const player& p2);

int checkOldPlayer(player &p, int &check);

void inputPlayer(int theme, player &p);

void checkLeaderBoard(player newPlayer);

void readLeaderBoard(int theme, player user);