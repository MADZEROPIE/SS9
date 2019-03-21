// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Row.h"

int main()
{
	Row<int> k;
	k.Input();
	k.Show();
	Row<int> z(k);
	//z = k * (-3);
	z.Show();
	k.Show();
	z -= k;
	z.Show();
}
