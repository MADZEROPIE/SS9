#pragma once
#include "Matrix.h"
#include "Con_sole.h"
#include <ctime>

template<typename T>
class SLAU
{
	Matrix<T> A,A_base;// ������� ���� ��������/��������
	Row<T> b,b_base;// ������� �������� ������ ��������/��������
	Matrix<T> x; // ������� ������� � ��������������� ����
	bool solex; // ������������� �������
	int rank = 0; //���� ����
	double acc=1e-16; // �������� ���������� �� ����
	bool solved = false; // ������� ������?
	vector<int>pivot; // ������ �������� ������� ���������
	vector<bool> used; // ???
	bool rat_overflow = false; //������������ rational
public:
	SLAU() {}
	template<typename T1> friend class SLAU;
	template<typename T1>SLAU<T>& operator=(SLAU<T1>&);

	SLAU<T>& Input();//���� ����
	int Gauss_forw(bool file_out = false, string filename = "output.txt"); //������ ��� ������ ������
	int JGauss(bool file_out = false, string filename = "output.txt");// ����� �������-������
	
	void interactive(bool file_out = false,string filename = "output.txt"); //������������� ����� ������
	bool end_gauss(int k); // �������� �� ��������� �������������� ������ ������
	
	Matrix<T> Gauss_back(bool file_out = false, string filename = "output.txt"); //�������� ��� ��� ������ ������ (������������ �������)
	Row<T> check_res(bool file_out = false, string filename = "output.txt");	//������� �������

	bool sol_ex() { return solex; }	//������������� �������
	bool is_solved() { return solved; }	//������� ������?
		
	void Show(bool base=false);	//����� ����
	void Show_in_file(ofstream&, bool base = false);// ����� ���� � ����
	void Show_sol(bool file_out = false, string filename = "output.txt"); //����� �������
	bool rat_over() { return rat_overflow; }
	~SLAU() {}
};


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
	cout << endl;
	A_base.cl_resize(v, h);
	b_base.resize(v);
	pivot.resize(h);
	used.resize(v);
	solved = false;
	for (int i = 0; i < h; ++i)
		pivot[i] = -1;
	cout << "��������� ���� ���������� �������? Y/N ";
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
				cin >> A_base[i][j];
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
		cin >> b_base[i];
		cur.Y += 1;
	}
	cur.Y += 1;
	gotoxy(0, cur.Y);
	}
	else {
		srand(time(NULL));
		for (int i = 0; i < v; ++i) {
			b_base[i] = T(rand()%100);
			for (int j = 0; j < h; ++j)
			{
				A_base[i][j] = T(rand()%100); 
			}
		}
	}
	cout << "�������: A*x=b" << endl;
	cur = get_coords();
	A_base.Show(true);
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
	b_base.Show(true);
	gotoxy(0, cur.Y + max(v,h) + 1);
	rat_overflow = false;
	return *this;
}

template<typename T>
inline void SLAU<T>::Show(bool base)
{
	COORD xy1 = get_coords();
	if(base) A_base.Show();
	else A.Show();
	COORD xy2 = { xy1.X + step * A.m,xy1.Y };
	gotoxy(xy2);
	if (base) b_base.Show();
	else b.Show();
}

template<typename T>
inline void SLAU<T>::Show_in_file(ofstream & fout, bool base)
{
	int n = A_base.n;
	int m = A_base.m;
	char border = char(166);
	for (int i = 0; i < n; ++i)
	{
		fout << border;
		for (int j = 0; j < m; ++j)
		{
			fout.width(fstep);
			if (!base)  fout << A[i][j]; 
			else fout << A_base[i][j];
		}	
		fout << border;
		fout.width(fstep);
		if (!base) fout << b[i];
		else fout << b_base[i];
		fout << border << endl;
	}
	fout << endl;
}

template<typename T>
inline void SLAU<T>::Show_sol(bool file_out,string filename)
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
		ofstream fout;
		if (file_out)
		{
			fout.open(filename, ofstream::app);
			if (!fout.is_open())
			{
				cout << "�� ������� ������� ���� " << filename;
				file_out = false;
			}
		}
		if (file_out)
		{
			char border = char(166);
			for (int j = 0; j < m; ++j)
			{
				fout << border;
				fout << "x" << j+1;
				fout.width(4);
				fout << border;
				if (j == 0)
					fout << " = ";
				else
					fout << "   ";
				fout << border;
				fout.width(fstep);
				fout << sol[0][j];
				fout << border;
				if (j == 0 && n>1)
					fout << " + ";
				else
					fout << "   ";
				for (int i = 1; i < n; ++i)
				{
					fout << border;
					fout.width(fstep);
					fout << sol[i][j];
					fout << border;
					fout.width(5);
					if (j == 0)
						fout << " *t" << i;
					else
						fout << "   ";
					fout.width(5);
					if (i != n - 1 && j == 0)
						fout << " + ";
					else
						fout << "   ";

				}
				fout << endl;
			}
			fout << endl;
			fout.close();
		}
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
inline int SLAU<T>::Gauss_forw(bool file_out, string filename)
{
	ofstream fout;
	if (file_out) {
		fout.open(filename, ofstream::app);
		if (!fout.is_open()) {
			cout << "�� ������� ������� ���� " << filename << endl;
			file_out = false;
		}
		else {
			fout << "�������� �������: " << endl;
			this->Show_in_file(fout, true);
			fout << "����������� ����� ������..." << endl;
		}
	}
	int m = A_base.m;
	int n = A_base.n; rank = 0;
	int k = 0;
	A = A_base; b = b_base;
	solved = false;
	for (int i = 0; i < A.m; ++i)
		pivot[i] = -1;
	for (int j = 0; j < used.size(); ++j) used[j] = false;
	try {
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
			if (max_elem >= n || double(abs(A[max_elem][j])) < acc)
				continue;
			else
			{
				if (file_out) fout << "������������ �� ������ ������� ��������� � " << max_elem << " - �� ������" << endl;
				if (max_elem != k)
				{
					if (file_out) fout << "������ ������� ������ � ��������� " << max_elem << " � " << k << endl;
					swap(A[max_elem], A[k]);
					swap(b[max_elem], b[k]);
					if (file_out) { cout << endl; this->Show_in_file(fout); }
				}
				pivot[j] = k;
				k++;
				used[k - 1] = true;
				for (int l = k; l < n; ++l)
				{
					T d = A[l][j] / A[k - 1][j];
					if (file_out) fout << "�������� �� " << l << "-�� ������ " << k - 1 << " ������, ���������� �� " << d << endl;
					A[l] -= A[k - 1] * d;
					b[l] -= b[k - 1] * d;
					A[l][j] = T(0);
				}
				if (file_out) {
					fout << endl; this->Show_in_file(fout);
				}
			}
		}
	}
	catch (const std::overflow_error& ex) {
		if (file_out) fout << ex.what() << '\n';
		std::cerr << ex.what() << '\n';
		rat_overflow = true;
	}
	if (file_out) {this->Show_in_file(fout);
	fout << "����� ������ ��������." << endl;
	fout.close();
	}
	this->Show();
	solved = true;
	rank = k;
	return rank;
}

template<typename T>
inline Matrix<T> SLAU<T>::Gauss_back(bool file_out, string filename)
{
	int m = A.m;
	int n = A.n;
	ofstream fout;
	if (file_out) {
		fout.open(filename, ofstream::app);
		if (!fout.is_open()) {
			cout << "�� ������� ������� ���� " << filename << endl;
			file_out = false;
		}
	}
	try
	{
		if (solved) {
			for (int i = 0; i < n; ++i)
				if (used[i] == false && double(abs(b[i])) < acc);

				else if (used[i] == false)
				{
					if (file_out) fout << "������� �����������. " << endl;
					cout << "������� �����������. ";
					solex = false;
					return x;
				}
			x.cl_resize(m, m - rank + 1);
			for (int j = 0; j < m; ++j)
				if (pivot[j] >= 0)
					for (int i = pivot[j] - 1; i >= 0; i--)
					{
						T d = A[i][j] / A[pivot[j]][j];
						A[i] -= A[pivot[j]] * d;
						b[i] -= b[pivot[j]] * d;
						A[i][j] = T(0);
					}

			cout << "���� ������� = " << rank << endl;
			if (file_out) fout<< "���� ������� = " << rank << endl;
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
							x[j][k++] = T(0) - A[pivot[j]][l] / A[pivot[j]][j];
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
			if (file_out) fout << "������� �������� ����� ������ ��� �������-������." << endl;
			cout << "������� �������� ����� ������ ��� �������-������." << endl;
		}
	}
	catch (const std::overflow_error& ex) {
		if (file_out) fout << ex.what() << '\n';
		std::cerr << ex.what() << '\n';
		rat_overflow = true;
	}
	if (file_out) fout.close();
	return x;
}

template<typename T>
inline Row<T> SLAU<T>::check_res(bool file_out, string filename)
{
	int m = A_base.m;
	Row<T> res;
	Row<T> frw(m);
	ofstream fout;
	if (file_out) {
		fout.open(filename, ofstream::app);
		if (!fout.is_open()) {
			cout << "�� ������� ������� ���� " << filename << endl;
			file_out = false;
		}
	}
	if (solex) {
		for (int i = 0; i < m; ++i)
			frw[i] = x[i][0];
		res = A_base * frw - b_base;
		//cout << "�������: "<<endl;
		res.Show();
		if (file_out) { fout << "�������: " << endl; res.Show_in_file(fout); }
	}
	else { 
		cout << "���������� ��������� �������. " << endl; 
		if (file_out) fout << "���������� ��������� �������. " << endl;
	}
	fout.close();
	return res;
}

template<typename T>
inline int SLAU<T>::JGauss(bool file_out, string filename)
{
	ofstream fout;
	if (file_out) {
		fout.open(filename, ofstream::app);
		if (!fout.is_open()) {
			cout << "�� ������� ������� ���� " << filename << endl;
			file_out = false;
		}
		else {
			fout << "�������� �������: " << endl;
			this->Show_in_file(fout, true);
			fout << "����������� ����� �������-������..." << endl;
		}
	}
	int m = A_base.m;
	int n = A_base.n; rank = 0;
	int k = 0;
	A = A_base; b = b_base;
	solved = false;
	for (int i = 0; i < A.m; ++i)
		pivot[i] = -1;
	for (int j = 0; j < used.size(); ++j) used[j] = false;
	try
	{
		for (int j = 0; j < m; ++j)
		{
			int max_elem = k;
			for (int i = k; i < n; ++i)
				if (abs(double(A[i][j])) < acc)
					A[i][j] = T(0);
				else if (abs(A[i][j]) > abs(A[max_elem][j]))
					max_elem = i;
			if (max_elem >= n || double(abs(A[max_elem][j])) < acc)
				continue;
			else
			{
				if (file_out) fout << "������������ �� ������ ������� ��������� � " << max_elem << " - �� ������" << endl;
				if (max_elem != k)
				{
					if (file_out) fout << "������ ������� ������ � ��������� " << max_elem << " � " << k << endl;
					swap(A[max_elem], A[k]);
					swap(b[max_elem], b[k]);
					if (file_out) {
						fout << endl; this->Show_in_file(fout);
					}
				}
				pivot[j] = k;
				k++;
				used[k - 1] = true;
				for (int l = 0; l < n; ++l)
				{
					if (l == k - 1)
						continue;
					T d = A[l][j] / A[k - 1][j];
					if (file_out) fout << "�������� �� " << l << "-�� ������ " << k - 1 << " ������, ���������� �� " << d << endl;
					A[l] -= A[k - 1] * d;
					b[l] -= b[k - 1] * d;
					A[l][j] = T(0);
				}
				if (file_out) {
					fout << endl; this->Show_in_file(fout);
				}
			}
		}
	}
	catch (const std::overflow_error& ex) {
		if (file_out) fout << ex.what() << '\n';
		std::cerr << ex.what() << '\n';
		rat_overflow = true;
	}
	
	solved = true;
	rank = k;
	if (file_out) {
		fout << "����� �������-������ ��������." << endl;
		fout.close();
	}
	return rank;
}

template<typename T>
void SLAU<T>::interactive(bool file_out,string filename)
{
	A = A_base; b = b_base;
	solved = false;
	for (int i = 0; i < A.m; ++i)
		pivot[i] = -1;
	for (int j = 0; j < used.size(); ++j) used[j] = false;
	int n = A.n;
	int m = A.m;
	int k = 0;
	ofstream fout; 
	if (file_out)
	{	
		fout.open(filename, ofstream::app);
		if (!fout.is_open())
		{
			cout << "�� ������� ������� ���� " << filename << endl;
			file_out = false;
		}
		else {
			fout << "�������� �������: " << endl;
			this->Show_in_file(fout, true);
			fout << "������������� �����:" << endl;
		}
	}
	try {
		do
		{
			int i, j;
			cout << endl;
			this->Show();
			cout << "�������� ������� �������. " << endl;
			cout << "������� ����� ������: i = ";
			do
			{
				cin >> i;
				if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); i = -1; }
			} while (i < 0 || i >= n);
			cout << "������� ����� ������� j = ";
			do
			{
				cin >> j;
				if (!(cin.good())) { cin.clear(); cin.ignore(); fflush(stdin); j = -1; }
			} while (j < 0 || j >= m);

			if (pivot[j] == -1 && k <= i && double(abs(A[i][j])) > acc)
			{
				if (file_out)
				{
					fout << "������ ������� � ��������� i = " << i << " j = " << j << " � �������� �������� ��������" << endl;
				}
				pivot[j] = k;
				used[k] = true;
				if (i != k) {

					swap(A[i], A[k]);
					swap(b[i], b[k]);
					cout << "������ ������� ������ � ��������� " << i << " � " << k << endl;
					if (file_out)
					{
						fout << "������ ������� ������ � ��������� " << i << " � " << k << endl;
						this->Show_in_file(fout);
					}
					this->Show();
				}
				for (int l = k + 1; l < n; ++l)
				{
					T d = A[l][j] / A[k][j];
					//if (steps_sh) cout << "�������� �� " << l << "-�� ������ " << k  << " ������, ���������� �� " << d << endl;
					A[l] -= A[k] * d;
					b[l] -= b[k] * d;
					A[l][j] = T(0);
				}
				cout << "��������� ���������� x" << j << " �� ����." << endl;
				if (file_out)
				{
					fout << "��������� ���������� x" << j << " �� ����." << endl;
					this->Show_in_file(fout);
				}
				k++;
			}
			else cout << "���� ������� �� ����� ���� ������ � �������� ��������. �������� ������ ������� �������." << endl;

		} while (!end_gauss(k));
	}
	catch (const std::overflow_error& ex) {
		if (file_out) fout << ex.what() << '\n';
		std::cerr << ex.what() << '\n';
		rat_overflow = true;
	}
	if (file_out) { fout << "����� ������ ��������." << endl; fout.close(); }
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
				for (j = k; j < n && double(abs(A[j][i])) < acc; ++j)
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
	A_base.cl_resize(c.A_base.n,c.A_base.m);
	x.cl_resize(c.x.n,c.x.m);
	b_base.resize(c.b_base.size());
	solved = false;
	pivot.resize(c.pivot.size());
	used.resize(c.used.size());
	for (int i = 0; i < A_base.n; ++i)
	{
		b_base[i] = T(c.b_base[i]);
		for (int j = 0; j < A_base.m; ++j)
			A_base(i, j) = T(c.A_base(i, j));
	}
	return *this;
}