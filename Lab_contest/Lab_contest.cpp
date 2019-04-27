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
		"Вывод результатов ",
		"Выход" }; // Пункты меню

	int ch = -1;
	SLAU<rational> rslau;
	SLAU<float> flslau;
	bool slau_ex = false,sol_inter=false;
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
			sol_inter = false;
			break;
		case 2:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			
			cout << "Выводить промежуточные преборазования с комментариями? ";
			step_sh = get_ch();
			
			cout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			flslau.Gauss_forw(step_sh);
			
			cout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
			rslau.Gauss_forw(step_sh);
			sol_inter = false;
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			
			cout << "Выводить промежуточные преборазования с комментариями? ";
			step_sh = get_ch();
			
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			flslau.JGauss(step_sh );
			
			cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
			rslau.JGauss(step_sh);
			sol_inter = false;
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			cout << "Выводить пояснения? ";
			step_sh = get_ch();
			
			flslau.interactive(step_sh);
			cout << "Метод Гаусса завершен." << endl;
			sol_inter = true;
			break;
		case 5:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			else if (!flslau.is_solved()) { system("cls"); cout << "Cначала вызовите метод Гаусса."<<endl; break; }
			cout << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol();
			if (!sol_inter) {
				rslau.Gauss_back();
				rslau.Show_sol();
			}
			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res();
				if (!sol_inter) {
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res();
				}
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
