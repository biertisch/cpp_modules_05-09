#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Vogon"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: _name(name), _grade(grade)
{

		if (grade < 1)
			throw GradeTooHighException();
		else if (grade > 150)
			throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
	: _name(other._name), _grade(other._grade) {}

Bureaucrat::~Bureaucrat() {}

// Assignment only copies grade (name is const)
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
		_grade = other._grade;
	return *this;
}

const std::string& Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

void Bureaucrat::incrementGrade(int nbIncrement)
{
	if (_grade - nbIncrement < 1)
		throw GradeTooHighException();
	_grade -= nbIncrement;
}

void Bureaucrat::decrementGrade(int nbDecrement)
{
	if (_grade + nbDecrement > 150)
		throw GradeTooLowException();
	_grade += nbDecrement;
}

bool Bureaucrat::signForm(AForm& form) const
{
	try
	{
		form.beSigned(*this);
		std::cout << "Bureaucrat " << _name << " signed " << form.getName() << ".\n";
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Bureaucrat " << _name << " couldn't sign " << form.getName()
			<< " because " << e.what() << ".\n";
			return false;
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}