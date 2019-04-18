#pragma once
#include "Row.h"

template<typename T>
class Matrix
{
private:
	uint32_t n,//Количество строк
		m;// Количество столбцов
	Row<Row<T> > M;

public:
	template<typename T1> friend class SLAU;
	Matrix();
	Matrix(uint32_t n, uint32_t m);
	Matrix( Matrix& B);
	T& operator()(int i, int j) { return M[i][j]; }
	Matrix<T>& operator=( Matrix<T>& B);
	Row<T> operator*(Row<T>& X);
	Row<T>& operator[](int i) { return M[i]; }
	Matrix<T>& Input();
	void cl_resize(int v, int h) {
		for (int i = 0; i < n; ++i)	M[i].Clear(); 
		M.Clear(); 
		n = v; m = h;
		M.resize(v);
		for (int i = 0; i < n; ++i)	M[i].resize(h);
	}
	void Show(bool nextdraw=false);
	~Matrix();
};

template<typename T>
inline Matrix<T>::Matrix()
{
}

template<typename T>
inline Matrix<T>::Matrix(uint32_t n, uint32_t m)
{

	M.resize(n);
	for(int i=0;i<n;++i) M[i].resize(m);
	this->m = m;
	this->n = n;
}

template<typename T>
inline Matrix<T>::Matrix( Matrix & B)
{
	m = B.m;
	n = B.n;
	M.resize(B.n);
	for (int i = 0; i < n; ++i) {
		M[i].resize(B.m);
		for (int j = 0; j < B.m; ++j) 
			M[i][j] = B.M[i][j];  
	}
	
}

template<typename T>
inline Matrix<T> & Matrix<T>::operator=(Matrix<T> & B)
{
	if (m != B.m || n != B.n) {
		for (int i = 0; i < n; ++i) M[i].Clear();
		M.Clear();
		M.resize(B.n);
		for (int i = 0; i < B.n; ++i) M[i].resize(B.m);
		m = B.m;
		n = B.n;
	}
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < m; ++j)
			M[i][j] = B.M[i][j];
	
	return *this;
}

template<typename T>
inline Row<T> Matrix<T>::operator*(Row<T>& X)
{
	int len = X.Size();
	Row<T> res(n);
	if (m != len) cout << "ERROR"<<endl;
	else {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) res[j] += M[j][i] * X[i];
		}
	}
	return res;
}

template<typename T>
inline Matrix<T>& Matrix<T>::Input()
{
	for (int i = 0; i < n; ++i) M[i].Clear();
	M.Clear();
	cout << "Введите количество строк: ";
	cin >> n;
	M.resize(n);
	cout << "Введите количество столбцов: ";
	cin >> m;
	//cout << "Введите точность вычислений: ";
	//cin >> acc;
	for (int i = 0; i < n; ++i) {
		M[i].resize(m);
		for (int j = 0; j < m; ++j) cin >> M[i][j];
	}
	return *this;
}

template<typename T>
inline void Matrix<T>::Show(bool nextdraw)
{
	COORD c = get_coords();
	drawline(c.X, c.Y, n);
	drawline(c.X + m * step, c.Y, n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			gotoxy(c.X + j * step + 1, c.Y + i);
			cout << M[i][j];
		}
	if (nextdraw == true)
		gotoxy(c.X + m * step + 1, c.Y);
	else
		gotoxy(0, c.Y + n + 2);
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	//cout << "MATRIX DESTRUCTOR" << endl;
	//for(int i = 0; i < n; ++i) M[i].~Row();
	//M.~Row();
}
