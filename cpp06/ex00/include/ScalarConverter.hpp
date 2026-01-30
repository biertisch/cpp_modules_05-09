#pragma once

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <string>

#define ERR_EMPTY "Invalid input: empty string"
#define ERR_NON_PRINT "Invalid input: non-printable characters"
#define ERR_FORMAT "Invalid input: invalid format"
#define ERR_RANGE "Invalid input: value out of range"

class ScalarConverter
{
	private:
		enum e_type
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};

		// Class is not instantiable
		ScalarConverter();
		ScalarConverter(const ScalarConverter&);
		~ScalarConverter();
		ScalarConverter& operator=(const ScalarConverter&);

		// Helpers
		// String manipulation
		static std::string trim(const std::string& raw);
		static std::string lower(const std::string& raw);

		// Input validation
		static bool validateGeneral(const std::string& input);
		static e_type getType(const std::string& input);
		static bool validateInt(const std::string& input);
		static bool validateFloat(const std::string& input);
		static bool validateDouble(const std::string& input);

		// Type casting
		static void convertChar(const std::string& input);
		static void convertInt(const std::string& input);
		static void convertFloat(const std::string& input);
		static void convertDouble(const std::string& input);
		static void convertPseudo(const std::string& input);

	public:
		static void convert(const std::string& input);
};
