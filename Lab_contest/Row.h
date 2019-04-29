#pragma once
#include<iostream>
#include "Con_sole.h"
#include <iomanip>

using namespace std;


template <typename T>
class Row
{
private:
	vector<T> arr; //Вектор элементов столбца
	size_t n; //Количество элементов
public:
	// Конструкторы
	Row(); 
	Row(size_t n);
	Row(const Row<T>&);

	//Перегруженные операции
	T& operator[](int i) { return arr[i]; }
	Row<T>& operator=(const Row<T>& b);
	Row<T>& operator*=(const T& k);
	Row<T> operator *(const T& k);
	Row<T>& operator -=(const Row<T>& b);
	Row<T> operator -(const Row<T>& b);

	void Clear(); //Удаление всех элементов столбца
	void resize(uint32_t m); //Изменение размера
	void Show(bool drawnext=false);	//Вывод на экран

	size_t size() {
		return n;
	} // Возвращает размер столбца
	Row<T>& Input(); //Ввод столбца
	template <typename T> friend void swap(Row<T>&a, Row<T>& b);// Меняет объекты a и b местами

	~Row();	//Деструктор
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
