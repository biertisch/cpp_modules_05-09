#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) :
	AForm("Robotomy Request Form", target, 72, 45)
{
	std::srand(std::time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) :
	AForm(other)
{
	std::srand(std::time(NULL));
}

RobotomyRequestForm::~RobotomyRequestForm() {}

// Cannot copy anything: all attributes are private in base class
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	(void)other;
	return *this;
}

void RobotomyRequestForm::completeExecution() const
{
	std::cout << "*BZZZZZ BRRRRRRRRRRRRR ZRRRRRRRRRR BR BRR BRRRRR*\n";
	if (std::rand() % 2)
		std::cout << getTarget() << " has been successfully robotomized!\n";
	else
		std::cout << getTarget() << "'s robotomy failed.\n";
}
