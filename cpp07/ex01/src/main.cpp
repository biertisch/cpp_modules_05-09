#include "iter.hpp"
#include <iostream>
#include <string>

static void printSection(const std::string& title)
{
	int width = 60;
	int padding = (width - title.size()) / 2;
	if (padding < 1)
		padding = 0;

	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

// test functions
template <typename T>
void print(const T& value)
{
	std::cout << value << " ";
}

template <typename T>
void increment(T& value)
{
	++value;
}

void decrementInt(int& value)
{
	--value;
}

int main()
{
	printSection("Testing with int array");
	int int_array[] = {8, 20, 12, 6, -2};

	std::cout << "print<int>:\t";
	iter(int_array, 5, print<int>);

	std::cout << "\nincrement<int>:\t";
	iter(int_array, 5, increment<int>);
	iter(int_array, 5, print<int>);

	std::cout << "\ndecrementInt:\t";
	iter(int_array, 5, decrementInt);
	iter(int_array, 5, print<int>);
	std::cout << "\n";

	printSection("Testing with double array");
	double double_array[] = {4.2, 9.7, -1.3, 2.1, 8.6};

	std::cout << "print<double>:\t\t";
	iter(double_array, 5, print<double>);

	std::cout << "\nincrement<double>:\t";
	iter(double_array, 5, increment<double>);
	iter(double_array, 5, print<double>);
	std::cout << "\n";

	printSection("Testing with std::string");
	const std::string string_array[] = {"apple", "banana", "cherry", "kiwi", "orange"};

	std::cout << "print<std::string>:\t";
	iter(string_array, 5, print<std::string>);
	std::cout << "\n";

	return 0;
}
