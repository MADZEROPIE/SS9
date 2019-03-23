#pragma once
#include "Matrix.h"

template<typename T>
class SLAU
{
	Matrix<T> A;
	Row<T> b;
	T acc;
public:
	SLAU();
	SLAU<T>& Input();
	int Gauss_forw();
	int JGauss();
	Row<T> Gauss_back();
	Row<T> check_res();
	void Show();
	~SLAU();
};

template<typename T>
inline SLAU<T>::SLAU()
{
}

template<typename T>
inline SLAU<T>& SLAU<T>::Input()
{
	int v, h;
	cout << "¬ведите количество строк: ";
	cin >> v;
	cout << "¬ведите количество столбцов: ";
	cin >> h;
	cout << "¬ведите точность вычислений: ";
	cin >> acc;
	A.cl_resize(v, h);
	b.resize(v);
	
	cout << "¬ведите матрицу A: \n";
	for (int i = 0; i < v; ++i) { 
		for (int j = 0; j < h; ++j) cin >> A.M[i][j]; }
	
	cout << "¬ведите столбец b: \n";
	for (int i = 0; i < v; ++i) cin >> b[i];
	return	*this;
}

template<typename T>
inline void SLAU<T>::Show()
{
	A.Show();
	cout << "---------------------------\n";
	b.Show();
}

template<typename T>
inline SLAU<T>::~SLAU()
{
}
