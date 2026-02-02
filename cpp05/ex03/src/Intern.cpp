#include "Intern.hpp"

std::string Intern::_knownForms[3] = {
	"presidential pardon",
	"robotomy request",
	"shrubbery creation"
};

Intern::Intern() {}

Intern::Intern(const Intern&) {}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern&)
{
	return *this;
}

AForm* Intern::makeFormInternal(const std::string& name, const std::string& target) const
{
	int index;
	for (index = 0; index < 3; index++)
		if (name == _knownForms[index])
			break;

	switch (index)
	{
		case 0:
			return new PresidentialPardonForm(target);
		case 1:
			return new RobotomyRequestForm(target);
		case 2:
			return new ShrubberyCreationForm(target);
		default:
			throw InvalidFormRequestException();
	}
}

AForm* Intern::makeForm(const std::string& name, const std::string& target) const
{
	try
	{
		AForm* form = makeFormInternal(name, target);
		std::cout << "Intern created " << form->getName() << ".\n";
		return form;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Intern failed to create \"" << name << "\" because " << e.what() << ".\n";
		return NULL;
	}
}

const char* Intern::InvalidFormRequestException::what() const throw()
{
	return "form request is invalid";
}
