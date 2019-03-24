#pragma once
#include<iostream>
#include "Con_sole.h"
using namespace std;


template <typename T>
class Row
{
private:
	T* arr;//
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
	void Show();
	size_t Size();
	Row<T>& Input();
	template <typename T> friend void swap(Row<T>&a, Row<T>& b);
	~Row();
};


template<typename T>
inline Row<T>::Row()
{
	arr = nullptr;
	n = 0;
}


template<typename T>
inline void Row<T>::Show()
{
	COORD l = get_coords();
	l.Y++;
	COORD l1 = { l.X + 1,l.Y };
	COORD r = { l.X + step,l.Y };
	for (int i = 0; i < n; ++i) 
	{
		move_cur(l);
		cout << char(166);
		move_cur(l1);
		cout << arr[i];
		move_cur(r);
		cout << char(166);
		l.Y++;
		l1.Y++;
		r.Y++;
	}
	move_cur({ 0,l.Y + 1 });
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
	delete[] arr;
	arr = new T[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	return *this;
}

template<typename T>
inline Row<T>::~Row()
{
	delete[] arr;
	arr = nullptr;
}

template<typename T>
Row<T>::Row(size_t n)
{
	arr = new T[n];
	for (int i = 0; i < n; ++i) arr[i] = T(0);
	this->n = n;
}

template<typename T>
inline Row<T>::Row(const Row<T>&b)
{
	n = b.n;
	arr = new T[n];
	for (int i = 0; i < n; ++i) arr[i] = b.arr[i];
}

template<typename T>
inline Row<T>& Row<T>::operator=(const Row<T>& b)
{
	if (this != &b) {
		delete[] arr;
		arr = new T[b.n];
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
	delete[] arr;
	arr = nullptr;
	n = 0;
}

template<typename T>
inline void Row<T>::resize(uint32_t m)
{
	if (m != n && n != 0) {
		int k = m > n ? n : m;
		T* tmp = new T[n];
		for (int i = 0; i < k; ++i) tmp[i] = arr[i];
		delete[] arr;
		arr = new T[m];
		for (int i = 0; i < k; ++i) arr[i] = tmp[i];
		n = m;
		delete[] tmp;
	}
	if (n == 0){
		arr = new T[m];
	n = m;
	}
}

template<typename T>
inline void swap(Row<T>& a, Row<T>& b)
{
	T* tmp = a.arr;
	a.arr = b.arr;
	b.arr = tmp;
}
