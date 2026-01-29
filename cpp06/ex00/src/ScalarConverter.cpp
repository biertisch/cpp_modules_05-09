#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&)
{
	return *this;
}

void ScalarConverter::convert(const std::string& input)
{
	// step 0: initial validation (not empty, no non-printable chars)
	if (!validateGeneral(input))
	{
		// print error message
		return;
	}

	// maybe put every letter to lower case and trim spaces in beginning and end?

	// step 1: identify & validate type (char, int, float, double)
	// step 2: convert to type
	// step 3: explicitly convert to three other types (using static_cast)
}

// Checks if input is not empty and contains no non-printable chars
static bool validateGeneral(const std::string& input)
{
	if (input.empty())
		return false;

	for (size_t i = 0; i < input.length(); i++)
		if (!isprint(input[i])) // issue error warning?
			return false;

	return true;
}

static ScalarConverter::e_type getType(const std::string& input)
{
	if (input.length() == 1 && !isdigit(input[0]))
		return ScalarConverter::CHAR;

	else if (input.find(".") == std::string::npos
		&& input.find("inf") == std::string::npos
		&& input.find("nan") == std::string::npos)
	{
		// if validateInt
		return ScalarConverter::INT;

		// allows space, numeric chars, '+' and '-'
		// check limits


		// else return INVALID
	}

	else if (input.find("f") == input.length() - 1
		&& input != "-inf"
		&& input != "+inf")
	{
		// if validateFloat
		return ScalarConverter::FLOAT;
		// allows space, numeric chars, '+', '-', '.', 'f', '-inff','+inff', 'nanf'
		// last char must be 'f'
		// check limits

		// else return INVALID
	}

	// else if validate double
	// DOUBLE
	// allows space, numeric chars, '+', '-', '.', '-inf', '+inf', 'nan'

	else
		return ScalarConverter::INVALID;
}
