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
	if(a*q!=p) return false;
	else return true;
}

bool rational::operator!=(int a)
{
	if (a*q==p) return false;
	else return true;
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
	int64_t tmp = gcd(abs(a.p), abs(a.q));
	a.p /= tmp;
	a.q /= tmp;
	if (a.p < 0 && a.q < 0) {
		a.p *= -1;
		a.q *= -1;
	}
}

void set(rational & a)
{
	char t;
	do { cin >> a.p >> t >> a.q; } while (!a.q);

}

rational set()
{
	rational a; char t;
	do { cin >> a.p >> t >> a.q; } while (!a.q);

	return a;
}

void show(const rational & a)
{
	cout << a.p << "/" << a.q;
}


void show(const double& a) {
	cout << a;
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
	bool flag = 0;
	for (int i = 0; i < str.size(); ++i)
		if (str[i] == '/')
		{
			a.p = num;
			num = 0;
			flag = 1;
		}
		else
			num = (num * 10 + (str[i] - '0'));
	if (flag)
		a.q = num;
	else
	{
		a.p = num;
		a.q = 1;
	}
	return stream;
}
