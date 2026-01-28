#include "Bureaucrat.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title	<< std::string(padding, ' ') << '\n';
	std::cout << std::string(width, '=') << '\n';
}

void alterTryCatch(Bureaucrat* vogon, void(Bureaucrat::*func)(int), int increment = 1)
{
	if (!vogon)
		return;
	try
	{
		(vogon->*func)(increment);
		std::cout << *vogon << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to change " << vogon->getName() << "'s grade because " << e.what() << ".\n";
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
		std::cerr << "Failed to create " << name << " because " << e.what() << ".\n";
		return NULL;
	}
}

int main()
{
	printSection("CREATING BUREAUCRATS");
	Bureaucrat* a = createTryCatch("Reginald P. Clipboard", 1);
	Bureaucrat* b = createTryCatch("Agnes Formwell", 150);
	Bureaucrat* c = createTryCatch("Edgar Stampington", 151); // grade too low
	Bureaucrat* d = createTryCatch("Beatrice Redtape", 0); // grade too high

	printSection("INCREMENTING & DECREMENTING GRADES");
	alterTryCatch(a, &Bureaucrat::decrementGrade);
	alterTryCatch(a, &Bureaucrat::incrementGrade);
	alterTryCatch(a, &Bureaucrat::incrementGrade); // grade too high
	alterTryCatch(b, &Bureaucrat::incrementGrade);
	alterTryCatch(b, &Bureaucrat::decrementGrade);
	alterTryCatch(b, &Bureaucrat::decrementGrade); // grade too low
	alterTryCatch(b, &Bureaucrat::decrementGrade); // grade too low

	// free memory
	delete a;
	delete b;
	delete c;
	delete d;

	return 0;
}