#pragma once
#include "Matrix.h"
#include "Con_sole.h"
#include <ctime>

template<typename T>
class SLAU
{
	Matrix<T> A;// ������� ���� (��������)
	Row<T> b;// ������� �������� ������ (��������)
	Matrix<T> x; // ������� ������� � ��������������� ����
	bool solex; // ������������� �������
	int rank = 0; //���� ����
	double acc=1e-16; // �������� ���������� �� ����
	bool solved = false; // ������� ������?
	Row<int>pivot; // ???
	vector<bool> used; // ???
public:
	SLAU();
	template<typename T1> friend class SLAU;
	SLAU<T>& Input();//���� ����
	int Gauss_forw(bool steps_sh=true);
	int JGauss(bool steps_sh = true);
	void interactive(bool steps_sh = true);
	bool end_gauss(int k);
	template<typename T1>SLAU<T>& operator=(SLAU<T1>&);
	Matrix<T> Gauss_back();
	bool sol_ex() { return solex; }
	bool is_solved() { return solved; }
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
	cout << "������� ���������� �����: ";
	do
	{
		cin >> v;
		if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); v = -1; }
	} while (v < 0);
	cout << "������� ���������� ��������: ";
	do
	{
		cin >> h;
		if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); h = -1; }
	} while (h < 0);
	cout << "������� �������� ����������: ";
	do
	{
		cin >> acc;
		if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); acc = -1.0; }
	} while (acc < 0);
	cout << endl;
	A.cl_resize(v, h);
	b.resize(v);
	pivot.resize(h);
	used.resize(v);
	solved = false;
	for (int i = 0; i < h; ++i)
		pivot[i] = -1;
	cout << "��������� ���� ���������� �������? ";
	bool random = get_ch();
	COORD cur = get_coords();
	if (!random){
		gotoxy(0, cur.Y + v / 2);
		cout << "A = ";
		cur.X += 4;
		drawline(cur.X, cur.Y, v);
		COORD c = { cur.X + 1,cur.Y };
		for (int i = 0; i < v; ++i) {
			for (int j = 0; j < h; ++j)
			{
				gotoxy(c.X + step * j, c.Y + i);
				cin >> A[i][j];
			}
		}
	drawline(cur.X += step * h, cur.Y, v);
	gotoxy(cur.X += 1, cur.Y + v / 2);
	cout << " b = ";
	cur.X += 5;
	drawline(cur.X, cur.Y, v);
	drawline(cur.X + step, cur.Y, v);
	cur.X += 1;
	for (int i = 0; i < v; ++i)
	{
		gotoxy(cur);
		cin >> b[i];
		cur.Y += 1;
	}
	cur.Y += 1;
	gotoxy(0, cur.Y);
	}
	else {
		srand(time(NULL));
		for (int i = 0; i < v; ++i) {
			b[i] = T(rand()%100);
			for (int j = 0; j < h; ++j)
			{
				A[i][j] = T(rand()%100); 
			}
		}
	}
	cout << "�������: A*x=b" << endl;
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
		cout << "��� �������." << endl;
	}
	else
	{
		cout << "������� �������� ����� ������ ��� ������� - ������." << endl;
	}
	
}
template<typename T>
inline SLAU<T>::~SLAU()
{
	//cout << "DESTRUCTOR SLAU"<<endl;
}

template<typename T>
inline int SLAU<T>::Gauss_forw(bool steps_sh )
{
	int m = A.m;
	int n = A.n; rank=0;
	int k = 0;
	for (int j = 0; j < m; ++j)
	{
		int max_elem = k;
		for (int i = k; i < n; ++i)
		{
			if (abs(double(A[i][j])) < acc)
				A[i][j] = T(0);
			else if (abs(A[i][j]) > abs(A[max_elem][j]))
				max_elem = i;
		}
		if (max_elem>=n || double(abs(A[max_elem][j]))<acc)
			continue;
		else
		{
			if (steps_sh) cout << "������������ �� ������ ������� ��������� � " << max_elem << " - �� ������" << endl;
			if (max_elem != k)
			{
				if (steps_sh) cout << "������ ������� ������ � ��������� " << max_elem << " � " << k << endl;
				swap(A[max_elem], A[k]);
				swap(b[max_elem], b[k]);
				this->Show();
			}
			pivot[j] = k;
			k++;
			used[k-1] = true;
			for (int l = k; l < n; ++l)
			{
				T d = A[l][j] / A[k - 1][j];
				if (steps_sh) cout << "�������� �� " << l << "-�� ������ " << k - 1 << " ������, ���������� �� " << d << endl;
				A[l] -= A[k - 1] * d;
				b[l] -= b[k - 1] * d;
				A[l][j] = T(0);
			}
			if (steps_sh) this->Show();
		}
	}	

	solved = true;
	rank = k;
	return rank;
}

template<typename T>
inline Matrix<T> SLAU<T>::Gauss_back()
{
	int m = A.m;
	int n = A.n;
	
	if (solved) {
		for (int i = 0; i < n; ++i)
			if (used[i] == false && double(abs(b[i])) < acc);
				
			else if (used[i]==false)
			{
				cout << "������� �����������." << endl;
				solex = false;
				return x;
			}
		x.cl_resize(m, m - rank + 1);
		for (int j=0;j<m;++j)
			if (pivot[j]>=0)
				for (int i = pivot[j] - 1; i >= 0; i--)
				{
					T d = A[i][j] / A[pivot[j]][j];
					A[i] -= A[pivot[j]] * d;
					b[i] -= b[pivot[j]] * d;
					A[i][j] = T(0);
				}

		cout <<"���� ������� = " <<rank<<endl;
		this->Show();
		int p = 1;
		for (int j = 0; j < m; ++j)
		{
			if (pivot[j] >= 0)
			{
				x[j][0] = b[pivot[j]] / A[pivot[j]][j];
				int k = 1;
				for (int l = 0; l < m; ++l)
				{
					if (pivot[l] == -1)
						x[j][k++] = T(0)-A[pivot[j]][l] / A[pivot[j]][j];
				}
			}
			else
			{
				x[j][p] = 1;
				p++;
			}
		}
		
		solex = true;
	}
	else 
	{	
		cout << "������� �������� ����� ������ ��� �������-������." << endl;
	}
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
		cout << "�������:";
		res.Show();
		}
	else cout << "���������� ��������� �������. " << endl;
	return res;
}

template<typename T>
inline int SLAU<T>::JGauss(bool steps_sh)
{
	int m = A.m;
	int n = A.n; rank = 0;
	int k = 0;
	for (int j = 0; j < m; ++j)
	{
		int max_elem = k;
		for (int i = k; i < n; ++i)
			if (abs(double(A[i][j])) < acc)
				A[i][j] = T(0);
			else if (abs(A[i][j]) > abs(A[max_elem][j]))
				max_elem = i;
		if (max_elem >= n || double(abs(A[max_elem][j]))<acc)
			continue;
		else
		{
			if(steps_sh) cout << "������������ �� ������ ������� ��������� � " << max_elem << " - �� ������" << endl;
			if (max_elem != k)
			{
				if (steps_sh) cout << "������ ������� ������ � ��������� " << max_elem << " � " << k << endl;
				swap(A[max_elem], A[k]);
				swap(b[max_elem], b[k]);
				if (steps_sh) this->Show();
			}
			pivot[j] = k;
			k++;
			used[k-1] = true;
			for (int l = 0; l < n; ++l)
			{
				if (l == k - 1)
					continue;
				T d = A[l][j] / A[k - 1][j];
				if (steps_sh) cout << "�������� �� " << l << "-�� ������ " << k-1 << " ������, ���������� �� " << d << endl;
				A[l] -= A[k - 1] * d;
				b[l] -= b[k - 1] * d;
				A[l][j] = T(0);
			}
			if (steps_sh) this->Show();
		}
	}
	
	solved = true;
	rank = k;
	return rank;
}

template<typename T>
void SLAU<T>::interactive(bool steps_sh)
{
	int n = A.n;
	int m = A.m;
	int k = 0;
	do
	{
		int i,j;
		this->Show();
		do
		{
			cout << "������� ����� ������: i = ";
			cin >> i;
			if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); i = -1; }
		} while (i<0 || i>=n);
		do
		{
			cout << "������� ����� ������� j = ";
			cin >> j;
			if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); j = -1; }
		} while (j < 0 || j >= m);
		
		if (pivot[j]==-1 && k<=i && abs(double(A[i][j]))>acc)
		{
			pivot[j] = k;
			used[k] = true;
			if (steps_sh) cout << "������ ������� ������ � ��������� " << i<< " � " << k << endl;
			swap(A[i], A[k]);
			swap(b[i], b[k]);
			this->Show();
			for (int l = k+1; l < n; ++l)
			{
				T d = A[l][j] / A[k][j];
				if (steps_sh) cout << "�������� �� " << l << "-�� ������ " << k  << " ������, ���������� �� " << d << endl;
				A[l] -= A[k] * d;
				b[l] -= b[k] * d;
				A[l][j] = T(0);
			}
			k++;
		}
		else cout << "�������� ������ ������� �������."<<endl;

	} while (!end_gauss(k));
	solved = true;
	rank = k;
	this->Show();
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
				for (j = k; j < n && abs(double(A[j][i])) < acc; ++j)
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
	solved = false;
	pivot.resize(c.pivot.Size());
	used.resize(c.used.size());
	for (int i = 0; i < pivot.Size(); ++i)
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

