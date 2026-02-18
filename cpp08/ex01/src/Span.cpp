#include "Span.hpp"

Span::Span(unsigned int capacity) : _capacity(capacity) {}

Span::Span(const Span& other) :
	_capacity(other._capacity), _container(other._container) {}

Span::~Span() {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_capacity = other._capacity;
		_container = other._container;
	}
	return *this;
}

int& Span::operator[](unsigned int index)
{
	return _container.at(index);
}

int Span::operator[](unsigned int index) const
{
	return _container.at(index);
}

std::size_t Span::size() const
{
	return _container.size();
}

void Span::addNumber(int value)
{
	if (_container.size() >= _capacity)
		throw std::length_error("Container is full");
	_container.push_back(value);
}

unsigned int Span::longestSpan() const
{
	if (_container.size() < 2)
		throw std::length_error("Too few elements to search span");
	int min = *std::min_element(_container.begin(), _container.end());
	int max = *std::max_element(_container.begin(), _container.end());
	return static_cast<unsigned int>(max - min);
}

unsigned int Span::shortestSpan() const
{
	if (_container.size() < 2)
		throw std::length_error("Too few elements to search span");

	std::vector<int> sorted = _container;
	sort(sorted.begin(), sorted.end());

	unsigned int shortest = std::numeric_limits<int>::max();
	for (unsigned int i = 1; i < sorted.size(); i++)
	{
		unsigned int diff = sorted[i] - sorted[i - 1];
		if (diff < shortest)
			shortest = diff;
	}

	return shortest;
}

std::ostream& operator<<(std::ostream& os, const Span& sp)
{
	os << "Span: ";
	for (unsigned int i = 0; i < sp.size(); i++)
		os << sp[i] << " ";
	return os;
}
