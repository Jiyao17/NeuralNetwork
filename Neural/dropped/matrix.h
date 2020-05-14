
#include<vector>
#include<memory>
#include<iostream>

template<typename T>
class Vector
{
	typedef T scalar;
	static void deleter(scalar* p) { delete[] p; std::cout << "deleter called" << std::endl; }
	typedef std::shared_ptr<scalar> vector;

	vector _vec;
	int _size;
	// row or colum
	//enum { row, col } _shape;
public:
	int size();
	scalar& operator[](int index) const;

	Vector(int len);
	Vector(int len, scalar initVal);
	Vector(const std::vector<T> &vec);
	Vector(const Vector &vec);
	~Vector();

};


template<typename T>
int Vector<T>::size()
{
	return _size;
}

template<typename T>
typename Vector<T>::scalar& Vector<T>::operator[](int index) const
{
	return _vec.get()[index];
}


template<typename T>
Vector<T>::Vector(int len)
{
	_size = len;
	scalar* vec = new scalar[_size];
	_vec.reset(vec, &deleter);
	//_shape = shape;
}

template<typename T>
Vector<T>::Vector(int len, scalar initVal)
{
	_size = len;
	scalar* vec = new scalar[_size];
	_vec.reset(vec, &deleter);
	//_shape = shape;

	for (int i = 0; i < len; i++)
		_vec.get()[i] = initVal;
}

template<typename T>
Vector<T>::Vector(const std::vector<T> &vec)
{
	_size = vec.capacity();
	_vec.reset(new scalar[_size], &deleter);
	//_shape = shape;

	for (int i = 0; i < _size; i++)
	{
		_vec.get()[i] = vec[i];
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vec)
{
	_size = vec._size;
	//scalar* v = new scalar[_size];
	_vec.reset(new scalar[_size], &deleter);
	//_shape = shape;

	for (int i = 0; i < _size; i++)
	{
		_vec.get()[i] = vec[i];
	}
}

template<typename T>
Vector<T>::~Vector()
{
	//std::cout << "try to delete" << std::endl;
	_vec.reset();
}




// (scalar -> 0) must be possible to enable Matrix * Matrix
// Operators are defined according to math strictly
template<typename T>
class Matrix
{
	typedef T scalar;
	// enable M[i][j] = a;
	static void deleter(scalar* vec){ delete[] vec; }
	typedef std::shared_ptr<scalar> vector;
	
	typedef std::unique_ptr<vector> matrix;

	matrix _mat;
	int _rowNum;
	int _colNum;
public:
	typedef std::vector<std::vector<T>> Mat;

	Matrix(int rowNum, int colNum, scalar initVal);
	Matrix(Mat &M);
	Matrix(Matrix<T> &M);

	~Matrix();
	//Matrix(({}) v);

	vector operator[](int index);
	Matrix& operator*(Matrix &M);
	Matrix& operator+(Matrix &M);
	Matrix& operator+(scalar &s);
};

template<typename T>
Matrix<T>::Matrix(int rowNum, int colNum, scalar initVal)
{
	/*
	// C++: bad kids suck
	if (rowNum <= 0 || colNum <= 0)
		throw "Invalid size.";
	*/
	_rowNum = rowNum;
	_colNum = colNum;
	_mat.reset(new vector[_rowNum], &deleter);

	for (int i = 0; i < _rowNum; i++)
		_mat.get()[i].reset(new T[_colNum]);
	// requires copy constructor for scalor
	for (int i = 0; i < rowNum; i++)
		for (int j = 0; j < colNum; j++)
			_mat.get()[i].get()[j] = initVal;
}

template<typename T>
Matrix<T>::Matrix(Mat &M)
{
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
	_mat.reset(new vector[_rowNum], &deleter);

	for (int i = 0; i < _rowNum; i++)
		_mat.get()[i].reset(new scalar[_colNum]);

	for (int i = 0; i < _rowNum; i++)
		for (int j = 0; j < _colNum; j++)
			_mat.get()[i].get()[j] = M[i][j];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &M)
{
	_rowNum = M._rowNum;
	_colNum = M._colNum;
	matrix rows(new vector[_rowNum], deleter);
	_mat.move(rows);

	for (int i = 0; i < _rowNum; i++)
		_mat.get()[i].reset(new T[_colNum]);

	for (int i = 0; i < _rowNum; i++)
		memcpy(_mat.get()[i].get(), M._mat.get()[i].get(), M._colNum);
	
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < _rowNum; i++)
		delete _mat.get()[i];

	delete[] _mat.release();
}

template<typename T>
typename Matrix<T>::vector Matrix<T>::operator[](int index)
{
	return _mat.get()[index];
}

template<typename T>
Matrix<T>& Matrix<T>::operator*(Matrix &M)
{
	/*
	//C++: careless kids suffer
	// illegal multiplication
	if (colNum != M.rowNum)
		throw "ILLegal multiplication: firstMatrixColNum != secondMatrixRowNum";
	*/
	
	// (scalar -> 0) must be possible
	Matrix result(_rowNum, M._colNum, 0);
	// trivial matrix multiplication
	for (int i = 0; i < _rowNum; i++)
		for (int j = 0; j < M._colNum; j++)
			for (int k = 0; k < _colNum; k++)
				result._mat.get()[i].get()[j] += _mat.get()[i].get()[k] * M._mat.get()[k].get()[j];
	
	return result;
}

/*
template<typename T>
class Vector
{
	typedef T scalar;
	typedef std::shared_ptr<T> vector;

	vector _vec;
	int _len;
	// row or colum
	enum { row, col } _shape;


public:
	Vector(int len, int shape = 0);
	Vector(int len, scalar initVal, int shape = 0);
	Vector(const std::vector<T> &vec, int shape = 0);
	~Vector();
};

template<typename T>
Vector<T>::Vector(int len, int shape)
{
	_len = len;
	_vec(new T[len]);
	_shape = shape;
}

template<typename T>
Vector<T>::Vector(int len, scalar initVal, int shape)
{
	_len = len;
	_vec.reset(new scalar[len]);
	_shape = shape;

	for (int i = 0; i < len; i++)
		_vec[i] = initVal;
}

template<typename T>
Vector<T>::Vector(const std::vector<T> &vec, int shape)
{
	_len = vec.capacity();
	_v = new T[_len];
	_shape = shape;

	for (int i = 0; i < _len; i++)
	{
		_v[i] = vec[i];
	}
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _vec;
}


*/