#pragma once

#include "matrix.hpp"
#include<ctime>


template<typename T>
//LinearRegTrainSet
class LRTS
{
public:
	typedef T scalar;

	const Matrix<scalar>* _w;
	scalar _wScope;
	scalar _b;
	size_t _xLen;
	scalar _noiseScope;
	size_t _batchSize;

	LRTS(const Matrix<scalar> &w, scalar wScope, scalar b, scalar noiseScope, size_t batchSize);

	
	scalar randFrac();
	Matrix<scalar>* randx();

	void trainSetGen(Matrix<scalar>* X, Matrix<scalar>* T);
};

template<typename T>
LRTS<T>::LRTS(const Matrix<T> &w, T wScope, T b, T noiseScope, size_t batchSize)
{
	_w = &w;
	_b = b;
	_xLen = _w->_rowNum;
	_noiseScope = noiseScope;
	_wScope = wScope;
	_batchSize = batchSize;

	srand((unsigned)time(NULL));
}

template<typename T>
typename LRTS<T>::scalar LRTS<T>::randFrac()
{
	scalar r = rand() % 1000000 / 1000000.0 * _noiseScope;
	int sign = rand() % 2 ? -1 : 1;
	return sign * r;
};

template<typename T>
Matrix<T>* LRTS<T>::randx()
{
	Matrix<T>* x = new Matrix<T>(1, _xLen);

	for (size_t i = 0; i < _xLen; i++)
		(*x)[0][i] = rand() % 100000/100000.0*_wScope;

	return x;
}

template<typename T>
void LRTS<T>::trainSetGen(Matrix<scalar>* X, Matrix<scalar>* T)
{
	for (size_t i = 0; i < _batchSize; i++)
	{
		X[i] = randx();
		T[i] = X[i] * (*_w);
		T[i] += _b + randFrac();
	}
}
