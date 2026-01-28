#include "Form.hpp"

Form::Form(const std::string& name, const int signGrade, const int execGrade) :
	_name(name),
	_signGrade(signGrade),
	_execGrade(execGrade),
	_signed(false)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other) :
	_name(other._name),
	_signGrade(other._signGrade),
	_execGrade(other._execGrade),
	_signed(false) {}

Form::~Form() {}

// Assignment only copies signed status (other variables are const)
Form& Form::operator=(const Form& other)
{
	if (this != &other)
		_signed = other._signed;
	return *this;
}

const std::string& Form::getName() const
{
	return _name;
}

int Form::getSignGrade() const
{
	return _signGrade;
}

int Form::getExecGrade() const
{
	return _execGrade;
}

bool Form::getStatus() const
{
	return _signed;
}

void Form::beSigned(const Bureaucrat& vogen)
{
	if (!_signed)
	{
		if (vogen.getGrade() <= _signGrade)
			_signed = true;
		else
			throw GradeTooLowException();
	}
	else
		throw AlreadySignedException();
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "grade is too low";
}

const char* Form::AlreadySignedException::what() const throw()
{
	return "form has already been signed";
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
	os << f.getName()
		<< ": grade to sign " << f.getSignGrade()
		<< ", grade to execute " << f.getExecGrade()
		<< ", " <<  (f.getStatus() ? "signed" : "unsigned") << ".";
	return os;
}