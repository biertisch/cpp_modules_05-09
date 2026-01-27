#include "Bureaucrat.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title	<< std::string(padding, ' ') << '\n';
	std::cout << std::string(width, '=') << '\n';
}

void alterTryCatch(Bureaucrat *vogon, void (Bureaucrat::*func)(int n), int nb = 1)
{
	if (!vogon)
		return;

	try
	{
		(vogon->*func)(nb);
		std::cout << *vogon << '\n';
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
	alterTryCatch(a, &Bureaucrat::decrementGrade);
	alterTryCatch(a, &Bureaucrat::incrementGrade);
	alterTryCatch(a, &Bureaucrat::incrementGrade); // grade too high
	alterTryCatch(b, &Bureaucrat::incrementGrade, 5);
	alterTryCatch(b, &Bureaucrat::decrementGrade, 50); // grade too low

	// free memory
	delete a;
	delete b;
	delete c;
	delete d;

	return 0;
}