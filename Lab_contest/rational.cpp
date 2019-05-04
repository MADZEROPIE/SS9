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

bool rational::operator==(const rational& a)
{
	return ((p*a.q) == (a.p*q));
}

bool rational::operator!=(const rational& a)
{
	return ((p*a.q) != (a.p*q));
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
	#ifdef SAFE_RAT
	res.p = safe_add(safe_mult(a.p, b.q), safe_mult(b.p, a.q));
	res.q = safe_mult(a.q, b.q);
	#else
	res.p = a.p* b.q + b.p* a.q;
	res.q = a.q* b.q;
	#endif 
	del(res);
	return res;
}

rational operator-(const rational & a, const rational & b)
{
	rational res;
	#ifdef SAFE_RAT
	res.p = safe_sub(safe_mult(a.p,b.q), safe_mult(b.p,a.q));
	res.q = safe_mult(a.q,b.q);
	#else
	res.p = a.p* b.q - b.p* a.q;
	res.q = a.q* b.q;
	#endif 
	del(res);
	return res;
}

rational operator*(const rational & a, const rational & b)
{
	rational res;
	#ifdef SAFE_RAT
	res.p = safe_mult(a.p,b.p);
	res.q = safe_mult(a.q,b.q);
	#else
	res.p = a.p* b.p;
	res.q = a.q* b.q;
	#endif 
	del(res);
	return res;
}

rational operator/(const rational & a, const rational & b)
{
	rational res;
	#ifdef SAFE_RAT
	res.p = safe_mult(a.p,b.q);
	res.q = safe_mult(a.q,b.p);
	#else
	res.p = a.p* b.q;
	res.q = a.q* b.p;
	#endif 
	del(res);
	return res;
}

void del(rational& a)
{
	int64_t tmp = gcd(abs(a.p), abs(a.q)); // При вызове abs, если число равно LLONG_MIN, abs вернет LLONG_MIN => gcd = отрицат. числу => если он равен -1, то будет переполнение
	if (tmp == -1||tmp == 0) throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
	a.p /= tmp;
	a.q /= tmp;
	if (a.p < 0 && a.q < 0) {
		a.p *= -1;
		a.q *= -1;
	}
}



int64_t gcd(int64_t a, int64_t b) {
	if (a == 0) return b;
	return gcd(b%a, a);
}

rational abs(const rational& b)
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

#ifdef SAFE_RAT
int64_t safe_mult(int64_t a, int64_t b)
{
	if (a > 0 && ((b>0 && a > LLONG_MAX / b)||(b<0 && b<LLONG_MIN/a )))  throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
	if (a < 0 && (( b < 0 && b < LLONG_MAX / a) || (b > 0 && a < LLONG_MIN / b))) throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
	return a*b;
}

int64_t safe_add(int64_t a, int64_t b)
{
	if (((b > 0) && (a > (LLONG_MAX - b))) || ((b < 0) && (a < (LLONG_MIN - b)))) {
		throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
	}
	return a + b;
}


int64_t safe_sub(int64_t a, int64_t b)
{
	return safe_add(a,-b);
}

int64_t safe_div(int64_t  a, int64_t  b)
{
	if (b==0 || (a==LLONG_MIN && b==-1)) throw overflow_error("Переполнение. Дальнейшая работа с rational невозможна.");
	return a / b;
}
#endif

ostream & operator<<(ostream& stream, const rational& a)
{	
	if (stream.width() == fstep)
	{
		stream.width(fstep / 2 - !(fstep % 2));
		stream <<right<< a.p << "/";
		stream.width(fstep / 2);
		stream << left << a.q;
	}
	else
		stream << a.p << "/" << a.q;
		
	return stream;
}

istream & operator>>(istream& stream, rational& a)
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
	if (flag) {
		(num != 0) ? a.q = num : a.q = 1;
	}
	else
	{
		a.p = num;
		a.q = 1;
	}
	del(a);
	return stream;
}
