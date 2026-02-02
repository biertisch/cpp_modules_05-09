#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	protected:
		void completeExecution() const;

	public:
		PresidentialPardonForm(const std::string& target = "unknown");
		PresidentialPardonForm(const PresidentialPardonForm& other);
		~PresidentialPardonForm();

		PresidentialPardonForm& operator=(const PresidentialPardonForm&);
};
