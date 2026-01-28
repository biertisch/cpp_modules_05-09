#include "AForm.hpp"

AForm::AForm(const std::string& name, const std::string& target, const int signGrade, const int execGrade) :
	_name(name),
	_target(target),
	_signGrade(signGrade),
	_execGrade(execGrade),
	_signed(false)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other) :
	_name(other._name),
	_target(other._target),
	_signGrade(other._signGrade),
	_execGrade(other._execGrade),
	_signed(false) {}

AForm::~AForm() {}

// Assignment only copies signed status (other variables are const)
AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
		_signed = other._signed;
	return *this;
}

const std::string& AForm::getName() const
{
	return _name;
}

const std::string& AForm::getTarget() const
{
	return _target;
}

int AForm::getSignGrade() const
{
	return _signGrade;
}

int AForm::getExecGrade() const
{
	return _execGrade;
}

bool AForm::getStatus() const
{
	return _signed;
}

void AForm::beSigned(const Bureaucrat& vogen)
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

void AForm::execute(const Bureaucrat& executor) const
{
	if (_signed)
	{
		if (executor.getGrade() <= _execGrade)
		{
			try
			{
				completeExecution();
			}
			catch (const std::exception& e)
			{
				throw;
			}
		}
		else
			throw GradeTooLowException();
	}
	else
		throw UnsignedFormException();
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "grade is too low";
}

const char* AForm::AlreadySignedException::what() const throw()
{
	return "form has already been signed";
}

const char* AForm::UnsignedFormException::what() const throw()
{
	return "form is not signed";
}

std::ostream& operator<<(std::ostream& os, const AForm& f)
{
	os << f.getName()
		<< ": grade to sign " << f.getSignGrade()
		<< ", grade to execute " << f.getExecGrade()
		<< ", " <<  (f.getStatus() ? "signed" : "unsigned") << ".";
	return os;
}
