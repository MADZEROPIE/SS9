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

void drawx(int x, int y, int n)
{
	
	drawline(x, y, n);
	drawline(x + 5, y, n);
	for (int i = 1; i <= n; ++i)
	{
		gotoxy(x + 1, y + i - 1);
		cout << "x" << i;
	}
	gotoxy(x + 6, y);
}

bool get_ch()
{
	char ch = 'L';
	while (ch != 'Y' && ch != 'N' && ch != '0' && ch != '1') cin >> ch;
	return (ch == 'Y' || ch == '1');
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