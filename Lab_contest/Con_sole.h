#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

const int step = 10;

COORD get_coords();
void gotoxy(int x, int y);
void gotoxy(COORD coord);
void drawline(int x, int y, int l);
void move_cur(COORD);
void drawx(int x, int y, int n);