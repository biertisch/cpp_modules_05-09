#include "ScalarConverter.hpp"

static void printSection(const std::string& title)
{
	int width = 50;
	int padding = (width - title.size()) / 2;
	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printSection("Type: Customizable");
		for (int i = 1; i < argc; i++)
			ScalarConverter::convert(argv[i]);
	}

	printSection("Type: Char");
	ScalarConverter::convert("A");
	ScalarConverter::convert("z");
	ScalarConverter::convert(" m ");
	ScalarConverter::convert(" ");
	ScalarConverter::convert("  ");
	ScalarConverter::convert("!");
	ScalarConverter::convert("\t"); // Invalid
	ScalarConverter::convert(""); // Invalid
	ScalarConverter::convert("string"); // Invalid


	printSection("Type: Int");
	ScalarConverter::convert("0");
	ScalarConverter::convert(" 66     ");
	ScalarConverter::convert("-2");
	ScalarConverter::convert("255");
	ScalarConverter::convert("2147483647"); // INT_MAX
	ScalarConverter::convert("-2147483648"); // INT_MIN
	ScalarConverter::convert("2147483648"); // Invalid
	ScalarConverter::convert("-2147483649"); // Invalid
	ScalarConverter::convert("-+31"); // Invalid
	ScalarConverter::convert("-31  78"); // Invalid

	printSection("Type: Float");
	ScalarConverter::convert("nanf");
	ScalarConverter::convert("-inff");
	ScalarConverter::convert("+inff");
	ScalarConverter::convert("  +INFF");
	ScalarConverter::convert("3.84f");
	ScalarConverter::convert("-28.5f");
	ScalarConverter::convert("72.3f");
	ScalarConverter::convert("3.4028235e38f"); // FLOAT_MAX
	ScalarConverter::convert("3.4028236e38f"); // Invalid
	ScalarConverter::convert("f-28.5f"); // Invalid
	ScalarConverter::convert("-28.5ff"); // Invalid

	printSection("Type: Double");
	ScalarConverter::convert("0.0");
	ScalarConverter::convert("98.2");
	ScalarConverter::convert("-36.7");
	ScalarConverter::convert("nan");
	ScalarConverter::convert("+inf");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("NAN");
	ScalarConverter::convert("-2147483649.3"); // below INT_MIN
	ScalarConverter::convert("3.4028236e38"); // over FLOAT_MAX
	ScalarConverter::convert("1.8e308"); // Invalid
	ScalarConverter::convert("12a.8"); // Invalid
	ScalarConverter::convert("12..8"); // Invalid
	ScalarConverter::convert("12.8.0"); // Invalid

	return 0;
}