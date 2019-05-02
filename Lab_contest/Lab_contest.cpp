/*РАЗРАБОТАНО MADZEROPIE И STEP_TO_VICTORY ДЛЯ УЧАСТИЯ В КОНКУРСЕ ПРОГРАММНЫХ ПРОЕКТОВ. ВСЕ ПРАВА ЗАЩИЩЕНЫ.*/

#include "pch.h"
#include <iostream>
#include "Row.h"
#include "rational.h"
#include "Matrix.h"
#include "SLAU.h"

const int NotUsed = system("color F1");//Цвет консоли

void menu(bool file_out=false) {
	vector<const char*> menu = { "Задать СЛАУ ",
		"Решение СЛАУ методом Гаусса",
		"Решение СЛАУ методом Жордана-Гаусса ",
		"Интерактивный метод Гаусса ",
		"Выход" }; // Пункты меню

	int ch = -1;//Переменная выбора пункта меню
	SLAU<rational> rslau;//СЛАУ для rational
	SLAU<float> flslau;//СЛАУ для float
	bool slau_ex = false;//Существование СЛАУ
	bool rat_overflow = false; //Переполнение rational
	ofstream fout; //Файл
	string filename = "output.txt"; //Путь файла
	if (file_out) {
		fout.open(filename, ofstream::app);
		if (!fout.is_open())
		{
			cout << "Не удалось открыть файл " << filename;
			file_out = false;
		}
	}
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
			if(file_out) {
				fout << "Исходная система: " << endl;
				rslau.Show_in_file(fout, true);
			}
			if(file_out) fout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			cout << "Выполняется метод Гаусса для десятичных дробей (float)..." << endl;
			flslau.Gauss_forw(file_out);
			
			try {
				if (file_out) fout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
				cout << "Выполняется метод Гаусса для рациональных дробей (rational)..." << endl;
				rslau.Gauss_forw(file_out);
			}
			catch (const std::overflow_error& ex)
			{
				if (file_out) fout << ex.what() << '\n';
				std::cerr << ex.what() << '\n';
				rat_overflow = true;
			}
			cout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			if(file_out) fout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol(file_out);
			if (!rat_overflow) {
				try {
					rslau.Gauss_back();
					rslau.Show_sol(file_out);
				}
				catch (const std::overflow_error& ex)
				{
					if (file_out) fout << ex.what() << '\n';
					std::cerr << ex.what() << '\n';
					rat_overflow = true;
				}
			}
			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				if (file_out) fout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res(file_out);
				if (!rat_overflow) {
					if(file_out) fout << "Невязка для рациональных дробей (rational) :" << endl;
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res(file_out);
				}
			}
			if(file_out) fout.close();
			break;
		case 3:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			rat_overflow = false;
			if (file_out) {
				fout << "Исходная система: " << endl;
				rslau.Show_in_file(fout, true);
			}
			if (file_out) fout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			cout << "Выполняется метод Жордана-Гаусса для десятичных дробей (float)..." << endl;
			flslau.JGauss(file_out);
			
			try {
				if (file_out) fout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
				cout << "Выполняется метод Жордана-Гаусса для рациональных дробей (rational)..." << endl;
				rslau.JGauss(file_out);
			}
			catch (const std::overflow_error& ex)
			{
				if (file_out) fout << ex.what() << '\n';
				std::cerr << ex.what() << '\n';
				rat_overflow = true;
			}
			cout << "Метод Жордана-Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			if(file_out) fout << "Метод Жордана-Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol(file_out);

			if (!rat_overflow) {
				try {
					rslau.Gauss_back();
					rslau.Show_sol(file_out);
				}
				catch (const std::overflow_error& ex)
				{
					if (file_out) fout << ex.what() << '\n';
					std::cerr << ex.what() << '\n';
					rat_overflow = true;
				}
			}

			if (flslau.sol_ex()) {
				if (file_out) fout << "Невязка для десятичных дробей (float) :" << endl;
				cout << "Невязка для десятичных дробей (float) :" << endl;
				flslau.check_res(file_out);
				if (!rat_overflow) {
					if (file_out) fout << "Невязка для рациональных дробей (rational) :" << endl;
					cout << "Невязка для рациональных дробей (rational) :" << endl;
					rslau.check_res(file_out);
				}
			}
			break;
		case 4:
			if (!slau_ex) { system("cls"); cout << "Cначала создайте СЛАУ." << endl; break; }
			flslau.interactive(file_out);
			cout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			if (file_out) fout << "Метод Гаусса завершен." << endl << "Идет формирование решений... " << endl;
			flslau.Gauss_back();
			flslau.Show_sol(file_out);

			if (flslau.sol_ex()) {
				cout << "Невязка для десятичных дробей (float) :" << endl;
				if (file_out) fout << "Невязка для десятичных дробей (float) :" << endl;
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
	bool file_out;//Вывод промежуточных преобразований
	cout << "Сохранять промежуточные преборазования в файл? Y/N ";
	file_out = get_ch();
	menu(file_out);
	return 0;
}
