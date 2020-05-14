#pragma once

#include "vector.hpp"
#include <iostream>

// (scalar -> 0) must be possible to enable Matrix * Matrix
// Operators are defined according to math strictly
template<typename T>
class Matrix
{
	typedef T scalar;
	typedef Vector<scalar> vector;
	typedef vector* matrix;

	matrix _mat;
	size_t _rowNum;
	size_t _colNum;
public:
	typedef std::vector<std::vector<T>> Mat;

	Matrix() { std::cout << "default constructor M() called" << std::endl; };
	Matrix(size_t rowNum, size_t colNum, scalar initVal);
	explicit Matrix(Mat &M);
	explicit Matrix(Matrix<T> &M);

	~Matrix();
	//Matrix(({}) v);

	vector& operator[](unsigned int index);
	Matrix& operator=(Matrix *M);
	Matrix& operator=(Matrix &M);
	Matrix& operator*=(Matrix &M);
	Matrix& operator+(Matrix &M);
	Matrix& operator+(scalar &s);
};

template<typename T>
Matrix<T>::Matrix(size_t rowNum, size_t colNum, scalar initVal)
{
	std::cout << "constructor M(r, c, init) called." << std::endl;
	/*
	// C++: bad kids suck
	if (rowNum <= 0 || colNum <= 0)
		throw "Invalid size.";
	*/
	_rowNum = rowNum;
	_colNum = colNum;
	_mat = new vector[_rowNum];

	// requires copy constructor for scalor
	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = *(new vector(_colNum, initVal));
	}
}

template<typename T>
Matrix<T>::Matrix(Mat &M)
{
	std::cout << "copy constructor Mat& called." << std::endl;
	/*
	//C++: stupid kids suffer
	rowNum = M.capacity();
	if (rowNum == 0)
		return;
	else
		_rowNum = rowNum;
	colNum = M[0].capacity();
	if (colNum == 0)
		return;
	else
		_colNum = M[0].capacity();
	*/

	_rowNum = M.capacity();
	_colNum = M[0].capacity();
	_mat = new vector[_rowNum];

	for (int i = 0; i < _rowNum; i++)
		_mat[i] = new scalar[_colNum];

	for (int i = 0; i < _rowNum; i++)
		for (int j = 0; j < _colNum; j++)
			_mat[i][j] = M[i][j];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &M)
{
	std::cout << "copy constructor Matrix<T>& called." << std::endl;

	_rowNum = M._rowNum;
	_colNum = M._colNum;
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
		_mat[i] = new vector(_colNum);

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] = M._mat[i][j];
}

template<typename T>
Matrix<T>::~Matrix()
{
	std::cout << "destructor ~M() called." << std::endl;
	delete[] _mat;
}

template<typename T>
typename Matrix<T>::vector& Matrix<T>::operator[](size_t index)
{
	std::cout << "Matrix.operator[]() called." << std::endl;
	return _mat[index];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix *M)
{
	//shallow copy

	std::cout << "shallow operator=(Matrix*) called." << std::endl;
	delete[] _mat;

	_rowNum = M->_rowNum;
	_colNum = M->_colNum;
	_mat = M->_mat;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &M)
{
	//deep copy

	std::cout << "deep operator=(Matrix&) called." << std::endl;
	delete[] _mat;

	_rowNum = M._rowNum;
	_colNum = M._colNum;
	
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new vector(_colNum);
		for (size_t j = 0; j < _colNum; j++)
		{
			_mat[i][j] = M[i][j];
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix &M)
{
	/*
	//C++: careless kids suffer
	// illegal multiplication
	if (colNum != M.rowNum)
		throw "ILLegal multiplication: firstMatrixColNum != secondMatrixRowNum";
	*/
	std::cout << "operator*= called." << std::endl;

	Matrix temp(*this);
	delete[] _mat;
	*this = new Matrix<T>(_rowNum, M._colNum, 0);

	// (scalar -> 0) must be possible
	Matrix<T> result(_rowNum, M._colNum, 0);
	// trivial matrix multiplication
	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < M._colNum; j++)
			for (size_t k = 0; k < _colNum; k++)
				_mat[i][j] += temp._mat[i][k] * M[k][j];

	return *this;
}

