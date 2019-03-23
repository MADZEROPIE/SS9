#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

struct rational
{
	int64_t p;//ÄÅËÈÒÅËÜ
	int64_t q;//ÇÍÀÌÅÍÀÒÅËÜ
	bool operator > (const rational& a);
	bool operator < (const rational& a);
	bool operator >= (const rational& a);
	bool operator <= (const rational& a);
	bool operator ==(int a);
	bool operator!=(int a);
	rational();
	rational(int);
	rational& operator= (int a);
	rational& operator +=(const rational& a);
	rational& operator -=(const rational& a);
	rational& operator *=(const rational& a);
	rational& operator /=(const rational& a);
};
rational operator+ (const rational& a,const rational& b);
rational operator- (const rational& a, const rational& b);
rational operator* (const rational& a, const rational& b);
rational operator/ (const rational& a, const rational& b);
void swap(rational&a, rational&b);
void del(rational& a);
void set(rational& a);
rational set();
void show(const rational& a);
void show(const double& a);
int64_t gcd(int64_t, int64_t);//ÍÎÄ

ostream& operator<<(ostream& stream,const rational& a);
istream& operator>>(istream& stream, rational& a);