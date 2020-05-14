#pragma once

#include "linearNet.hpp"
//#include "matrix.hpp"

template<typename T>
class LinearReg: public LinearNet<T>
{
public:
	typedef T scalar;
	
	//using LinearNet<T>::linearEval;

	LinearReg(size_t inputLen, size_t outputLen = 1, scalar initValW = 1, scalar initValB = 0)
		:LinearNet<T>(inputLen, outputLen, initValW, initValB) { };
	//scalar eval(const Matrix<T> &x);
	void grad(const Matrix<T> &x, const Matrix<T> &tag);
	//void train(const Matrix<T>* X, const Matrix<T>* Tag, size_t batchSize, double lr);
};

template<typename T>
void LinearReg<T>::grad(const Matrix<T>& x, const Matrix<T>& tag)
{
	Matrix<T>* tempGradW;
	//LinearNet<T>* ln = static_cast<LinearNet<T>*>(this);

	this->linearEval(x);
	//std::cout << x;
	//std::cout << this->_y;
	//std::cout << tag;
	this->_y -= tag;

	tempGradW = x * this->_y._mat[0][0];
	tempGradW->reshape(this->_w._rowNum, 1);

	//std::cout << *tempGradW;
	//std::cout << this->_y;

	this->_gradW += *tempGradW;
	this->_gradB += this->_y._mat[0][0];
}

