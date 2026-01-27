#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() :
	AForm("Presidential Pardon Form", "unkown", 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) :
	AForm("Presidential Pardon Form", target, 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) :
	AForm(other) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

// Cannot copy anything: all attributes are private in base class
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	(void)other;
	return *this;
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	if (getStatus())
	{
		if (executor.getGrade() <= getExecGrade())
			std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox.";
		else
			throw GradeTooLowException();
	}
	else
		throw UnsignedFormException();
}