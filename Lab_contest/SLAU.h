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
	cout << "������� ���������� �����: ";
	cin >> v;
	cout << "������� ���������� ��������: ";
	cin >> h;
	cout << "������� �������� ����������: ";
	cin >> acc;
	A.cl_resize(v, h);
	b.resize(v);
	
	cout << "������� ������� A: \n";
	for (int i = 0; i < v; ++i) { 
		for (int j = 0; j < h; ++j) cin >> A.M[i][j]; }
	
	cout << "������� ������� b: \n";
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

template<typename T>
inline int SLAU<T>::Gauss_forw()
{
	int m = A.m;
	int n = A.n;
	for (int j = 0; j < m; ++j)
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
			swap(A[k], A[j]);
			for (int i = j + 1;i < n; ++i)
			{
				T d = A(i, j) / A(j, j);
				A[i] -= d * A[j];
				b[i] -= d * b[j];
			}
		}
	}
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
		for (int k = n - 1; k > i; ++k)
			sum += x[k] * A(i, k);
		if (A(i, i) < acc && sum - b[i] < acc);
			//x - �����
		else if (A(i, i) < acc && sum - b[i] >= acc)
			return 0;
		//no solution
		else
		{
			x[i] = (b[i] - sum) / A(i, i);
			rank++;
		}
			
	}
	return rank;
}
template<typename T>
inline int SLAU<T>::JGauss()
{
	int m = A.m;
	int n = A.n;
	for (int j = 0; j < m; ++j)
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
			swap(A[k], A[j]);
			for (int i = 0; i < n; ++i)
				if (i != j)
				{
					T d = A(i, j) / A(j, j);
					A[i] -= d * A[j];
					b[i] -= d * b[j];
				}
		}
	}
}