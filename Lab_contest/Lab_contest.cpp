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

	SLAU<int> a;
	a.new_Input();
	a.Show();
	
	
	SLAU<double> b;
	b = a;
	SLAU<rational> c;
	c = a;
	b.Show();
	c.Show();
	//b.JGauss();
	//b.Gauss_back();
	//c.Gauss_forw();
	//c.Gauss_back();
	//b.check_res();
	//c.check_res();
	return 0;
}
