﻿// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	//Matrix<int> b;
	//b.Input();
	//b.Show();
	//b(0, 0) = 7;
	//b.Show();
	/*SLAU<double> a;
	a.Input();
	a.Show();
	cout<<a.JGauss()<<endl;
	a.Show();
	(a.Gauss_back()).Show();
	*/
	SLAU<int> a;
	a.new_Input();
	a.Show();
	//SLAU<double> b;
	//b.new_Input();
	//b = a;
	SLAU<rational> c;
	c = a;
	//b.Show();
	c.Show();
	//b.JGauss();
	//b.Gauss_back();
	c.Gauss_forw();
	c.Gauss_back();
//	b.check_res();
	c.check_res();
}
