#include "whatever.hpp"
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

int main()
{
	printSection("Testing with int (a = 2, b = 3)");
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "swap(a, b) --> a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	printSection("Testing with std::string (a = chaine1, b = chaine2)");
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "swap(c, d) --> c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	printSection("Testing with double (a = -48.7, b = 3.5)");
	double e = -48.7;
	double f = 3.5;
	swap(e, f);
	std::cout << "swap(e, f) --> e = " << e << ", f = " << f << std::endl;
	std::cout << "min(e, f) = " << min(e, f) << std::endl;
	std::cout << "max(e, f) = " << max(e, f) << std::endl;

	printSection("Testing with char (g = 'A', h = 'M')");
	char g = 'A';
	char h = 'M';
	swap(g, h);
	std::cout << "swap(g, h) --> g = " << g << ", h = " << h << std::endl;
	std::cout << "min(g, h) = " << min(g, h) << std::endl;
	std::cout << "max(g, h) = " << max(g, h) << std::endl;

	return 0;
}
