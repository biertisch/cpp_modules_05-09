#pragma once

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
		Form(const std::string& name = "Useless Form",
			const int signGrade = 150,
			const int execGrade = 150);
		Form(const Form& other);
		~Form();

		Form& operator=(const Form& other);

		const std::string& getName() const;
		int getSignGrade() const;
		int getExecGrade() const;
		bool getStatus() const;

		void beSigned(const Bureaucrat& signer);

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

		class AlreadySignedException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const Form& f);
