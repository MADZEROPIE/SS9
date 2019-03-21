#pragma once
#include<iostream>

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
	Row<T>& operator=(const Row<T>& b);
	Row<T>& operator*=(const T& k);
	Row<T> operator *(const T& k);
	Row<T>& operator -=(const Row<T>&);
	void Show();
	Row<T>& Input();

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
	for (int i = 0; i < n; ++i) cout << arr[i] << " ";
	cout << endl;
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
}

template<typename T>
Row<T>::Row(size_t n)
{
	arr = new T[n];
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
	delete[] arr;
	arr = new T[b.n];
	n = b.n;
	for (int i = 0; i < n; ++i) arr[i] = b.arr[i];
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
