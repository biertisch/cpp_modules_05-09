#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	try
	{
		PmergeMe sort(argc - 1, argv + 1);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}