#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Span.hpp"

static void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

int main()
{
	printSection("Testing addNumber & span functions (size 5)");
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp << "\n";
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;

	printSection("Testing addRange & span functions (size 10,000)");
	std::srand(std::time(NULL));
	std::vector<int> vec(10000);
	for (int i = 0; i < 10000; ++i)
		vec[i] = rand() % 100000; // adjust range
	Span mega = Span(10000);
	mega.addRange(vec.begin(), vec.end());
	std::cout << "Min: " << *std::min_element(vec.begin(), vec.end()) << "\n";
	std::cout << "Max: " << *std::max_element(vec.begin(), vec.end()) << "\n";
	std::cout << "Shortest span: " << mega.shortestSpan() << std::endl;
	std::cout << "Longest span: " << mega.longestSpan() << std::endl;

	printSection("Testing exception handling when adding elements");
	std::cout << "Adding 10,000 elements to full container sized 5:\n";
	try
	{
		sp.addRange(vec.begin(), vec.end());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nAdding 1 element to full container sized 10,000:\n";
	try
	{
		mega.addNumber(1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nAdding 2 elements to empty container sized 1:\n";
	std::vector<int> arr(2);
	arr[0] = 0;
	arr[1] = 1;
	Span small(1);
	try
	{
		small.addRange(arr.begin(), arr.end());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	printSection("Testing exception handling when getting spans");
	std::cout << "Calling longestSpan on container sized 0:\n";
	Span empty(0);
	try
	{
		std::cout << empty.longestSpan() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nCalling shortestSpan on full container sized 1:\n";
	try
	{
		std::cout << small.shortestSpan() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nCalling shortestSpan on container sized 10 with no elements:\n";
	Span size10(10);
	try
	{
		std::cout << size10.shortestSpan() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nCalling shortestSpan on container sized 10 with 1 element (0):\n";
	size10.addNumber(0);
	try
	{
		std::cout << size10.shortestSpan() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nCalling longestSpan() on container sized 10 with 2 elements (0, 5):\n";
	size10.addNumber(5);
	try
	{
		std::cout << size10.longestSpan() << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}