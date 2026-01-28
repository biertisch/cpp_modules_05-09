#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

int main()
{
	Intern intern = Intern();

	printSection("MAKING FORMS");
	AForm* a = intern.makeForm("presidential pardon", "Eustace Wimple");
	AForm* b = intern.makeForm("robotomy request", "Horace Cogsworth");
	AForm* c = intern.makeForm("shrubbery creation", "on boss's ergonomic chair");
	AForm* d = intern.makeForm("unknown", "unknown");

	// Free memory
	delete a;
	delete b;
	delete c;
	delete d;

	return 0;
}
