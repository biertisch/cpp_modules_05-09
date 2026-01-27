#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title	<< std::string(padding, ' ') << '\n';
	std::cout << std::string(width, '=') << '\n';
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

	printSection("CREATING FORMS");
	PresidentialPardonForm form = PresidentialPardonForm("Mandy");
	std::cout << form;

	a->signForm(form);

	return 0;
}