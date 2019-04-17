// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"
#include "SLAU.h"


void menu() {
	vector<const char*> menu = { "Задать СЛАУ ","Решение СЛАУ методом Гаусса","Решение СЛАУ методом Жордана-Гаусса ","Интерактивный метод Гаусса ","Вывод результатов ","Выход" };
	int ch = -1;
	SLAU<int> tslau;
	SLAU<rational> rslau;
	SLAU<float> flslau;
	bool slau_ex = false;
	while (true) {
		do
		{
			cout << "Выберете пункт меню " << endl;
			for (auto i = 0; i < menu.size(); ++i) cout << i+1 << ". " << menu[i] << endl;
			cin >> ch;
		} while (ch <= 0 || ch > menu.size());
		switch (ch)
		{
		case 1:
			tslau.new_Input();
			rslau = tslau;
			flslau = tslau;
			slau_ex = true;
			break;
		case 2:
			if (!slau_ex) { cout << "Cначала создайте СЛАУ"; break; }
			cout << "Выполняется метод Гаусса для десятичных дробей (float)" << endl;
			flslau.Gauss_forw();
			cout << "Выполняется метод Гаусса для рациональных дробей (rational)" << endl;
			rslau.Gauss_forw();
			break;
		case 3:
			if (!slau_ex) { cout << "Cначала создайте СЛАУ"; break; }
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)" << endl;
			flslau.Gauss_forw();
			cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)" << endl;
			rslau.Gauss_forw();
			break;
		case 4:
			cout << "ТУТ ДОЛЖЕН БЫТЬ ИНТЕРАКТИВ, но его НЕТ" << endl;
			break;
		case 5:
			cout << "Идет формирование решений " << endl;
			flslau.Gauss_back();
			rslau.Gauss_back();
			cout<<"Невязка для десятичных дробей (float) :" << endl;
			flslau.check_res();
			cout << "Невязка для рациональных дробей (rational) :" << endl;
			rslau.check_res();
			break;
		default:
			return;
			break;
		}
	}
}




int main()
{
	setlocale(LC_ALL, "Russian");
	menu();
	
	return 0;
}
