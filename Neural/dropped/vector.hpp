
#pragma once

#include<vector>
#include<memory>
#include<iostream>

template<typename T>
class Vector
{
	typedef T scalar;
	typedef shared_ptr<T> vector;

	vector _vec;
	size_t _size;
	// row or colum
	//enum { row, col } _shape;

public:
	size_t size();
	scalar& operator[](unsigned int index) const;
	Vector& operator=(const std::vector<scalar>& vec);
	Vector& operator=(const Vector& vec);
	Vector& operator=(const Vector* vec);

	Vector();
	explicit Vector(size_t size);
	explicit Vector(const std::vector<scalar> &vec);
	// deep copy constructor
	explicit Vector(const Vector<scalar> &vec);
	Vector(size_t size, scalar initVal);
	~Vector();

};

template<typename T>
Vector<T>::Vector()
{
	std::cout << "default constructor V() called." << std::endl;
	_size = 0;
	_vec = nullptr;
	//_shape = shape;
}

template<typename T>
Vector<T>::Vector(size_t len)
{
	std::cout << "constructor V(len) called." << std::endl;
	_size = len;
	_vec = new scalar[_size];
	//_shape = shape;
}

template<typename T>
Vector<T>::Vector(size_t len, scalar initVal)
{
	std::cout << "constructor V(len, init) init called." << std::endl;
	_size = len;
	_vec = new scalar[_size];
	//_shape = shape;

	for (size_t i = 0; i < len; i++)
		_vec[i] = initVal;
}

template<typename T>
Vector<T>::Vector(const std::vector<T> &vec)
{
	std::cout << "constructor std::vector<T> called." << std::endl;
	_size = vec.capacity();
	_vec = new scalar[_size];
	//_shape = shape;

	for (int i = 0; i < _size; i++)
		_vec[i] = vec[i];
}

//deep copy
template<typename T>
Vector<T>::Vector(const Vector<T> &vec)
{
	std::cout << "constructor Vector<T> called." << std::endl;
	// cannot call vec.size(), why?
	_size = vec._size;
	_vec = new T[_size];

	for (size_t i = 0; i < _size; i++)
		_vec[i] = vec[i];
}

template<typename T>
Vector<T>::~Vector()
{
	std::cout << "destructor ~V() called." << std::endl;
	delete[] _vec;
}


template<typename T>
size_t Vector<T>::size()
{
	return _size;
}

template<typename T>
typename Vector<T>::scalar& Vector<T>::operator[](size_t index) const
{
	std::cout << "V.operator[]() called." << std::endl;
	return _vec[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vec)
{
	std::cout << "operator=(Vector<T>&) called." << std::endl;
	// cout << "operator=Vector called." << endl;
	delete[] _vec;
	_size = vec._size;

	_vec = new scalar[_size];

	//if scalar is Vector, memcopy doesn't work
	//memcpy(_vec, vec._vec, _size * sizeof(T));
	//this still works when scalar is Vector
	for (size_t i = 0; i < _size; i++)
		//call operator= again if scalar is Vector
		_vec[i] = vec[i];

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> *vec)
{
	std::cout << "operator=(Vector<T>*) called." << std::endl;
	delete[] _vec;

	_size = vec->_size;
	_vec = vec->_vec;

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const std::vector<scalar> &vec)
{
	std::cout << "operator=(std::ector<T>&) called." << std::endl;
	delete[] _vec;
	_size = vec.capacity();

	_vec = new scalar[_size];
	for (size_t i = 0; i < _size; i++)
		_vec[i] = vec[i];

	return *this;
}


