#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

static void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

template <typename T>
void print_container(const T& container)
{
	for (typename T::const_iterator n = container.begin(); n != container.end(); ++n)
		std::cout << *n << ' ';
	std::cout << '\n';
}

template <typename T>
static void find_wrap(const T& container, int value)
{
	if (easyfind(container, value) != container.end())
		std::cout << "Value " << value << " found.\n";
	else
		std::cout << "Value " << value << " not found.\n";
}

int main()
{
	printSection("TESTING WITH VECTOR");
	int arr_v[] = { 42, 3, -7, 21, 78 };
	std::vector<int> v(arr_v, arr_v + 5);
	print_container(v);
	find_wrap(v, -7);
	find_wrap(v, 78);
	find_wrap(v, 2);

	printSection("TESTING WITH LIST");
	int arr_l[] = { 18, -34, 13, 89, 61 };
	std::list<int> l(arr_l, arr_l + 5);
	print_container(l);
	find_wrap(l, 13);
	find_wrap(l, -34);
	find_wrap(l, 81);

	printSection("TESTING WITH DEQUE");
	int arr_d[] = { 76, 53, -4, 0, 33 };
	std::deque<int> d(arr_d, arr_d + 5);
	print_container(d);
	find_wrap(d, 0);
	find_wrap(d, 76);
	find_wrap(d, 30);
}
