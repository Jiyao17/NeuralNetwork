#pragma once

#include "linearNet.hpp"

#include<cmath>

template<typename T>
class SoftmaxNet : public LinearNet<T>
{
public:
	typedef T scalar;

	size_t _maxNumIndex;
	

	SoftmaxNet(size_t inputLen, size_t outputLen, scalar initValW = 1, scalar initValB = 0);

	size_t maxElem(Matrix<T> &M, size_t rowNum = 0);
	size_t softmax();
	size_t eval(const Matrix<T> &x);
	void grad(const Matrix<T> &x, const Matrix<T> &tag);
};

template<typename T>
SoftmaxNet<T>::SoftmaxNet(size_t inputLen, size_t outputLen, scalar initValW, scalar initValB)
	:LinearNet<T>(inputLen, outputLen, initValW, initValB) 
{
	// randomized initial values converge faster
	scalar r;
	int sign;
	for (size_t i = 0; i < inputLen; i++)
		for (size_t j = 0; j < outputLen; j++)
		{
			r = rand() % 1000000 / 1000000.0 * 1;
			sign = rand() % 2 ? -1 : 1;
			r *= sign;
			(this->_w)[i][j] = r;
			//(this->_w)[i][j] = 1;
		}

	for (size_t j = 0; j < outputLen; j++)
	{
		r = rand() % 1000000 / 1000000.0 * 1;
		sign = rand() % 2 ? -1 : 1;
		r *= sign;
		(this->_b)[0][j] = r;
	}
}

template<typename T>
size_t SoftmaxNet<T>::softmax()
{
	scalar expSum = 0;

	//avoid overflow
	//may underflow as 0, which is much better and meaningful than overflow
	_maxNumIndex = (this->_y).maxElemIndex(0, 0);
	this->_y -= (this->_y)[0][_maxNumIndex];

	for (size_t i = 0; i < this->_outputLen; i++)
	{
		(this->_y)[0][i] = exp((this->_y)[0][i]);
		expSum += (this->_y)[0][i];
	}
	this->_y /= expSum;

	_maxNumIndex = (this->_y).maxElemIndex(0, 0);
	return _maxNumIndex;
}

template<typename T>
size_t SoftmaxNet<T>::eval(const Matrix<T> &x)
{
	this->linearEval(x);
	//std::cout << this->_y;
	return softmax();
}

template<typename T>
void SoftmaxNet<T>::grad(const Matrix<T> &x, const Matrix<T> &tag)
{
	eval(x);
	//std::cout << this->_y;
	
	//Matrix<T>* tempGradB = new Matrix(1, this->_outputLen, 0);

	// d_y / d_w
	//std::cout << _tempY;
	this->_y -= scalar(1);
	//std::cout << _tempY;
	size_t i = tag[0][0];
	//for (size_t i = 0; i < this->_outputLen; i++)
	//{
		
		//std::cout << this->_tempGradW;
		//std::cout << x;
		//std::cout << this->_y;
		
		for (size_t j = 0; j < this->_inputLen; j++)
		{
			//std::cout << _tempY;
			(this->_tempGradW)[j][i] = (this->_y)[0][i] * x[0][j];
		}
	//}
	//this->_y -= 1;
	//std::cout << this->_tempGradW;
	//std::cout << this->_y;

	this->_gradW += this->_tempGradW;
	
	//this->_gradB += this->_tempY;
	(this->_gradB)[0][i] += (this->_y)[0][i];
	//std::cout << "gradB:" << this->_gradB;
}

/*

*/
