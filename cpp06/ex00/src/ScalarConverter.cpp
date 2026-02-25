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
	std::cout << "\nInput: '" << input << "'\n";

	if (!validateGeneral(input))
		return;

	const std::string trimmedInput = trim(input);
	const std::string lowerInput = lower(trimmedInput);
	std::cout << std::fixed << std::setprecision(1);

	e_type type = getType(lowerInput);
	switch (type)
	{
		case CHAR:
			convertChar(trimmedInput);
			break;

		case INT:
			convertInt(lowerInput);
			break;

		case FLOAT:
			convertFloat(lowerInput);
			break;

		case DOUBLE:
			convertDouble(lowerInput);
			break;

		default:
			break;
	}
}

// Trims spaces in beginning and end
std::string ScalarConverter::trim(const std::string& raw)
{
	size_t start = 0;
	size_t end = raw.length() - 1;

	while (raw[start] == ' ' && start < raw.length() - 1)
		start++;

	while (raw[end] == ' ' && end > start)
		end--;

	size_t len = end - start + 1;

	if (start != 0 || end != raw.length() - 1)
		return raw.substr(start, len);

	return raw;
}

std::string ScalarConverter::lower(const std::string& raw)
{
	std::string processed = raw;

	for (size_t i = 0; i < raw.length(); ++i)
		processed[i] = tolower(raw[i]);

	return processed;
}
