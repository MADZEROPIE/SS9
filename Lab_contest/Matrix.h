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
	Matrix(uint32_t n, uint32_t m,T acc=T(0));
	Matrix( Matrix& B);
	T& operator()(int i, int j) { return M[i][j]; }
	Matrix<T>& operator=( Matrix<T>& B);
	Row<T> operator*(const Row<T>& X);
	Row<T>& operator[](int i) { return M[i]; }
	Matrix<T>& Input();
	void cl_resize(int v, int h) {
		for (int i = 0; i < m; ++i)	M[i].Clear(); 
		M.Clear(); 
		n = v; m = h;
		M.resize(v);
		for (int i = 0; i < n; ++i)	M[i].resize(h);
	}
	void Show();
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
inline Row<T> Matrix<T>::operator*(const Row<T>& X)
{
	int len = X.Size();
	Row<T> res(len);
	if (m != len) cout << "ERROR";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) res[i] += M[i][j] * X[j];
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
inline void Matrix<T>::Show()
{
	int step = 10;
	COORD lu = get_coords();
	COORD ru = { SHORT(lu.X + step * m),SHORT(lu.Y) };
	char border = char(166);
	for (int i = 1; i <= n; ++i)
	{
		move_cur({ lu.X,SHORT(lu.Y + i) });
		cout << border;
		move_cur({ ru.X,SHORT(ru.Y + i) });
		cout << border;
	}
	COORD c = { lu.X + 1,lu.Y + 1 };
	for (int i = 0; i < n; ++i)
	{

		for (int j = 0; j < m; ++j)
		{
			move_cur(c);
			cout << M[i][j];
			c.X += step;
		}
		c.Y += 1;
		c.X = lu.X + 1;
	}
	move_cur({ 0,c.Y + 1 });
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	//for(int i = 0; i < n; ++i) M[i].~Row();
	//M.~Row();
}
