#pragma once

#include "matrix.hpp"
#include<ctime>
#include<string>
#include<iostream>
#include<fstream>

/*

template<typename T>
class DataLoader
{
public:
	typedef T scalar;

	const Matrix<scalar>* _w;
	scalar _wScope;
	scalar _b;
	size_t _xLen;
	scalar _noiseScope;
	size_t _batchSize;
};

*/


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


template<typename T>
class MNISTDATA
{
public:

	size_t _batchSize;
	std::string _trainSetPath;
	std::string _testSetPath;
	std::ifstream _finTrain;
	std::ifstream _finTest;

	MNISTDATA(std::string trainSetPath, std::string testSetPath, size_t batchSize);

	// dataset: 0 for train set, 1 for test set
	void dataSetGen(Matrix<T>* X, Matrix<T>* T, int dataset=0);
	void reset(int dataset=0);

};

template<typename T>
MNISTDATA<T>::MNISTDATA(std::string trainSetPath, std::string testSetPath, size_t batchSize)
{
	_trainSetPath = trainSetPath;
	_testSetPath = testSetPath;
	_finTrain.open(trainSetPath);
	_finTest.open(trainSetPath);
	_batchSize = batchSize;
}

template<typename T>
void MNISTDATA<T>::dataSetGen(Matrix<T>* X, Matrix<T>* T, int dataset)
{
	/*
	X; array of pixels, 1 row 28*28 columns
	Y: array of tags, 1 row 1 column
	*/
	std::ifstream* fin;
	if (dataset)
	{
		fin = &_finTest;
		_batchSize = 1;
	}
	else
		fin = &_finTrain;

	char temp;
	for (size_t i = 0; i < _batchSize; i++)
	{
		(*fin) >> T[i][0][0];
		(*fin) >> temp;
		// 28*28 will be calculated only once during compilation
		// so that needn't be optimized manually
		for (size_t j = 0; j < 28 * 28; j++)
		{
			*fin >> X[i][0][j];
			if(j != 28 * 28 - 1)
				*fin >> temp;
		}

		//uniform, not neccessary
		//X[i] += 1;
		//X[i] /= 255.0;
	}

	
}

template<typename T>
void MNISTDATA<T>::reset(int dataset)
{
	if (dataset)
	{
		_finTest.close();
		_finTest.open(_testSetPath);
	}
	else
	{
		_finTrain.close();
		_finTrain.open(_trainSetPath);
	}
}