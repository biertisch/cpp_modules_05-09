#include "Bureaucrat.hpp"
#include "Form.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title	<< std::string(padding, ' ') << '\n';
	std::cout << std::string(width, '=') << '\n';
}

void safeSignForm(Bureaucrat* vogon, Form* form)
{
	if (!vogon || !form)
		return;
	vogon->signForm(*form);
}

Form* createForm(const std::string& name, const int signGrade, const int execGrade)
{
	try
	{
		Form* form = new Form(name, signGrade, execGrade);
		std::cout << *form << '\n';
		return form;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return NULL;
	}
}

Bureaucrat* createBureaucrat(const std::string& name, int grade)
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
	Bureaucrat* a = createBureaucrat("Arnold", 13);
	Bureaucrat* b = createBureaucrat("Betty", 142);

	printSection("CREATING FORMS");
	Form* c = createForm("Crouton Uniformization Form", 32, 45);
	Form* d = createForm("Dentist Permission Form", 148, 150);
	Form* e = createForm("Ergonomic Chair Standard Form", -4, 150); // grade too low
	Form* f = createForm("Flying Saucer Identification Form", 57, 190); // grade too high

	printSection("SIGNING FORMS");
	safeSignForm(a, c);
	safeSignForm(b, c); // grade too low
	safeSignForm(a, d);
	safeSignForm(b, d);

	// free memory
	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;

	return 0;
}