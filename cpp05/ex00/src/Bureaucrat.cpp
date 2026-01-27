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

Bureaucrat& Bureaucrat::operator++()
{
	if (_grade <= 1)
		throw GradeTooHighException();
	_grade--;
	return *this;
}

Bureaucrat& Bureaucrat::operator--()
{
	if (_grade >= 150)
		throw GradeTooLowException();
	_grade++;
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

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "grade too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "grade too low";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}