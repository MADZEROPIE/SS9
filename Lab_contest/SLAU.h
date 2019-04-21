#pragma once
#include "Matrix.h"
#include "Con_sole.h"

template<typename T>
class SLAU
{
	Matrix<T> A;
	Row<T> b;
	Matrix<T> x;
	bool solex;
	int rank = 0;
	double acc=1e-16;
	bool solved = false;
	Row<int> pivot;
public:
	SLAU();
	template<typename T1> friend class SLAU;
	SLAU<T>& Input();
	SLAU<T>& new_Input();
	int Gauss_forw();
	int JGauss();
	void interactive();
	bool end_gauss( int k);
	template<typename T1>SLAU<T>& operator=(SLAU<T1>&);
	Matrix<T> Gauss_back();
	void Show_res() {
		this->Show_sol();
	}
	Row<T> check_res();
	void Show();
	void Show_sol();
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
	x.resize(h);
	
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
	pivot.resize(h);
	for (int i = 0; i < h; ++i)
		pivot[i] = -1;
	COORD cur = get_coords();
	gotoxy(0, cur.Y+v / 2);
	cout << "A = ";
	cur.X += 4;
	drawline(cur.X, cur.Y, v);
	COORD c = { cur.X + 1,cur.Y };
	for (int i = 0; i < v; ++i)
		for (int j = 0; j < h; ++j)
		{
			gotoxy(c.X + step * j, c.Y + i);
			cin >> A[i][j];
		}

	drawline(cur.X += step * h, cur.Y, v);
	gotoxy(cur.X+=1, cur.Y + v / 2);
	cout << " b = ";
	cur.X += 5;
	drawline(cur.X, cur.Y, v);
	drawline(cur.X+step, cur.Y, v);
	cur.X += 1;
	for (int i = 0; i < v; ++i)
	{
		gotoxy(cur);
		cin >> b[i];
		cur.Y += 1;
	}
	cur.Y += 1;
	gotoxy(0,cur.Y);
	cout << "Система: A*x=b" << endl;
	cur = get_coords();
	A.Show(true);
	cur = get_coords();
	cur.X += 1;
	gotoxy(cur);
	cout << " * ";
	cur.X += 4;
	drawx(cur.X, cur.Y, h);
	cur = get_coords();
	gotoxy(cur);
	cout << " = ";
	cur.X += 4;
	b.Show(true);
	gotoxy(0, cur.Y + max(v,h) + 1);
	return *this;
}

template<typename T>
inline void SLAU<T>::Show()
{
	COORD xy1 = get_coords();
	A.Show();
	COORD xy2 = { xy1.X + step * A.m,xy1.Y };
	gotoxy(xy2);
	b.Show();
}
template<typename T>
inline void SLAU<T>::Show_sol()
{
	int m = A.m;
	if (solex)
	{
		int n = m - rank + 1;
		Matrix<T>sol(n, m);
		int m = A.m;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				sol[j][i] = x[i][j];
		COORD cur = get_coords();
		drawx(cur.X, cur.Y, m);
		cur = get_coords();
		gotoxy(cur.X, cur.Y + n / 2);
		cout << " = ";
		gotoxy(cur.X + 4, cur.Y);
		if (n > 1)
		{
			sol[0].Show(true);
			cur = get_coords();
			gotoxy(cur.X, cur.Y + n / 2);
			cout << " + ";
			gotoxy(cur.X + 4, cur.Y);
			for (int i = 1; i < n - 1; ++i)
			{
				sol[i].Show(true);
				cur = get_coords();
				gotoxy(cur.X, cur.Y + n / 2);
				cout << " * t" << i << " + ";
				gotoxy(cur.X + 10, cur.Y);
			}
			sol[n - 1].Show(true);
			cur = get_coords();
			gotoxy(cur.X, cur.Y + n / 2);
			cout << " * t" << n - 1;
		}
		else
		{
			sol[0].Show(true);
		}
		gotoxy(0, cur.Y + m + 1);
	}
	else if (solved)
	{
		cout << "Нет решений." << endl;
	}
	else
	{
		cout << "Сначала вызовите Метод Гаусса или Жордана - Гаусса." << endl;
	}
	
}
template<typename T>
inline SLAU<T>::~SLAU()
{
	//cout << "DESTRUCTOR SLAU"<<endl;
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
			pivot[j] = j;
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
	for (int i = 0; i < m; ++i)
		cout << pivot[i] << " ";
	cout << endl;
	if (solved) {
		for (int j = 0; j < m; ++j)
			if (pivot[j] >= 0)
				for (int i = pivot[j] - 1; i >= 0; --i)
				{
					T d = A[i][j] / A[pivot[j]][j];
					A[i] -= A[pivot[j]] * d;
					b[i] -= b[pivot[j]] * d;
					A[i][j] = T(0);
				}
		
		x.cl_resize(m,m-rank+1);
		cout <<"РАНГ СИСТЕМЫ = " <<rank<<endl;
		this->Show();
		int k = 1;
		for (int i=0;i<m;++i)
			if (pivot[i] >= 0)
			{
				int l = 1;
				
				x[pivot[i]][0] = b[pivot[i]] / A[pivot[i]][i];
				for (int j = 0; j < m; ++j)
				{
					if (pivot[j]>=0)
						continue;
					else
					{
						x[pivot[i]][l++] = A[pivot[i]][j] / A[pivot[i]][i];
						x.Show();
					}
				}
			}
			else
				x[i][k] = 1;
		solex = true;
	}
	else 
	{	
		cout << "Сначала вызовите Метод Гаусса или Жордана- Гаусса." << endl;
	}
	x.Show();
	return x;
}

template<typename T>
inline Row<T> SLAU<T>::check_res()
{
	int m = A.m;
	Row<T> res;
	Row<T> frw(m);
	if (solex) {
		for (int i = 0; i < m; ++i)
			frw[i] = x[i][0];
		res = A * frw - b;
		cout << "Невязка:";
		res.Show();
		}
	else cout << "Невозможно посчитать невязку. " << endl;
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
			pivot[j] = j;
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
void SLAU<T>::interactive()
{
	int n = A.n;
	int m = A.m;
	int k = 0;
	vector<bool> used(m);
	do
	{
		int i,j;
		this->Show();
		cout << "Введите номер строки: i = ";
		cin >> i;
		cout << endl << "Введите номер столбца j = ";
		cin >> j;
		//i -= 1;
		//j -= 1;
		if (pivot[i]==-1 && k<=i && abs(A[i][j])>acc)
		{
			pivot[k] = i;
			swap(A[i], A[k]);
			swap(b[i], b[k]);

			for (int l = k+1; l < n; ++l)
			{
				T d = A[l][j] / A[k][j];
				A[l] -= A[k] * d;
				b[l] -= b[k] * d;
			}
			k++;
		}
		else
			cout << "Выберите другой ведущий элемент";

		cout << endl;

	} while (!end_gauss(k));
	this->Show();
	this->solved=true;
}

template<typename T>
bool SLAU<T>::end_gauss(int k)
{
	int n = A.n;
	int m = A.m;
	if (k >= min(n, m))
		return true;
	else
	{
		for (int i = 0; i < m; ++i)
			if (pivot[i] == -1)
			{
				int j;
				for (j = k; j < n && abs(A[j][i]) < acc; ++j)
					A[j][i] = T(0);
				if (j < n)
					return false;
			}
		return true;
	}
}

template<typename T>
template<typename T1>
inline SLAU<T>& SLAU<T>::operator=(SLAU<T1>&c)
{
	A.cl_resize(c.A.n,c.A.m);
	x.cl_resize(c.x.n,c.x.m);
	b.resize(c.b.Size());
	pivot.resize(c.pivot.Size());
	for (int i = 0; i < c.pivot.Size(); ++i)
		pivot[i] = -1;
	acc = c.acc;
	for (int i = 0; i < A.n; ++i)
	{
		b[i] = T(c.b[i]);
		for (int j = 0; j < A.m; ++j)
			A(i, j) = T(c.A(i, j));
	}
	return *this;
}

