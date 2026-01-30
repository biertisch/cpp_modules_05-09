#include "Bureaucrat.hpp"
#include "Form.hpp"

static void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

static void safeSignForm(Bureaucrat* vogon, Form* form)
{
	if (!vogon || !form)
		return;
	vogon->signForm(*form);
}

static Form* createForm(const std::string& name, const int signGrade, const int execGrade)
{
	try
	{
		Form* form = new Form(name, signGrade, execGrade);
		std::cout << *form << '\n';
		return form;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to create " << name << " because " << e.what() << ".\n";
		return NULL;
	}
}

static Bureaucrat* createBureaucrat(const std::string& name, int grade)
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
	Bureaucrat* bReg = createBureaucrat("Reginald P. Clipboard", 13);
	Bureaucrat* bAgn = createBureaucrat("Agnes Formwell", 142);

	printSection("CREATING FORMS");
	Form* fFly = createForm("Flying Saucer Registration Form", 32, 15);
	Form* fTea = createForm("Tea Temperature Regulation Form", 148, 142);
	Form* fCrou = createForm("Crouton Standardization Form", -4, 150); // grade too low
	Form* fErgo = createForm("Ergonomic Chair Compliance Form", 57, 190); // grade too high

	printSection("SIGNING FORMS");
	safeSignForm(bAgn, fFly); // grade too low
	safeSignForm(bReg, fFly);
	safeSignForm(bReg, fFly); // already signed
	safeSignForm(bAgn, fTea);

	// free memory
	delete bReg;
	delete bAgn;
	delete fFly;
	delete fTea;
	delete fCrou;
	delete fErgo;

	return 0;
}
