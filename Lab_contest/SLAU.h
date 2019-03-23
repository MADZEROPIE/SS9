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
	~SLAU();
};

