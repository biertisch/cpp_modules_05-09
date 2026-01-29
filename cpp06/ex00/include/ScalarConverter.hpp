#pragma once

#include <cctype>
#include <iostream>
#include <string>

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
		static bool validateGeneral(const std::string& input);
		static e_type getType(const std::string& input);

	public:
		static void convert(const std::string& input);
};
