#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int step = 12;
const int fstep = 19;

COORD get_coords();
void gotoxy(int x, int y);
void gotoxy(COORD coord);
void drawline(int x, int y, int l);
void drawx(int x, int y, int n);

bool get_ch(); // �������, ���������� ���� �� ������������