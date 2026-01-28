#pragma once

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <exception>
#include <string>

class Intern
{
	private:
		static std::string _knownForms[3];
		AForm* makeFormInternal(const std::string& name, const std::string& target) const;

	public:
		Intern();
		Intern(const Intern& other);
		~Intern();

		Intern& operator=(const Intern& other);

		AForm* makeForm(const std::string& name, const std::string& target) const;

		class InvalidFormRequestException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};
