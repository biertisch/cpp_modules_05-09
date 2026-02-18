#include <iostream>
#include <list>
#include "MutantStack.hpp"

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
	int values[] = {5, 17, -3, 0};
	MutantStack<int> mstack;

	printSection("Testing push() (5, 17, -3, 0)");
	for (int i = 0; i < 4; ++i)
	{
		mstack.push(values[i]);
		std::cout << mstack << '\n';
	}

	printSection("Testing top()");
	std::cout << mstack.top() << "\n";

	printSection("Testing size()");
	std::cout << mstack.size() << "\n";

	printSection("Testing begin() and end()");
	std::cout << "MutantStack: ";
	for (MutantStack<int>::iterator i = mstack.begin(); i != mstack.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";

	std::list<int> l;
	for (int i = 0; i < 4; ++i)
		l.push_back(values[i]);
	std::cout << "List: ";
	for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";

	printSection("Testing rbegin() and rend()");
	std::cout << "MutantStack: ";
	for (MutantStack<int>::reverse_iterator i = mstack.rbegin(); i != mstack.rend(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";

	std::cout << "List: ";
	for (std::list<int>::reverse_iterator i = l.rbegin(); i != l.rend(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";


	printSection("Testing empty() and pop()");
	while (!mstack.empty())
	{
		mstack.pop();
		std::cout << mstack << "\n";
	}
	return 0;
}
