#pragma once
#include<iostream>
#include "Con_sole.h"
using namespace std;


template <typename T>
class Row
{
private:
	vector<T> arr;//
	size_t n;//SIZE
public:
	Row();
	Row(size_t n);
	Row(const Row<T>&);
	T& operator[](int i) { return arr[i]; }
	Row<T>& operator=(const Row<T>& b);
	Row<T>& operator*=(const T& k);
	Row<T> operator *(const T& k);
	Row<T>& operator -=(const Row<T>& b);
	Row<T> operator -(const Row<T>& b);
	void Clear();
	void resize(uint32_t m);
	void Show(bool drawnext=false);
	size_t Size();
	Row<T>& Input();
	template <typename T> friend void swap(Row<T>&a, Row<T>& b);
	~Row();
};


template<typename T>
inline Row<T>::Row() :arr()
{
	n = 0;
}


template<typename T>
inline void Row<T>::Show(bool nextdraw)
{
	COORD c = get_coords();
	drawline(c.X, c.Y, n);
	drawline(c.X + step, c.Y, n);
	for (int i = 0; i < n; ++i) 
	{
		gotoxy(c.X + 1, c.Y + i);
		cout << arr[i];
	}
	if (nextdraw == true)
		gotoxy(c.X + step + 1, c.Y);
	else
		gotoxy(0, c.Y + n + 1);
}

template<typename T>
inline size_t Row<T>::Size()
{
	return n;
}

template<typename T>
inline Row<T>& Row<T>::Input()
{
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; ++i) cin >> arr[i];
	return *this;
}

template<typename T>
inline Row<T>::~Row()
{
	//cout << "ROW DESTRUCTOR" << endl;
	n = 0;
}

template<typename T>
Row<T>::Row(size_t n):arr(n)
{
	
	for (int i = 0; i < n; ++i) arr[i] = T(0);
	this->n = n;
}

template<typename T>
inline Row<T>::Row(const Row<T>&b):arr(b.arr)
{
	n = b.n;
}

template<typename T>
inline Row<T>& Row<T>::operator=(const Row<T>& b)
{
	if (this != &b) {
		arr.resize(b.n); 
		n = b.n;
		for (int i = 0; i < n; ++i) arr[i] = b.arr[i];	
	}
	return *this;
}

template<typename T>
inline Row<T>& Row<T>::operator*=(const T & k)
{
	for (int i = 0; i < n; ++i) arr[i] *= k;
	return *this;
}

template<typename T>
inline Row<T> Row<T>::operator*(const T & k)
{
	Row<T> res(*this);
	for (int i = 0; i < n; ++i) res.arr[i] *= k;
	return res;
}

template<typename T>
inline Row<T>& Row<T>::operator-=(const Row<T>& b)
{
	for (int i = 0; i < n; ++i) arr[i] -= b.arr[i];
	return *this;
}

template<typename T>
inline Row<T> Row<T>::operator-(const Row<T>& b)
{
	Row<T> res(*this);
	for (int i = 0; i < n; ++i) res.arr[i] -= b.arr[i];
	return res;
}

template<typename T>
inline void Row<T>::Clear()
{
	arr.clear();
	n = 0;
}

template<typename T>
inline void Row<T>::resize(uint32_t m)
{
	arr.resize(m);
	n = m;
}

template<typename T>
inline void swap(Row<T>& a, Row<T>& b)
{
	swap(a.arr, b.arr);
	swap(a.n, b.n);
}
