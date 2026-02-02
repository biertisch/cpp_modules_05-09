#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) :
	AForm("Shrubbery Creation Form", target, 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) :
	AForm(other) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

// Cannot copy anything: all attributes are private in base class
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm&)
{
	return *this;
}

void ShrubberyCreationForm::completeExecution() const
{
	std::ifstream in("assets/ascii_tree.txt");
	std::ofstream out((getTarget() + "_shrubbery").c_str());
	if (!in || !out)
		throw std::runtime_error("could not open file");

	std::string line;
	while (std::getline(in, line))
		out << line << '\n';

	in.close();
	out.close();

	std::cout << "A beautiful shrub emerges " << getTarget() << ".\n";
}
