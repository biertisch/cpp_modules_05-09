#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

void safeExecuteForm(Bureaucrat* vogon, AForm* form)
{
	if (!vogon || !form)
		return;

	std::cout << vogon->getName() << " (grade " << vogon->getGrade() << ") is trying to execute "
		<< form->getName() << " (execute grade " << form->getExecGrade() << "):\n";

	vogon->executeForm(*form);

	std::cout << "\n";
}

void safeSignForm(Bureaucrat* vogon, AForm* form)
{
	if (!vogon || !form)
		return;
	vogon->signForm(*form);
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
	Bureaucrat* bReg = createBureaucrat("Reginald P. Clipboard", 5);
	Bureaucrat* bAgn = createBureaucrat("Agnes Formwell", 42);
	Bureaucrat* bEdg = createBureaucrat("Edgar Stampington", 134);

	printSection("CREATING FORMS");
	PresidentialPardonForm pardon = PresidentialPardonForm("Eustace Wimple");
	std::cout << pardon << "\n";
	RobotomyRequestForm robot1 = RobotomyRequestForm("Nigel Tinkerton");
	std::cout << robot1 << "\n";
	RobotomyRequestForm robot2 = RobotomyRequestForm("Horace Cogsworth");
	std::cout << robot2 << "\n";
	ShrubberyCreationForm shrub = ShrubberyCreationForm("inside the photocopier");
	std::cout << shrub << "\n";

	printSection("SIGNING FORMS");
	safeSignForm(bReg, &pardon);
	safeSignForm(bAgn, &robot1);
	safeSignForm(bEdg, &shrub);

	printSection("EXECUTING FORMS");
	safeExecuteForm(bEdg, &pardon); // grade too low
	safeExecuteForm(bReg, &pardon);
	safeExecuteForm(bEdg, &robot1); // grade too low
	safeExecuteForm(bAgn, &robot1);
	safeExecuteForm(bAgn, &robot1);
	safeExecuteForm(bAgn, &robot1);
	safeExecuteForm(bAgn, &robot1);
	safeExecuteForm(bAgn, &robot2); // form unsigned
	safeExecuteForm(bEdg, &shrub);

	// Free memory
	delete bReg;
	delete bAgn;
	delete bEdg;

	return 0;
}
