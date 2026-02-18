#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

class Span
{
	private:
		unsigned int _capacity;
		std::vector<int> _container;

	public:
		Span(unsigned int capacity = 10);
		Span(const Span& other);
		~Span();

		Span& operator=(const Span& other);

		int& operator[](unsigned int index);
		int operator[](unsigned int index) const;

		std::size_t size() const;

		void addNumber(int value);

		unsigned int longestSpan() const;
		unsigned int shortestSpan() const;

		template <typename Iterator>
		void addRange(Iterator first, Iterator last)
		{
			for (; first != last; ++first)
			{
				if (_container.size() >= _capacity)
					throw std::length_error("Container is full");
				_container.push_back(*first);
			}
		}
};

std::ostream& operator<<(std::ostream& os, const Span& sp);
