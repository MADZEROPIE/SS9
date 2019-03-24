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
	cout << endl;
	A.cl_resize(v, h);
	b.resize(v);
	char border = char(166);
	char border_lu = char(166);
	char border_ru = char(166);
	char border_ld = char(166);
	char border_rd = char(166);
	COORD c = get_coords();
	COORD lu = { c.X + 5,c.Y };
	COORD ld = { lu.X,lu.Y + v - 1 };
	COORD ru = { lu.X + step * h,lu.Y };
	COORD rd = { lu.X + step * h,lu.Y + v - 1 };
	move_cur({ 0,SHORT(c.Y + v / 2) });
	cout << "A = ";
	for (int i = 1; i <= v - 2; ++i)
	{
		move_cur({ lu.X,SHORT(lu.Y + i) });
		cout << border;
		move_cur({ ru.X,SHORT(ru.Y + i) });
		cout << border;
	}
	move_cur(lu);
	cout << border_lu;
	move_cur(ru);
	cout << border_ru;
	move_cur(ld);
	cout << border_ld;
	move_cur(rd);
	cout << border_rd;
	c = { lu.X + 1,lu.Y };
	for (int i = 0; i < v; ++i)
	{

		for (int j = 0; j < h; ++j)
		{
			move_cur(c);
			cin >> A[i][j];
			c.X += step;
		}
		c.Y += 1;
		c.X = lu.X + 1;
	}
	move_cur({ ru.X + 1,SHORT(ru.Y + v / 2) });
	cout << " b = ";
	for (int i = 1; i <= v - 2; ++i)
	{
		move_cur({ SHORT(ru.X + 6),SHORT(lu.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 6+step),SHORT(ru.Y + i) });
		cout << border;
	}
	move_cur({ SHORT(ru.X + 6), SHORT(lu.Y) });
	cout << border_lu;
	move_cur({ SHORT(ru.X + 6), SHORT(lu.Y + v-1) });
	cout << border_ld;
	move_cur({ SHORT(ru.X + 6 + step) , SHORT(lu.Y) });
	cout << border_ru;
	move_cur({ SHORT(ru.X + 6 + step) , SHORT(lu.Y + v - 1) });
	cout << border_rd;
	c = { SHORT(ru.X + 7),ru.Y };
	for (int i = 0; i < v; ++i)
	{
		move_cur(c);
		cin >> b[i];
		c.Y++;
	}
	cout << "Система: A*x=b" << endl;
	lu = get_coords();
	ld = { lu.X,SHORT(lu.Y + v - 1) };
	ru = { SHORT(lu.X + step * h),SHORT(lu.Y) };
	rd = { SHORT(lu.X + step * h),SHORT(lu.Y + v - 1) };
	
	for (int i = 2; i <= v - 1; ++i)
	{
		move_cur({ lu.X,SHORT(lu.Y + i) });
		cout << border;
		move_cur({ ru.X,SHORT(ru.Y + i) });
		cout << border;
		move_cur({ ru.X + 4,SHORT(ru.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 4+step),SHORT(ru.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 8+step),SHORT(ru.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 8+2*step),SHORT(ru.Y + i) });
		cout << border;
	}
	move_cur({ lu.X,SHORT(lu.Y + 1) });
	cout << border_lu;
	move_cur({ ru.X,SHORT(ru.Y + 1) });
	cout << border_ru;
	move_cur({ lu.X,SHORT(lu.Y + v) });
	cout << border_ld;
	move_cur({ ru.X,SHORT(ru.Y + v) });
	cout << border_rd;
	move_cur({ ru.X + 4,SHORT(ru.Y + 1) });
	cout << border_lu;
	move_cur({ SHORT(ru.X + 4+step),SHORT(ru.Y + 1) });
	cout << border_ru;
	move_cur({ SHORT(ru.X + 8 + step),SHORT(ru.Y + 1) });
	cout << border_lu;
	move_cur({ SHORT(ru.X + 8 + 2 * step),SHORT(ru.Y + 1) });
	cout << border_ru;
	move_cur({ ru.X + 4,SHORT(ru.Y + v) });
	cout << border_lu;
	move_cur({ SHORT(ru.X + 4 + step) ,SHORT(ru.Y + v) });
	cout << border_ru;
	move_cur({ SHORT(ru.X + 8 + step),SHORT(ru.Y + v) });
	cout << border_lu;
	move_cur({ SHORT(ru.X + 8 + 2 * step),SHORT(ru.Y + v) });
	cout << border_ru;
	move_cur({ ru.X + 1, SHORT(lu.Y + v / 2) });
	cout << " * ";
	move_cur({ SHORT(ru.X + 5 + step), SHORT(lu.Y + v / 2) });
	cout << " = ";
	c = { lu.X + 1,lu.Y + 1 };
	for (int i = 0; i < v; ++i)
	{

		for (int j = 0; j < h; ++j)
		{
			move_cur(c);
			cout << A(i,j);
			c.X += step;
		}
		c.Y += 1;
		c.X = lu.X + 1;
	}
	c = { ru.X + 5,ru.Y + 1 };
	for (int i = 0; i < v; ++i)
	{
		move_cur(c);
		cout << "x" << i + 1;
		c.Y++;
	}
	c = { SHORT(ru.X + 9 + step),ru.Y + 1 };
	for (int i = 0; i < v; ++i)
	{
		move_cur(c);
		cout << b[i];
		c.Y++;
	}
	move_cur({ 0,SHORT(lu.Y + v) });

	return *this;
}

template<typename T>
inline void SLAU<T>::Show()
{
	COORD xy1 = get_coords();
	A.Show();
	COORD xy2 = { xy1.X + step * A.m,xy1.Y };
	move_cur(xy2);
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
	int n = A.n; int rank=0;
	for (int j = 0; j < m; ++j)
	{
		int k = j;
		int max_elem = k;
		for (; k < n; ++k)
		{
			if (abs(A(k, j)) > abs(A(max_elem, j)))
				max_elem = k;
			if (abs(A(k, j)) < acc)
				A(k, j) = 0;
		}
		(*this).Show();
		if (abs(A(max_elem, j)) < acc)
			A(max_elem, j) = 0;
		else
		{
			rank++;
			swap(A[max_elem], A[j]);
			for (int i = j + 1;i < n; ++i)
			{
				T d = A(i, j) / A(j, j);
				A[i] -=  A[j]*d;
				A(i, j) = 0;
				b[i] -=  b[j]*d;
			}
		}
	}
	return rank;
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
	int rank=0;
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
			rank++;
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
	return rank;// А надо возвращать РАНГ!!!
}