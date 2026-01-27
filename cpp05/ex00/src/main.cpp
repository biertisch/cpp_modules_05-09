#include "Bureaucrat.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title	<< std::string(padding, ' ') << '\n';
	std::cout << std::string(width, '=') << '\n';
}

void decrementTryCatch(Bureaucrat *vogon)
{
	if (!vogon)
		return;
	try
	{
		--(*vogon);
		std::cout << "Demoted: " << *vogon << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void incrementTryCatch(Bureaucrat *vogon)
{
	if (!vogon)
		return;
	try
	{
		++(*vogon);
		std::cout << "Promoted: " << *vogon << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Bureaucrat* createTryCatch(const std::string& name, int grade)
{
	try
	{
		Bureaucrat* vogon = new Bureaucrat(name, grade);
		std::cout << *vogon << '\n';
		return vogon;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return NULL;
	}
}

int main()
{
	printSection("CREATING BUREAUCRATS");
	Bureaucrat* a = createTryCatch("a", 1);
	Bureaucrat* b = createTryCatch("b", 150);
	Bureaucrat* c = createTryCatch("c", 0); // grade too high
	Bureaucrat* d = createTryCatch("d", 151); // grade too low

	printSection("INCREMENTING & DECREMENTING GRADES");
	decrementTryCatch(a);
	incrementTryCatch(a);
	incrementTryCatch(a); // grade too high
	incrementTryCatch(b);
	decrementTryCatch(b);
	decrementTryCatch(b); // grade too low
	decrementTryCatch(b); // grade too low

	// free memory
	delete a;
	delete b;
	delete c;
	delete d;

	return 0;
}