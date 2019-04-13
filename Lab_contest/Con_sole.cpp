#include "pch.h"
#include "Con_sole.h"

void gotoxy(COORD coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(x),SHORT(y) });
}
void drawline(int x, int y, int l)
{
	COORD cur=get_coords();
	char border = char(166);
	gotoxy(x, y);
	for (int i = 0; i < l; ++i)
	{
		gotoxy(x, y + i);
		cout << border;
	}
	gotoxy(cur);
}
void move_cur(COORD coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD get_coords()
{
	pair<int, int>a;
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return cbsi.dwCursorPosition;
}