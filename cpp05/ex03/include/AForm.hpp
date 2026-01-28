#pragma once

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

	protected:
		virtual void completeExecution() const = 0;

	public:
		AForm(const std::string& name = "Useless Form",
			const std::string& target = "unknown",
			const int signGrade = 150,
			const int execGrade = 150);
		AForm(const AForm& other);
		virtual ~AForm();

		AForm& operator=(const AForm& other);

		const std::string& getName() const;
		const std::string& getTarget() const;
		int getSignGrade() const;
		int getExecGrade() const;
		bool getStatus() const;

		void beSigned(const Bureaucrat& signer);
		void execute(const Bureaucrat& executor) const;

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

		class UnsignedFormException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const AForm& f);
