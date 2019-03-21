#pragma once
#include "Row.h"

template<typename T>
class Matrix
{
private:
	uint32_t n,//Количество строк
		m;// Количество столбцов
	Row<Row<T> > M;
	T acc;
public:
	Matrix();
	Matrix(uint32_t n, uint32_t m,T acc=T(0));
	Matrix(const Matrix& B);
	Matrix<T>& operator=(const Matrix<T>& B);
	Row<T> operator*(const Row<T>& X);
	Matrix<T>& Input();
	~Matrix();
};

template<typename T>
inline Matrix<T>::Matrix()
{
}

template<typename T>
inline Matrix<T>::Matrix(uint32_t n, uint32_t m,T acc)
{
	M.resize(n);
	for(int i=0;i<n;++i) M[i].resize(m);
	this->m = m;
	this->n = n;
	this->acc = acc;
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix & B)
{	
	M.resize(B.n);
	for (int i = 0; i < n; ++i) {
		M[i].resize(m);
		for (int j = 0; j < B.m; ++j) M[i][j] = B.M[i][j];
	}
	m = B.m;
	n = B.n;
}

template<typename T>
inline Matrix<T> & Matrix<T>::operator=(const Matrix<T> & B)
{
	if (m != B.m || n != B.n) {
		for (int i = 0; i < n; ++i) M[i].Clear();
		M.resize(B.n);
		for (int i = 0; i < n; ++i) M[i].resize(B.m);
		m = B.m;
		n = B.n;
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; j++) M[i][j] = B.M[i][j];
	acc = B.acc;
}

template<typename T>
inline Row<T> Matrix<T>::operator*(const Row<T>& X)
{
	int len = X.Size();
	Row<T> res(len);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) res[i] += M[i][j] * X[j];
	}
	return res;
}

template<typename T>
inline Matrix<T>& Matrix<T>::Input()
{
	return *this;
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	for(int i = 0; i < n; ++i) M[i].~Row();
	M.~Row();
}
