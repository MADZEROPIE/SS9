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
	ofstream fout; //Файл
	string filename = "output.txt"; //Путь файла
	bool file_out;
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
			break;
		case 2:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Сохранять промежуточные преобразования в файл "<<filename<<"? Y/N ";
			file_out = get_ch();
			cout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			flslau.Gauss_forw(file_out, filename);

			cout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
			rslau.Gauss_forw(file_out, filename);
	
			cout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			if(file_out) fout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back(file_out);
			flslau.Show_sol(file_out, filename);
			if (!rslau.rat_over()) {
				rslau.Gauss_back(file_out);
				rslau.Show_sol(file_out, filename);
			}
			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res(file_out, filename);
				if (!rslau.rat_over()) {
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res(file_out, filename);
				}
			}
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Сохранять промежуточные преобразования в файл " << filename << "? Y/N ";
			file_out = get_ch();
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			flslau.JGauss(file_out, filename);
			
			cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
			rslau.JGauss(file_out, filename);
			
			cout << "Метод Жордана-Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back(file_out);
			flslau.Show_sol(file_out, filename);

			if (!rslau.rat_over()) {
				rslau.Gauss_back(file_out);
				rslau.Show_sol(file_out, filename);
			}

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res(file_out, filename);
				if (!rslau.rat_over()) {
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res(file_out, filename);
				}
			}
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Сохранять промежуточные преобразования в файл " << filename << "? Y/N ";
			file_out = get_ch();
			flslau.interactive(file_out);
			cout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back(file_out);
			flslau.Show_sol(file_out);
			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res(file_out);
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
