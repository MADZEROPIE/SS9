// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"
#include "SLAU.h"


void menu() {

}




int main()
{
	setlocale(LC_ALL, "Russian");
	int n, m;
	SLAU<double> a;
	/*cin >> n>>m;
	a.A.cl_resize(n, m);
	a.b.resize(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> a.A[i][j];
	cout << "b" << endl;
	for (int i = 0; i < n; ++i)
		cin >> a.b[i];
		*/
	a.new_Input();
	a.Show();
	a.Gauss_forw();
	a.Gauss_back();
	cout << "fdssssssssssssssssssssssssssssssssssssssssss";
	//SLAU<double> b;
	//b = a;
	//SLAU<rational> c;
	//c = a;
	//b.Show();
	//c.Show();
	//b.JGauss();
	//b.Gauss_back();
	//c.Gauss_forw();
	//c.Gauss_back();
	//b.check_res();
	//c.check_res();
	return 0;
}
