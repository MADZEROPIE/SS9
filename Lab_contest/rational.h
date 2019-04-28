#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

struct rational
{
	int64_t p;//��������
	int64_t q;//�����������

	//��������� ���������
	bool operator > (const rational& a);
	bool operator < (const rational& a);
	bool operator >= (const rational& a);
	bool operator <= (const rational& a);
	bool operator ==(int a);
	bool operator!=(int a);

	//������������
	rational();
	rational(int);

	//������������� ��������
	rational& operator= (int a);
	rational& operator +=(const rational& a);
	rational& operator -=(const rational& a);
	rational& operator *=(const rational& a);
	rational& operator /=(const rational& a);

	//���������� �����
	operator double() {	return double(p) / q;	}
	operator float() {	return float(p) / q;	}
};

//������������� ��������
rational operator+ (const rational& a,const rational& b);
rational operator- (const rational& a, const rational& b);
rational operator* (const rational& a, const rational& b);
rational operator/ (const rational& a, const rational& b);

void swap(rational& a, rational& b);
void del(rational& a);//���������� �����
int64_t gcd(int64_t, int64_t);//���
rational abs(const rational&);//������

ostream& operator<<(ostream& stream,const rational& a);	//������������� ��������� �����
istream& operator>>(istream& stream, rational& a);	//������������� ��������� ����
