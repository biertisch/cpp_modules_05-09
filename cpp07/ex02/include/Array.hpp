#pragma once

#include <iostream>
#include <stdexcept>
#include <typeinfo>

template <typename T>
class Array
{
	private:
		unsigned int _length;
		T* _data;

	public:
		Array();
		Array(unsigned int length);
		Array(const Array& other);
		~Array();

		Array& operator=(const Array& other);
		T& operator[](unsigned int index);
		T& operator[](unsigned int index) const;

		unsigned int size() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array);

#include "Array.tpp"
