#pragma once

#include "linearNet.hpp"

#include<cmath>

template<typename T>
class SoftmaxNet : public LinearNet<T>
{
public:
	typedef T scalar;

	size_t _batchSize;

	SoftmaxNet(size_t inputLen, size_t outputLen, scalar initVal=1, scalar initValB=0, size_t batchSize=10);

	Matrix<T>* softmax(Matrix<T>* o, double base=2);
	double eval(Matrix<T> &x);
	// cross entropy
	double loss(Matrix<T> &x, const Matrix<T> &yTag);
	void backward();
};

template<typename T>
SoftmaxNet<T>::SoftmaxNet(size_t inputLen, size_t outputLen, scalar initValNet, scalar initValB, size_t batchSize)
	:LinearNet<T>(inputLen, outputLen, initValNet, initValB)
{
	_batchSize = batchSize;
}

template<typename T>
Matrix<T>* SoftmaxNet<T>::softmax(Matrix<T>* o, double base)
{
	//Matrix* y = new Matrix(1, _outputLen, 0);
	double expSum = 0;
	for (size_t i = 0; i < _outputLen; i++)
	{
		(*o)[0][i] = pow(base, (*o)[0][i]);
		expSum += (*o)[0][i];
	}

	for (size_t i = 0; i < _outputLen; i++)
	{
		(*o)[0][i] /= expSum;
	}

	return o;
}

template<typename T>
double SoftmaxNet<T>::eval(Matrix<T> &x)
{
	return softmax(linearEval(x));
}

template<typename T>
double SoftmaxNet<T>::loss(Matrix<T> &x, const Matrix<T> &yTag)
{
	Matrix* y = eval(linearEval(x));



	delete y;
}

/*

*/
