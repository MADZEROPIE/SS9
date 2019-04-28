#include "pch.h"
#include "rational.h"

bool rational::operator>(const rational & a)
{
	return ((p*a.q)>(a.p*q));
}

bool rational::operator<(const rational & a)
{
	return ((p*a.q) < (a.p*q));
}

bool rational::operator>=(const rational & a)
{
	return ((p*a.q) >= (a.p*q));
}

bool rational::operator<=(const rational & a)
{
	return ((p*a.q) <= (a.p*q));
}

bool rational::operator==(int a)
{
	return (a*q == p);
}

bool rational::operator!=(int a)
{
	return (a*q != p);
}

rational::rational()
{
	p = 0; q = 1;
}

rational::rational(int a)
{
	p = a;
	q = 1;
}

rational & rational::operator=(int a)
{
	p = a;
	q = 1;
	return *this;
}

rational & rational::operator+=(const rational & a)
{
	*this = *this + a;
	return *this;
}

rational & rational::operator-=(const rational & a)
{
	*this = *this - a;
	return *this;
}

rational & rational::operator*=(const rational & a)
{
	*this = *this * a;
	return *this;
}

rational & rational::operator/=(const rational & a)
{
	*this = *this / a;
	return *this;
}

rational operator+(const rational & a, const rational & b)
{
	rational res;
	res.p = a.p*b.q + b.p*a.q;
	res.q = a.q*b.q;
	del(res);
	return res;
}

rational operator-(const rational & a, const rational & b)
{
	rational res;
	res.p = a.p*b.q - b.p*a.q;
	res.q = a.q*b.q;
	del(res);
	return res;
}

rational operator*(const rational & a, const rational & b)
{
	rational res;
	res.p = a.p*b.p;
	res.q = a.q*b.q;
	del(res);
	return res;
}

rational operator/(const rational & a, const rational & b)
{
	rational res;
	res.p = a.p*b.q;
	res.q = a.q*b.p;
	del(res);
	return res;
}

void swap(rational &a, rational&b)
{
	rational tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void del(rational & a)
{
	if (a.p <= LONG_MAX && a.p >= LONG_MIN && a.q <= LONG_MAX && a.q >= LONG_MIN) {
		int64_t tmp = gcd(abs(a.p), abs(a.q));
		a.p /= tmp;
		a.q /= tmp;
		if (a.p < 0 && a.q < 0) {
			a.p *= -1;
			a.q *= -1;
		}
	}
	else throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
}



int64_t gcd(int64_t a, int64_t b) {
	if (a == 0) return b;
	return gcd(b%a, a);
}

rational abs(const rational &b)
{
	rational res;
	if (b.p < 0)
	{
		res.p = -b.p;
		res.q = b.q;
	}
	else if (b.q<0)
	{
		res.p = b.p;
		res.q = -b.q;
	}
	else
	{
		res.p = b.p;
		res.q = b.q;
	}
	return res;
	
}

ostream & operator<<(ostream & stream, const rational &a)
{
	stream << a.p << "/" << a.q;
	return stream;
}

istream & operator>>(istream & stream, rational & a)
{
	string str;
	stream >> str;
	int num = 0;
	bool flag = false;
	for (int i = 0, tmp = 1; i < str.size(); ++i) {
		if (str[i] == '-' && i==0) tmp = -1;
		else if (str[i] == '/')
		{
			tmp = 1;
			a.p = num;
			num = 0;
			flag = true;
		}
		else if (str[i]<'0' || str[i]>'9')
		{
			str.clear(); stream >> str; num = 0; flag = false; i = -1; a.p = 0; a.q = 0;
		}
		else
			num = (num * 10 + (str[i] - '0')*tmp);
	}
	if (flag)
		a.q = num;
	else
	{
		a.p = num;
		a.q = 1;
	}
	del(a);
	return stream;
}
