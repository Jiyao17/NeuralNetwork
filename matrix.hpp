#pragma once

#include<vector>
#include<iostream>

constexpr int VERBOSITY = 0;

/*
scalar=0 must be available
all functions with return type Matrix<T>*:
return the pointer to the result stored in new memory
don't forget to delete them
*/
template<typename T>
class Matrix
{
public:
	typedef T scalar;
	typedef scalar* vector;
	typedef scalar** matrix;
	typedef std::vector<std::vector<T>> Mat;

	size_t _rowNum;
	size_t _colNum;
	matrix _mat;
	
	Matrix() { _rowNum = 0; _colNum = 0; _mat = nullptr; };
	Matrix(size_t rowNum, size_t colNum, scalar initVal=0);
	// deep copy 
	explicit Matrix(const Matrix<T> &M);
	explicit Matrix(const Mat &M);
	~Matrix();

	//both deep and shallow copy are "safe"
	//they delete previous memory before pointing to the new memory
	//delete this->_mat and shallow copy
	Matrix& operator=(const Matrix *M);
	//delete this->_mat and deep copy
	Matrix& operator=(const Matrix &M);
	Matrix& operator=(const scalar &s);
	//to form a Matrix from STL vector<vector>
	Matrix& operator=(const Mat &M);

	// returns Matrix* to enbale shallow copy
	// don't forget to delete the returned pointer whenever you call these functions
	scalar* operator[](const size_t index) const;
	Matrix* operator*(const Matrix &M) const; 
	Matrix* operator*(const scalar &s) const;
	Matrix* operator+(const Matrix &M) const;
	Matrix* operator+(const scalar &s) const;
	Matrix* operator-(const Matrix &M) const;
	Matrix* operator-(const scalar &s) const;
	// +/- to M itself
	// more efficient than upper versions(except *=Matrix)
	Matrix& operator*=(const Matrix &M);
	Matrix& operator*=(const scalar &s);
	Matrix& operator+=(const Matrix &M);
	Matrix& operator+=(const scalar &s);
	Matrix& operator-=(const Matrix &M);
	Matrix& operator-=(const scalar &s);

	// currently only row vec -> col vec or vice versa supported
	// no propagation
	// return a new Matrix*, don't forget to delete it
	Matrix* view(size_t rowNum, size_t colNum);
	// recast the matrix itself
	Matrix& reshape(size_t rowNum, size_t colNum);

	void clear();
	//friend std::ostream& operator<<(std::ostream &os, const Matrix &M);
};

template<typename T>
Matrix<T>::Matrix(size_t rowNum, size_t colNum, scalar initVal)
{
	if (VERBOSITY)
		std::cout << "constructor M(r, c, init) called." << std::endl;
	
	/*
	// bad kids suck
	if (rowNum <= 0 || colNum <= 0)
		throw "Invalid size.";
	*/
	_rowNum = rowNum;
	_colNum = colNum;
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new scalar[_colNum];
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] = initVal;
	}
}

template<typename T>
Matrix<T>::Matrix(const Mat &M)
{
	if (VERBOSITY)
		std::cout << "copy constructor Mat& called." << std::endl;
	/*
	//stupid kids suffer
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

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new scalar[_colNum];
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] = M[i][j];
	}
		
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &M)
{
	if (VERBOSITY)
		std::cout << "copy constructor Matrix<T>& called." << std::endl;

	_rowNum = M._rowNum;
	_colNum = M._colNum;
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new scalar[_colNum];
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] = M._mat[i][j];
	}
}

template<typename T>
Matrix<T>::~Matrix()
{
	if (VERBOSITY)
		std::cout << "destructor ~M() called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		delete[] _mat[i];

	delete[] _mat;
}

template<typename T>
T* Matrix<T>::operator[](size_t index) const
{
	if (VERBOSITY)
		std::cout << "Matrix.operator[]() called." << std::endl;

	/*
	// stupid kids suffer
	if (index >= _rowNum)
		throw "Matrix index out of range.";
	*/

	return _mat[index];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix *M)
{
	//shallow copy
	if (VERBOSITY)
		std::cout << "shallow operator=(Matrix*) called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		delete[] _mat[i];
	delete[] _mat;

	_rowNum = M->_rowNum;
	_colNum = M->_colNum;
	_mat = M->_mat;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix &M)
{
	//deep copy
	if (VERBOSITY)
		std::cout << "deep operator=(Matrix&) called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		delete[] _mat[i];
	delete[] _mat;

	_rowNum = M._rowNum;
	_colNum = M._colNum;
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new scalar[_colNum];
		for (size_t j = 0; j < _colNum; j++)
		{
			_mat[i][j] = M._mat[i][j];
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const scalar &s)
{
	//deep copy
	if (VERBOSITY)
		std::cout << "deep operator=(scalar&) called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
	{
		for (size_t j = 0; j < _colNum; j++)
		{
			_mat[i][j] = s;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Mat &M)
{
	//deep copy
	if (VERBOSITY)
		std::cout << "deep operator=(Matrix&) called." << std::endl;

	/*
	// stupid kids suffer
	rowNum = M.capacity();
	if (_rowNum == 0)
		return;
	else
		_rowNum = rowNum;
	colNum = M[0].capacity();
	if (colNum == 0)
		return;
	else
		_colNum = M[0].capacity();
	*/

	for (size_t i = 0; i < _rowNum; i++)
		delete[] _mat[i];
	delete[] _mat;

	
	_rowNum = M.capacity();
	_colNum = M[0].capacity();
	_mat = new vector[_rowNum];

	for (size_t i = 0; i < _rowNum; i++)
	{
		_mat[i] = new scalar[_colNum];
		for (size_t j = 0; j < _colNum; j++)
		{
			_mat[i][j] = M[i][j];
		}
	}

	return *this;
}

template<typename T>
Matrix<T>* Matrix<T>::operator*(const Matrix &M) const
{
	/*
	//C++: careless kids suffer
	// illegal multiplication
	if (_colNum != M._rowNum)
		throw "ILLegal multiplication: firstMatrixColNum != secondMatrixRowNum";
	*/
	if (VERBOSITY)
		std::cout << "operator* called." << std::endl;

	// (scalar -> 0) must be possible
	Matrix* temp = new Matrix<T>(_rowNum, M._colNum, 0);

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < M._colNum; j++)
			for (size_t k = 0; k < M._rowNum; k++)
			{
				scalar a = _mat[i][k] * M._mat[k][j];
				temp->_mat[i][j] += _mat[i][k] * M._mat[k][j];
			}
			
	return temp;
}

template<typename T>
Matrix<T>* Matrix<T>::operator*(const scalar &s) const
{
	if (VERBOSITY)
		std::cout << "Matrix.operator* scalar called." << std::endl;

	//deep copy

	Matrix* temp = new Matrix(*this);

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
			temp->_mat[i][j] *= s;

	return temp;
}

template<typename T>
Matrix<T>* Matrix<T>::operator+(const Matrix &M) const
{
	/*
	// careless kids suffer
	// illegal add
	if (_rowNum != M._rowNum || _colNum != M._colNum)
		throw "ILLegal M+M: row or colum numbers do not equal.";
	*/
	std::cout << "operator+ Matrix called." << std::endl;

	//deep copy
	Matrix* temp = new Matrix(*this);

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < M._colNum; j++)
			temp->_mat[i][j] += M._mat[i][j];

	return temp;
}

template<typename T>
Matrix<T>* Matrix<T>::operator+(const scalar &s) const
{
	
	if (VERBOSITY)
		std::cout << "operator+ scalar called." << std::endl;

	//deep constructor + shallow copy = deep copy
	//but "Matrix temp(*this);" is wrong because temp is destructed after return
	Matrix* temp = new Matrix(*this);

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
			temp->_mat[i][j] += s;

	return temp;
}

template<typename T>
Matrix<T>* Matrix<T>::operator-(const Matrix &M) const
{
	if (VERBOSITY)
		std::cout << "M.operator-(M) scalar called." << std::endl;

	Matrix* negM = M * (-1);
	Matrix* result = *this + *negM;
	// memory leakage without this line
	delete negM;

	// return *this + M * (-1); causes mamory leakage
	return result;
}

template<typename T>
Matrix<T>* Matrix<T>::operator-(const scalar &s) const
{
	if (VERBOSITY)
		std::cout << "M.operator-(s) scalar called." << std::endl;

	return *this + ((-1) * s);
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &M)
{
	if (VERBOSITY)
		std::cout << "M.operator*= Matrix called." << std::endl;

	//delete this->_mat, then shallow copy
	*this = *this * M;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const scalar &s)
{
	if (VERBOSITY)
		std::cout << "M.operator*=s called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] *= s;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix &M)
{

	if (VERBOSITY)
		std::cout << "M.operator+= Matrix called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < M._colNum; j++)
			_mat[i][j] += M._mat[i][j];

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const scalar &s)
{

	if (VERBOSITY)
		std::cout << "M.operator+=(s) scalar called." << std::endl;

	//"deep" add
	//do not ustilize +, which needs a new Matrix
	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
			_mat[i][j] += s;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix &M)
{

	if (VERBOSITY)
		std::cout << "M.operator-= Matrix called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		for (size_t j = 0; j < M._colNum; j++)
			_mat[i][j] -= M._mat[i][j];

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const scalar &s)
{
	if (VERBOSITY)
		std::cout << "M.operator-=(s) scalar called." << std::endl;

	*this += (-1)*s;

	return *this;
}

template<typename T>
Matrix<T>* Matrix<T>::view(size_t rowNum, size_t colNum)
{
	Matrix* temp = new Matrix(rowNum, colNum);

	size_t indexRow;
	size_t indexCol;
	for(size_t i=0; i<_rowNum; i++)
		for (size_t j = 0; j < _colNum; j++)
		{
			indexRow = i * j / colNum;
			indexCol = i * j % colNum;
			(*temp)[indexRow][indexCol] = _mat[i][j];
		}

	return temp;
}

template<typename T>
Matrix<T>& Matrix<T>::reshape(size_t rowNum, size_t colNum)
{
	Matrix temp(*this);

	*this = new Matrix(rowNum, colNum);
	size_t indexRow;
	size_t indexCol;
	size_t count = 0;
	for (size_t i = 0; i < temp._rowNum; i++)
	{
		for (size_t j = 0; j < temp._colNum; j++)
		{
			indexRow = count / colNum;
			indexCol = count % colNum;
			scalar a = temp._mat[i][j];
			_mat[indexRow][indexCol] = a;

			count++;
		}
	}

	return *this;
}

template<typename T>
void Matrix<T>::clear()
{

}

template<typename T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &M)
{
	for (size_t i = 0; i < M._rowNum; i++)
	{
		for (size_t j = 0; j < M._colNum; j++)
		{
			os << M._mat[i][j] << ' ';
		}

		os << std::endl;
	}

	return os;
}


/*
	Matrix<T>* mat = new Matrix<T>;
	mat->_rowNum = 1;
	mat->_colNum = _colNum;
	mat->_mat = new scalar[_colNum];

	for (size_t i = 0; i < _colNum; i++)
		(mat->_mat)[i] = _mat[index][i];

	return mat;


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Vector<T> &V)
{
	//deep copy
	std::cout << "deep operator=(Vector&) called." << std::endl;

	for (size_t i = 0; i < _rowNum; i++)
		delete[] _mat[i];
	delete[] _mat;

	_rowNum = 1;
	_colNum = V.size;

	_mat = new vector;
	_mat[0] = new scalar[_rowNum];
	for (size_t i = 0; i < _colNum; i++)
	{
		_mat[i] = V.vec[i];
	}

	return *this;
}



template<typename T>
class Matrix;

template<typename T>
class Vector
{
public:
	typedef T scalar;
	typedef scalar* vector;
	typedef std::vector<T> Vec;
	typedef vector* matrix;

	vector _vec;
	size_t _size;

	Vector() { };
	Vector(size_t size, scalar initVal);
	Vector(Vec &V);
	explicit Vector(Matrix<T>);
	~Vector();

	Vector& operator=(const Matrix<T> &M);
	Vector& operator=(const Vector* V);


};

template<typename T>
Vector<T>::Vector(size_t size, scalar initVal)
{
	_size = size;
	_vec = new scalar[_size];
	for (size_t i = 0; i < _size; i++)
		_vec[i] = initVal;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _vec;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Matrix<T> &M)
{
	_size = M._colNum;
	_vec = new scalar[_size];
	for (size_t i = 0; i < _size; i++)
		_vec[i] = M._mat[0][i];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector* V)
{
	_size = V->_size;
	_vec = V->_vec;

	return *this;
}

*/
