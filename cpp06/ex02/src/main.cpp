#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

static void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

void identify(Base& ref)
{
	std::cout << "Actual type based on reference: ";
	try
	{
		(void)dynamic_cast<A&>(ref);
		std::cout << "A\n";
		return;
	}
	catch (const std::exception&) {}

	try
	{
		(void)dynamic_cast<B&>(ref);
		std::cout << "B\n";
		return;
	}
	catch (const std::exception&) {}

	try
	{
		(void)dynamic_cast<C&>(ref);
		std::cout << "C\n";
		return;
	}
	catch (const std::exception&)
	{
		std::cerr << "unknown\n";
	}
}

void identify(Base* ptr)
{
	std::cout << "Actual type based on pointer: ";
	if (!ptr)
	{
		std::cerr << "Error: null pointer\n";
		return;
	}

	if (dynamic_cast<A*>(ptr))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(ptr))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(ptr))
		std::cout << "C\n";
	else
		std::cerr << "unknown\n";
}

Base* generate()
{
	switch (std::rand() % 3)
	{
		case 0:
			return new (std::nothrow) A();
		case 1:
			return new (std::nothrow) B();
		case 2:
			return new (std::nothrow) C();
		default:
			return NULL;
	}
}

int main()
{
	std::srand(std::time(NULL));

	printSection("Generating Four Objects");
	Base *ptr1 = generate();
	Base *ptr2 = generate();
	Base *ptr3 = generate();
	Base *ptr4 = generate();
	if (!ptr1 || !ptr2 || !ptr3 || !ptr4)
	{
		std::cerr << "Error generating new object\n";
		return 1;
	}

	printSection("Identifying Object 1");
	identify(ptr1);
	identify(*ptr1);

	printSection("Identifying Object 2");
	identify(ptr2);
	identify(*ptr2);

	printSection("Identifying Object 3");
	identify(ptr3);
	identify(*ptr3);

	printSection("Identifying Object 4");
	identify(ptr4);
	identify(*ptr4);

	delete ptr1;
	delete ptr2;
	delete ptr3;
	delete ptr4;

	return 0;
}
