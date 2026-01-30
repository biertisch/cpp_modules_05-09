#include "ScalarConverter.hpp"

void ScalarConverter::convertChar(const std::string& input)
{
	char value = input[0];

	if (isprint(value))
		std::cout << "char: '" << value << "'\n";
	else
		std::cout << "char: Non displayable\n";

	std::cout << "int: " << static_cast<int>(value) << "\n";
	std::cout << "float: " << static_cast<float>(value) << "f\n";
	std::cout << "double: " << static_cast<double>(value) << "\n";
}

void ScalarConverter::convertInt(const std::string& input)
{
	int value = atoi(input.c_str());

	if (value >= 0 && value <= 127 && isprint(value))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";

	std::cout << "int: " << value << "\n";
	std::cout << "float: " << static_cast<float>(value) << "f\n";
	std::cout << "double: " << static_cast<double>(value) << "\n";
}

void ScalarConverter::convertFloat(const std::string& input)
{
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return convertPseudo(input);

	float value = strtof(input.c_str(), NULL);

	if (value >= 0 && value <= 127 && isprint(static_cast<int>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";

	if (value >= std::numeric_limits<int>::min()
		&& value <= std::numeric_limits<int>::max())
		std::cout << "int: " << static_cast<int>(value) << "\n";
	else
		std::cout << "int: out of range\n";

	std::cout << "float: " << value << "f\n";
	std::cout << "double: " << static_cast<double>(value) << "\n";
}

void ScalarConverter::convertDouble(const std::string& input)
{
	if (input == "-inf" || input == "+inf" || input == "nan")
		return convertPseudo(input);

	double value = strtod(input.c_str(), NULL);

	if (value >= 0 && value <= 127 && isprint(static_cast<int>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";

	if (value >= std::numeric_limits<int>::min()
		&& value <= std::numeric_limits<int>::max())
		std::cout << "int: " << static_cast<int>(value) << "\n";
	else
		std::cout << "int: out of range\n";

	if (value >= -std::numeric_limits<float>::max()
		&& value <= std::numeric_limits<float>::max())
		std::cout << "float: " << static_cast<float>(value) << "f\n";
	else
		std::cout << "int: out of range\n";

	std::cout << "double: " << value << "\n";
}

void ScalarConverter::convertPseudo(const std::string& input)
{
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";

	if (input == "-inf" || input == "-inff")
	{
		std::cout << "float: -inff\n";
		std::cout << "double: -inf\n";
	}
	else if (input == "+inf" || input == "+inff")
	{
		std::cout << "float: +inff\n";
		std::cout << "double: +inf\n";
	}
	else
	{
		std::cout << "float: nanf\n";
		std::cout << "double: nan\n";
	}
}
