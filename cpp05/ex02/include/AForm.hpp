#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm
{
	private:
		const std::string _name;
		const std::string _target;
		const int _signGrade;
		const int _execGrade;
		bool _signed;

	public:
		AForm();
		AForm(const std::string& name, const std::string& target, const int signGrade, const int execGrade);
		AForm(const AForm& other);
		virtual ~AForm();

		AForm& operator=(const AForm& other);

		const std::string& getName() const;
		const std::string& getTarget() const;
		int getSignGrade() const;
		int getExecGrade() const;
		bool getStatus() const;

		void beSigned(const Bureaucrat& signer);
		virtual void execute(const Bureaucrat& executor) const = 0;

		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		class UnsignedFormException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif