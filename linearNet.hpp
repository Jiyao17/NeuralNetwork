#pragma once

#include "matrix.hpp"

template<typename T>
class LinearNet
{
public:
	typedef T scalar;

	size_t _inputLen;
	size_t _outputLen;
	Matrix<T> _w;
	Matrix<T> _b;

	Matrix<T> _gradW;
	Matrix<T> _gradB;
	Matrix<T> _y;
	double _loss;
	size_t _batchSize;

	LinearNet(size_t inputLen, size_t outputLen=1, scalar initValW=1, scalar initValB=0);

	Matrix<T>* linearEval(const Matrix<T> &x);

	//scalar eval(const Matrix<T> &x);
	void grad(const Matrix<T> &x, const Matrix<T> &tag);
	void backward(double lr);
	void zeroGrad();

	void train(const Matrix<T>* X, const Matrix<T>* Tag, size_t batchSize, double lr);
};

template<typename T>
LinearNet<T>::LinearNet(size_t inputLen, size_t outputLen, scalar initValW, scalar initValB)
{
	_inputLen = inputLen;
	_outputLen = outputLen;
	_w = new Matrix<T>(_inputLen, _outputLen, initValW);
	_b = new Matrix<T>(1, _outputLen, initValB);

	_gradW = new Matrix<T>(_inputLen, _outputLen);
	_gradB = new Matrix<T>(1, _outputLen);
	_y = new Matrix<T>(1, _outputLen);
	_loss = 0;
}

template<typename T>
Matrix<T>* LinearNet<T>::linearEval(const Matrix<T> &x)
{
	_y = x * _w;
	_y += _b;

	return &_y;
}

template<typename T>
void LinearNet<T>::grad(const Matrix<T>& x, const Matrix<T>& tag)
{
	Matrix<T>* tempGradW;
	
	linearEval(x);
	//std::cout << x;
	//std::cout << _y;
	//std::cout << tag;
	_y -= tag;

	tempGradW = x * _y._mat[0][0];
	tempGradW->reshape(_w._rowNum, 1);

	//std::cout << *tempGradW;
	//std::cout << _y;

	_gradW += *tempGradW;
	_gradB += _y._mat[0][0];
}

template<typename T>
void LinearNet<T>::backward(double lr)
{
	_w -= _gradW;
	_b -= _gradB;
}

template<typename T>
void LinearNet<T>::zeroGrad()
{
	_gradW *= 0;
	_gradB *= 0;
}

template<typename T>
void LinearNet<T>::train(const Matrix<T>* X, const Matrix<T>* Tag, size_t batchSize, double lr)
{
	zeroGrad();

	for (size_t i = 0; i < batchSize; i++)
	{
		grad(X[i], Tag[i]);
	}

	_gradW *= 1.0 / batchSize;
	_gradB *= 1.0 / batchSize;

	backward(lr);
}



/*
template<typename T>
double LinearNet<T>::Eval(LinearNet<T>:: (* linearEval)(Matrix<T>) le)
{

}
*/

