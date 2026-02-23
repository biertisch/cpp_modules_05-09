#include "ScalarConverter.hpp"

// Checks if input is not empty and contains no non-printable chars
bool ScalarConverter::validateGeneral(const std::string& input)
{
	if (input.empty())
	{
		std::cerr << ERR_EMPTY << "\n";
		return false;
	}

	for (size_t i = 0; i < input.length(); ++i)
	{
		if (!isprint(input[i]))
		{
			std::cerr << ERR_NON_PRINT << "\n";
			return false;
		}
	}

	return true;
}

ScalarConverter::e_type ScalarConverter::getType(const std::string& input)
{
	if (input.length() == 1 && !isdigit(input[0]))
		return CHAR;

	else if (input.find(".") == std::string::npos
			&& input.find("inf") == std::string::npos
			&& input.find("nan") == std::string::npos)
		return (validateInt(input) ? INT : INVALID);

	else if (input[input.length() - 1] == 'f'
			&& input != "-inf"
			&& input != "+inf")
		return (validateFloat(input) ? FLOAT : INVALID);

	else
		return (validateDouble(input) ? DOUBLE : INVALID);
}

bool ScalarConverter::validateInt(const std::string& input)
{
	if (input.find_first_not_of("+-0123456789") != std::string::npos)
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	char *endptr = NULL;
	double value = std::strtod(input.c_str(), &endptr);

	if ((endptr && *endptr))
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	if (value == HUGE_VAL || value == -HUGE_VAL
		|| value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
	{
		std::cerr << ERR_RANGE << "\n";
		return false;
	}

	return true;
}

bool ScalarConverter::validateFloat(const std::string& input)
{
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return true;

	if (input.find_first_not_of("+-0123456789.fe") != std::string::npos
		|| input.find_first_of("f") != input.find_last_of("f"))
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	char *endptr = NULL;
	double value = std::strtod(input.c_str(), &endptr);

	if ((endptr && *endptr != 'f') || !isdigit(*(endptr - 1)))
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	float f = static_cast<float>(value);
	if (!std::isfinite(f))
	{
		std::cerr << ERR_RANGE << "\n";
		return false;
	}

	return true;
}

bool ScalarConverter::validateDouble(const std::string& input)
{
	if (input == "-inf" || input == "+inf" || input == "nan")
		return true;

	if (input.find_first_not_of("+-0123456789.e") != std::string::npos)
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	char *endptr = NULL;
	double value = std::strtod(input.c_str(), &endptr);

	if ((endptr && *endptr) || !isdigit(*(endptr - 1)))
	{
		std::cerr << ERR_FORMAT << "\n";
		return false;
	}

	if (value == HUGE_VAL || value == -HUGE_VAL)
	{
		std::cerr << ERR_RANGE << "\n";
		return false;
	}

	return true;
}
