#pragma once
#include "Matrix.h"
#include "Con_sole.h"

template<typename T>
class SLAU
{
	Matrix<T> A;
	Row<T> b;
	T acc;
public:
	SLAU();
	SLAU<T>& Input();
	SLAU<T>& new_Input();
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
	cout << "Введите количество строк: ";
	cin >> v;
	cout << "Введите количество столбцов: ";
	cin >> h;
	cout << "Введите точность вычислений: ";
	cin >> acc;
	A.cl_resize(v, h);
	b.resize(v);
	
	cout << "Введите матрицу A: \n";
	for (int i = 0; i < v; ++i) { 
		for (int j = 0; j < h; ++j) cin >> A.M[i][j]; }
	
	cout << "Введите столбец b: \n";
	for (int i = 0; i < v; ++i) cin >> b[i];
	return	*this;
}

template<typename T>
inline SLAU<T>& SLAU<T>::new_Input()
{
	int v, h;
	cout << "Введите количество строк: ";
	cin >> v;
	cout << "Введите количество столбцов: ";
	cin >> h;
	cout << "Введите точность вычислений: ";
	cin >> acc;
	cout << "Введите матрицу A: \n";
	COORD a;
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			cout << "(" << i << "," << j << ") = ";
			cin >> A(i, j);
			a = get_coords();
			a.X++;
			move_cur(a);
		}
		a.X = 0;
		a.Y++;
		move_cur(a);
	}
	cout << "Введите столбец b: \n";
	for (int i = 0; i < v; ++i)
	{
		cout << "(", i, ") = ";
		cin >> b[i];
		a = get_coords();
		a.X++;
		move_cur(a);
	}
	return *this;
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

template<typename T>
inline int SLAU<T>::Gauss_forw()
{
	int m = A.m;
	int n = A.n; int j;
	for (j = 0; j < m; ++j)
	{
		int k = j;
		int max_elem = k;
		for (; k < n; ++k)
		{
			if (A(k, j) > A(max_elem, j))
				max_elem = k;
			if (A(k, j) < acc)
				A(k, j) = 0;
		}


		if (A(max_elem, j) < acc)
			A(max_elem, j) = 0;
		else
		{
			swap(A[max_elem], A[j]);
			for (int i = j + 1;i < n; ++i)
			{
				T d = A(i, j) / A(j, j);
				A[i] -=  A[j]*d;
				b[i] -=  b[j]*d;
			}
		}
	}
	return j;// А надо возвращать РАНГ!!!
}

template<typename T>
inline Row<T> SLAU<T>::Gauss_back()
{
	int m = A.m;
	int n = A.n;
	Row<T>x;
	x.resize(n);
	int rank = 0;
	for (int i = n - 1; i >= 0; --i)
	{
		T sum = 0;
		for (int k = n - 1; k > i; --k)
			sum += x[k] * A(i, k);
		if (A(i, i) < acc && sum - b[i] < acc);
			//x - любое
		else if (A(i, i) < acc && sum - b[i] >= acc)
			return 0;
		//no solution
		else
		{
			x[i] = (b[i] - sum) / A(i, i);
			rank++;
		}
			
	}
	return x;
}
template<typename T>
inline int SLAU<T>::JGauss()
{
	int m = A.m;
	int n = A.n;
	int j=0;
	for ( j = 0; j < m; ++j)
	{
		int k = j;
		int max_elem = k;
		for (; k < n; ++k)
		{
			if (A(k, j) > A(max_elem, j))
				max_elem = k;
			if (A(k, j) < acc)
				A(k, j) = 0;
		}

		if (A(max_elem, j) < acc)
			A(max_elem, j) = 0;
		else
		{
			swap(A[max_elem], A[j]);
			for (int i = 0; i < n; ++i)
				if (i != j)
				{
					T d = A(i, j) / A(j, j);
					A[i] -=  A[j]*d;
					b[i] -=  b[j]*d;
				}
		}
	}
	return j;// А надо возвращать РАНГ!!!
}