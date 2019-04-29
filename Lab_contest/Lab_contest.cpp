﻿/*РАЗРАБОТАНО MADZEROPIE И STEP_TO_VICTORY ДЛЯ УЧАСТИЯ В КОНКУРСЕ ПРОГРАММНЫХ ПРОЕКТОВ. ВСЕ ПРАВА ЗАЩИЩЕНЫ.*/

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"
#include "SLAU.h"

const int NotUsed = system("color F1");//Цвет консоли

void menu() {

	vector<const char*> menu = { "Задать СЛАУ ",
		"Решение СЛАУ методом Гаусса",
		"Решение СЛАУ методом Жордана-Гаусса ",
		"Интерактивный метод Гаусса ",
		"Выход" }; // Пункты меню

	int ch = -1;//Переменная выбора пункта меню
	SLAU<rational> rslau;//СЛАУ для rational
	SLAU<float> flslau;//СЛАУ для float
	bool slau_ex = false;//Существование СЛАУ
	bool step_sh;//Вывод промежуточных преобразований
	bool rat_overflow = false; //Переполнение rational
	while (true) {
		do
		{
			cout << "Выберите пункт меню: " << endl;
			for (auto i = 0; i < menu.size(); ++i) cout << i+1 << ". " << menu[i] << endl;
			cin >> ch;
			if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); ch = -1; system("cls");}
		} while (ch <= 0 || ch > menu.size());
		switch (ch)
		{
		case 1:
			rslau.Input();
			flslau = rslau;
			slau_ex = true;
			rat_overflow = false;
			break;
		case 2:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			rat_overflow = false;
			cout << "Выводить промежуточные преборазования с комментариями? Y/N";
			step_sh = get_ch();
			
			cout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			flslau.Gauss_forw(step_sh);
			
			try {
				cout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
				rslau.Gauss_forw(step_sh);
			}
			catch (const std::overflow_error& ex)
			{
				std::cerr << ex.what() << '\n';
				rat_overflow = true;
			}
			cout << "Метод Гаусса завершен." << endl;
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();
			if (!rat_overflow) {
				try {
					rslau.Gauss_back();
					rslau.Show_sol();
				}
				catch (const std::overflow_error& ex)
				{
					std::cerr << ex.what() << '\n';
					rat_overflow = true;
				}
			}

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();

				if (!rat_overflow) {
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res();
				}
			}
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			rat_overflow = false;
			cout << "Выводить промежуточные преборазования с комментариями? Y/N";
			step_sh = get_ch();
			
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			flslau.JGauss(step_sh );
			
			try {
				cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
				rslau.JGauss(step_sh);
			}
			catch (const std::overflow_error& ex)
			{
				std::cerr << ex.what() << '\n';
				rat_overflow = true;
			}
			cout << "Метод Жордана-Гаусса завершен." << endl;
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();

			if (!rat_overflow) {
				try {
					rslau.Gauss_back();
					rslau.Show_sol();
				}
				catch (const std::overflow_error& ex)
				{
					std::cerr << ex.what() << '\n';
					rat_overflow = true;
				}
			}

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();

				if (!rat_overflow) {
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res();
				}
			}
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Выводить пояснения? Y/N";
			step_sh = get_ch();
			
			flslau.interactive(step_sh);
			cout << "Метод Гаусса завершен." << endl;
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();	
			}
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
