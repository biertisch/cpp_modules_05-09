#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) :
	AForm("Presidential Pardon Form", target, 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) :
	AForm(other) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

// Cannot copy anything: all attributes are private in base class
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm&)
{
	return *this;
}

void PresidentialPardonForm::completeExecution() const
{
	std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox.\n";
}
