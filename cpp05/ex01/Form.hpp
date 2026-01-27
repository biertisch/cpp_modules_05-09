#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class Form
{
	private:
		const std::string _name;
		const int _signGrade;
		const int _execGrade;
		bool _signed;

	public:
		Form();
		Form(const std::string& name, const int signGrade, const int execGrade);
		Form(const Form& other);
		~Form();

		Form& operator=(const Form& other);

		const std::string& getName() const;
		int getSignGrade() const;
		int getExecGrade() const;
		bool getStatus() const;

		void beSigned(const Bureaucrat& vogen);

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
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif