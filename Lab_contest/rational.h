#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

struct rational
{
	int64_t p;//ДЕЛИТЕЛЬ
	int64_t q;//ЗНАМЕНАТЕЛЬ

	//Операторы сравнения
	bool operator > (const rational& a);
	bool operator < (const rational& a);
	bool operator >= (const rational& a);
	bool operator <= (const rational& a);
	bool operator ==(int a);
	bool operator!=(int a);

	//Конструкторы
	rational();
	rational(int);

	//Перегруженные операции
	rational& operator= (int a);
	rational& operator +=(const rational& a);
	rational& operator -=(const rational& a);
	rational& operator *=(const rational& a);
	rational& operator /=(const rational& a);

	//Приведение типов
	operator double() {	return double(p) / q;	}
	operator float() {	return float(p) / q;	}
};

//Перегруженные операции
rational operator+ (const rational& a,const rational& b);
rational operator- (const rational& a, const rational& b);
rational operator* (const rational& a, const rational& b);
rational operator/ (const rational& a, const rational& b);

void swap(rational& a, rational& b);
void del(rational& a);//Сокращение дроби
int64_t gcd(int64_t, int64_t);//НОД
rational abs(const rational&);//Модуль

ostream& operator<<(ostream& stream,const rational& a);	//Перегруженный потоковый вывод
istream& operator>>(istream& stream, rational& a);	//Перегруженный потоковый ввод
