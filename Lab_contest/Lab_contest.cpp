// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	/*Row<int> k;
	k.Input();
	k.Show();
	Row<int> z(k);
	//z = k * (-3);
	z.Show();
	k.Show();
	z -= k;
	z.Show();*/
	//rational a;
	Matrix<int> b;
	b.Input();
	b.Show();
	Matrix<int> c(b);
	c.Show();
	c.Input();
	Matrix<int> z(2, 4);
	z = c;
	z.Show();
	//cin >> a;
	//cout << a;
}
