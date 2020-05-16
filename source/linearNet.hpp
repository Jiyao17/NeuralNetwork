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

	Matrix<T> _tempGradW;

	LinearNet(size_t inputLen, size_t outputLen=1, scalar initValW=1, scalar initValB=0);

	Matrix<T>* linearEval(const Matrix<T> &x);

	//scalar eval(const Matrix<T> &x);
	
	void backward(double lr);
	void zeroGrad();
	virtual void grad(const Matrix<T> &x, const Matrix<T> &tag) = 0;
	void train(const Matrix<T>* X, const Matrix<T>* Tag, size_t batchSize, double lr);

	void importNet(std::string filePath);
	void exportNet(std::string filePath);
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

	_tempGradW = new Matrix<T>(_inputLen, _outputLen);
}

template<typename T>
Matrix<T>* LinearNet<T>::linearEval(const Matrix<T> &x)
{
	//std::cout << x;
	//std::cout << _w;
	//std::cout << _y;
	_y = x * _w;
	_y += _b;

	return &_y;
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
	for (size_t i = 0; i < batchSize; i++)
		grad(X[i], Tag[i]);

	_gradW *= 1.0 / batchSize;
	_gradB *= 1.0 / batchSize;
	
	backward(lr);

	zeroGrad();
}

template<typename T>
void LinearNet<T>::exportNet(std::string filePath)
{
	std::ofstream fout(filePath);
	
	for (size_t i = 0; i < _inputLen; i++)
	{
		for (size_t j = 0; j < _outputLen; j++)
			fout << _w[i][j] << " ";

		fout << std::endl;
	}

	for (size_t j = 0; j < _outputLen; j++)
		fout << _b[0][j] << " ";

	fout << std::endl;
}

template<typename T>
void LinearNet<T>::importNet(std::string filePath)
{
	std::ifstream fin(filePath);

	for (size_t i = 0; i < _inputLen; i++)
		for (size_t j = 0; j < _outputLen; j++)
			fin >> _w[i][j];

	for (size_t j = 0; j < _outputLen; j++)
		fin >> _b[0][j];
}



/*
template<typename T>
double LinearNet<T>::Eval(LinearNet<T>:: (* linearEval)(Matrix<T>) le)
{

}
*/

