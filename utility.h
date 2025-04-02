#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void goToXY(int x, int y);

int clamp(int a, int n, int b);

void sleep_1(long milli);

void printASCII(string filename, int rows, int cols, int theme);

void deleteASCII(int cols, int rows, int highLight);
