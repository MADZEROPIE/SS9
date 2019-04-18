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
	vector<const char*> menu = { "Задать СЛАУ ","Решение СЛАУ методом Гаусса","Решение СЛАУ методом Жордана-Гаусса ","Интерактивный метод Гаусса ","Вывод результатов ","Выход" };
	int ch = -1;
	SLAU<int> tslau;
	SLAU<rational> rslau;
	SLAU<float> flslau;
	bool slau_ex = false,solved=false;
	while (true) {
		do
		{
			cout << "Выберете пункт меню: " << endl;
			for (auto i = 0; i < menu.size(); ++i) cout << i+1 << ". " << menu[i] << endl;
			cin >> ch;
		} while (ch <= 0 || ch > menu.size());
		switch (ch)
		{
		case 1:
			rslau.new_Input();
			//rslau = tslau;
			flslau = rslau;
			slau_ex = true;
			solved = false;
			break;
		case 2:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ" << endl; break; }
			cout << "Выполняется метод Гаусса для десятичных дробей (float)" << endl;
			flslau.Gauss_forw();
			cout << "Выполняется метод Гаусса для рациональных дробей (rational)" << endl;
			rslau.Gauss_forw();
			solved = true;
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ" << endl; break; }
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)" << endl;
			flslau.Gauss_forw();
			cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)" << endl;
			rslau.Gauss_forw();
			solved = true;
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ" << endl; break; }
			cout << "ТУТ ДОЛЖЕН БЫТЬ ИНТЕРАКТИВ, но его НЕТ" << endl;
			break;
		case 5:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ" << endl; break; }
			else if (!solved) { system("cls"); cout << "Cначала вызовите метод Гаусса"<<endl; break; }
			cout << "Идет формирование решений " << endl;
			flslau.Gauss_back();
			rslau.Gauss_back();
			cout<<"Решение и невязка для десятичных дробей (float) :" << endl;
			flslau.check_res();
			cout << "Решение и невязка для рациональных дробей (rational) :" << endl;
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
	//rational a;
	//cin >> a;
	//cout << a;
	return 0;
}
