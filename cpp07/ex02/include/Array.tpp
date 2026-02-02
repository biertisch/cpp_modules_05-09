#pragma once

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _length(0), _data(NULL)
{
	std::cout << "Default Constructor: Created an empty array of type " << typeid(T).name() << ".\n";
}

template <typename T>
Array<T>::Array(unsigned int length) :  _length(length), _data(new T[length])
{
	std::cout << "Parametrized Constructor: Created an array of size " << _length << " and type " << typeid(T).name() << ".\n";

	for (unsigned int i = 0; i < _length; i++)
		_data[i] = T();
}

template <typename T>
Array<T>::Array(const Array& other) : _length(other._length), _data(new T[other._length])
{
	std::cout << "Copy Constructor: Created an array of size " << _length << " and type " << typeid(T).name() << ".\n";

	for (unsigned int i = 0; i < _length; i++)
		_data[i] = other._data[i];
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;

	std::cout << "Destructor: Array of size " << _length << " and type " << typeid(T).name() << " destroyed.\n";
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		_length = other._length;
		delete[] _data;
		_data = new T[_length];
		for (unsigned int i = 0; i < _length; i++)
			_data[i] = other._data[i];
	}

	std::cout << "Copy assignment: Copied array of size " << _length << " and type " << typeid(T).name() << ".\n";

	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _length)
		throw std::out_of_range("index out of bounds");
	return _data[index];
}

template <typename T>
T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _length)
		throw std::out_of_range("index out of bounds");
	return _data[index];
}


template <typename T>
unsigned int Array<T>::size() const
{
	return _length;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array)
{
	if (!array.size())
		out << "empty array";
	else
	{
		for (unsigned int i = 0; i < array.size(); i++)
			out << array[i] << " ";
	}
	return out;
}
