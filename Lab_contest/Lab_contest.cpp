// Lab_contest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"
#include "SLAU.h"

/*0 = Black 8 = Gray
1 = Blue 9 = Light Blue
2 = Green A = Light Green
3 = Aqua B = Light Aqua
4 = Red C = Light Red
5 = Purple D = Light Purple
6 = Yellow E = Light Yellow
7 = White F = Bright White*/

const int NotUsed = system("color F1");

void menu() {

	vector<const char*> menu = { "Задать СЛАУ ",
		"Решение СЛАУ методом Гаусса",
		"Решение СЛАУ методом Жордана-Гаусса ",
		"Интерактивный метод Гаусса ",
		"Выход" }; // Пункты меню

	int ch = -1;
	SLAU<rational> rslau;
	SLAU<float> flslau;
	bool slau_ex = false;
	bool step_sh;
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
			
			cout << "Выводить промежуточные преборазования с комментариями? ";
			step_sh = get_ch();
			
			cout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			flslau.Gauss_forw(step_sh);
			
			cout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
			rslau.Gauss_forw(step_sh);

			cout << "Метод Гаусса завершен." << endl;
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();

			rslau.Gauss_back();
			rslau.Show_sol();

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();

				cout << "Невязка для рациональных дробей (rational) :" << endl;
				rslau.check_res();
			}
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			
			cout << "Выводить промежуточные преборазования с комментариями? ";
			step_sh = get_ch();
			
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			flslau.JGauss(step_sh );
			
			cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
			rslau.JGauss(step_sh);
			
			cout << "Метод Жордана-Гаусса завершен." << endl;
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();

			rslau.Gauss_back();
			rslau.Show_sol();

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();

				cout << "Невязка для рациональных дробей (rational) :" << endl;
				rslau.check_res();
			}
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Выводить пояснения? ";
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
