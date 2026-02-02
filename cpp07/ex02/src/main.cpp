#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Array.hpp>

static void printSection(const std::string& title)
{
	int width = 60;
	int padding = (width - title.size()) / 2;
	if (padding < 1)
		padding = 0;

	std::cout << '\n' << std::string(width, '=')
		<< '\n' << std::string(padding, ' ') << title
		<< std::string(padding, ' ') << '\n'
		<< std::string(width, '=') << '\n';
}

int main()
{
	srand(time(NULL));
	std::cout << std::fixed << std::setprecision(1);

	try
	{
		printSection("CREATING ARRAYS");
		Array<int> empty_array;
		std::cout << empty_array << "\n\n";

		Array<int> zero_array(0);
		std::cout << zero_array << "\n\n";

		Array<int> int_array(10);
		for (unsigned int i = 0; i < int_array.size(); i++)
		{
			int_array[i] = rand() % 100;
		}
		std::cout << int_array << "\n\n";

		Array<double> double_array(7);
		for (unsigned int i = 0; i < double_array.size(); i++)
		{
			double_array[i] = rand() % 20;
		}
		std::cout << double_array << "\n\n";

		Array<std::string> string_array(3);
		string_array[0] = "apple";
		string_array[1] = "banana";
		string_array[2] = "cherry";
		std::cout << string_array << "\n\n";


		printSection("TESTING COPY CONSTRUCTOR & ASSIGNMENT");
		{
			Array<int>copy_construct(int_array);
			std::cout << copy_construct << "\n\n";

			Array<int>copy_assign;
			copy_assign = int_array;
			std::cout << copy_assign << "\n\n";

			std::cout << "After altering first element:\n";
			copy_construct[0] = 101;
			std::cout << "copy construct: " << copy_construct << '\n';

			copy_assign[0] = 102;
			std::cout << "copy assignment: " << copy_assign << "\n\n";

			std::cout << "Going out of scope...\n";
		}
		std::cout << "\nOriginal array: " << int_array << '\n';

		printSection("TESTING SUBSCRIPT ACCESS");
		try
		{
			std::cout << "string_array[0]: " << string_array[0] << '\n';
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		try
		{
			std::cout << "string_array[-2]: " << string_array[-2] << '\n';
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		try
		{
			std::cout << "string_array[3]: " << string_array[3] << '\n';
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
