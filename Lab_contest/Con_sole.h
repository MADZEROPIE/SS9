#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

const int step = 15;

COORD get_coords();
void move_cur(COORD coord);
