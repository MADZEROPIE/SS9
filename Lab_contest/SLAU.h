#pragma once
#include "Matrix.h"
#include "Con_sole.h"

template<typename T>
class SLAU
{
	
	Matrix<T> x;
	bool solex;
	int rank = 0;
	double acc=1e-16;
	bool solved = false;
public:
	Matrix<T> A;
	Row<T> b;
	SLAU();
	template<typename T1> friend class SLAU;
	SLAU<T>& Input();
	SLAU<T>& new_Input();
	int Gauss_forw();
	int JGauss();
	template<typename T1>SLAU<T>& operator=(SLAU<T1>&);
	Matrix<T> Gauss_back();
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
	x.resize(h);
	
	cout << "¬ведите матрицу A: \n";
	for (int i = 0; i < v; ++i) { 
		for (int j = 0; j < h; ++j) cin >> A.M[i][j]; }
	
	cout << "¬ведите столбец b: \n";
	for (int i = 0; i < v; ++i) cin >> b[i];
	return	*this;
}

template<typename T>
inline SLAU<T>& SLAU<T>::new_Input()
{
	int v, h;
	cout << "¬ведите количество строк: ";
	cin >> v;
	cout << "¬ведите количество столбцов: ";
	cin >> h;
	cout << "¬ведите точность вычислений: ";
	cin >> acc;
	cout << endl;
	A.cl_resize(v, h);
	b.resize(v);
	//for (int i = 0; i < h; ++i) x[i] = T(0);
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
	cout << "—истема: A*x=b" << endl;
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
		
		move_cur({ SHORT(ru.X + 8+step),SHORT(ru.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 8+2*step),SHORT(ru.Y + i) });
		cout << border;
	}
	for (int i = 1; i <=h; ++i)
	{
		move_cur({ ru.X + 4,SHORT(ru.Y + i) });
		cout << border;
		move_cur({ SHORT(ru.X + 4 + step),SHORT(ru.Y + i) });
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
	for (int i = 0; i < h; ++i)
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
	move_cur({ 0,SHORT(lu.Y + max(v,h)+1) });
	//for (int i = 0; i < h; ++i) x[i] = T(0);
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
	//cout << "DESTRUCTOR SLAU"<<endl;
	//b.~Row();
	//x.~Row();
	//A.~Matrix();
}

template<typename T>
inline int SLAU<T>::Gauss_forw()
{
	int m = A.m;
	int n = A.n; rank=0;
	for (int j = 0; j < m && j<n; ++j)
	{
		int k = j;
		int max_elem = k;
		for (; k < n; ++k)
		{
 			if (abs(A(k, j)) > abs(A(max_elem, j)))
				max_elem = k;
			if (double(abs(A(k, j))) < acc)
				A(k, j) = T(0);
		}
		
		if (double(abs(A(max_elem, j))) < acc)
			A(max_elem, j) = T(0);
		else
		{
			rank++;
			swap(A[max_elem], A[j]);
			swap(b[max_elem], b[j]);
			for (int i = j + 1;i < n; ++i)
			{
				T d = A(i, j) / A(j, j);
				A[i] -=  A[j]*d;
				A(i, j) = T(0);
				b[i] -=  b[j]*d;
			}
		}
		this->Show();
	}
	solved = true;
	return rank;
}

template<typename T>
inline Matrix<T> SLAU<T>::Gauss_back()
{
	int m = A.m;
	int n = A.n;
	
	if (solved) {
		for (int i = rank; i < n; ++i)
			if (double(abs(b[i])) < acc)
				b[i] = T(0);
			else
			{
				cout << "—истема несовместна" << endl;
				solex = false;
				return x;
			}
		x.cl_resize(m, m - rank + 1);
		for (int i=rank-1;i>=0;--i)
			for (int j = i-1; j >= 0; --j)
			{
				T d = A(j, i) / A(i, i);
				A[j] -= A[i] * d;
				A(i, j) = T(0);
				b[j] -= b[i] * d;
				this->Show();
			}
		cout << rank;
		this->Show();
		for (int i = 0; i < rank; ++i)
		{
			x[i][0] = b[i] / A[i][i];
			for (int j = rank; j < m; ++j)
				x[i][j-rank+1] = A[i][j] / A[i][i];
		}
		for (int i = rank; i < m; ++i)
		{
			x[i][i-rank+1] = 1;
		}
	}
	else 
	{
		
		cout << "—начала вызовите ћетод √аусса или ∆ордана- √аусса." << endl;
	}
	x.Show();
	return x;
}

template<typename T>
inline Row<T> SLAU<T>::check_res()
{
	Row<T> res (A * x[0]);
	res -= b;
	res.Show();
	return res;
}

template<typename T>
inline int SLAU<T>::JGauss()
{
	int m = A.m;
	int n = A.n;
	rank=0;
	for (int j = 0; j < m && j < n; ++j)
	{
		int k = j;
		int max_elem = k;
		for (; k < n; ++k)
		{
			if (abs(A(k, j)) > abs(A(max_elem, j)))
				max_elem = k;
			if (double(abs(A(k, j))) < acc)
				A(k, j) = T(0);
		}
		this->Show();
		if (double(abs(A(max_elem, j))) < acc)
			A(max_elem, j) = T(0);
		else
		{
			rank++;
			swap(A[max_elem], A[j]);
			swap(b[max_elem], b[j]);
			for (int i = 0; i < n; ++i)
				if (i != j)
				{
					T d = A(i, j) / A(j, j);
					A[i] -=  A[j]*d;
					b[i] -=  b[j]*d;
				}
		}
	}
	solved = true;
	return rank;
}

template<typename T>
template<typename T1>
inline SLAU<T>& SLAU<T>::operator=(SLAU<T1>&c)
{
	A.cl_resize(c.A.n,c.A.m);
	x.cl_resize(c.x.n,c.x.m);
	b.resize(c.b.Size());
	acc = c.acc;
	for (int i = 0; i < A.n; ++i)
	{
		b[i] = T(c.b[i]);
		for (int j = 0; j < A.m; ++j)
			A(i, j) = T(c.A(i, j));
	}
	//for (int j = 0; j < c.x.Size(); ++j) x[j] = T(c.x[j]);
	return *this;
}

