#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./RPN \"expression\"\n";
		return 1;
	}

	try
	{
		RPN calculator;
		std::cout << calculator.calculate(argv[1]) << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
