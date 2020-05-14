#pragma once

//#include "linearNet.hpp"

#include<cmath>

template<typename T>
class SoftmaxNet : public LinearNet<T>
{
public:
	typedef T scalar;

	SoftmaxNet(size_t inputLen, size_t outputLen, scalar initVal=1, scalar initValB=0);

	Matrix<T>* softmax(Matrix<T>* o, double base=2);
	double eval(Matrix<T> &x);
	// cross entropy
	double grad(Matrix<T> &x, const Matrix<T> &yTag);
	void backward();
};

template<typename T>
SoftmaxNet<T>::SoftmaxNet(size_t inputLen, size_t outputLen, scalar initValNet, scalar initValB)
	:LinearNet<T>(inputLen, outputLen, initValNet, initValB)
{

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
double SoftmaxNet<T>::grad(Matrix<T> &x, const Matrix<T> &yTag)
{
	Matrix* y = eval(linearEval(x));



	delete y;
}

/*

*/
