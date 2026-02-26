#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _listTimer(0), _vectorTimer(0) {}

PmergeMe::PmergeMe(int ac, char** argv)
{
	parseInput(ac, argv);

	printSequence("Before");

	long long start = getTime();
	mergeInsertionSort(_list);
	_listTimer = getTime() - start;

	start = getTime();
	mergeInsertionSort(_vector);
	_vectorTimer = getTime() - start;

	if (!isSorted(_list) || !isSorted(_vector))
		throw std::runtime_error("failed to sort input");

	printSequence("After");
	printTimers();
}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_list(other._list),
	_vector(other._vector),
	_listTimer(other._listTimer),
	_vectorTimer(other._vectorTimer) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_list = other._list;
		_vector = other._vector;
		_listTimer = other._listTimer;
		_vectorTimer = other._vectorTimer;
	}
	return *this;
}

void PmergeMe::parseInput(int ac, char** argv)
{
	if (ac < 1)
		throw std::invalid_argument("invalid number of arguments");

	for (int i = 0; i < ac && argv[i]; ++i)
	{
		unsigned int n = parseNumber(argv[i]);
		_list.push_back(n);
		_vector.push_back(n);
	}

	std::set<unsigned int> seen;
	for (size_t i = 0; i < _vector.size(); ++i)
		if (!seen.insert(_vector[i]).second)
			throw std::runtime_error("duplicate element found");
}

unsigned int PmergeMe::parseNumber(const std::string& arg) const
{
	if (arg.empty())
		throw std::invalid_argument("empty argument");

	char* endptr = NULL;
	long n = std::strtol(arg.c_str(), &endptr, 10);
	if (endptr && *endptr)
		throw std::invalid_argument("invalid argument");

	if (n < 0 || n > std::numeric_limits<unsigned int>::max())
		throw std::invalid_argument("number out of range");

	return static_cast<unsigned int>(n);
}

void PmergeMe::mergeInsertionSort(std::list<unsigned int>& list)
{
	(void)list;
}

void PmergeMe::mergeInsertionSort(std::vector<unsigned int>& vector)
{
	if (vector.size() <= 1)
		return;

	// Group in pairs
	std::vector<std::pair<unsigned int, unsigned int>> pairs;
	for (size_t i = 0; i < vector.size() - 1; i += 2)
		pairs.push_back({
			std::max(vector[i], vector[i + 1]),
			std::min(vector[i], vector[i + 1])
		});

	// Group largest element of each pair
	std::vector<unsigned int> sorted, uninserted;
	for(size_t i = 0; i < pairs.size(); ++i)
	{
		sorted.push_back(pairs[i].first);
		uninserted.push_back(pairs[i].second);
	}
	if (vector.size() % 2 != 0)
		uninserted.push_back(vector.back());

	// Recursively sort subgroup
	mergeInsertionSort(sorted);

	// Insert at the start pair of the smallest element
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (sorted[0] == pairs[i].first)
		{
			sorted.insert(sorted.begin(), pairs[i].second);
			uninserted.erase(uninserted.begin() + i);
			break;
		}
	}

	// Jacobsthal partition

	// Insertion using binary search
}

long long PmergeMe::getTime() const
{
	struct timeval now;
	if (gettimeofday(&now, NULL) == -1)
		throw std::runtime_error("failed to get time");
	return (now.tv_sec * 1000000LL + now.tv_usec);
}

void PmergeMe::printSequence(const std::string& description) const
{
	std::cout << description << ":\t";
	for (size_t i = 0; i < _vector.size(); ++i)
	{
		std::cout << _vector[i];
		if (i < _vector.size() - 1)
			std::cout << " ";
	}
	std::cout << "\n";
}

void PmergeMe::printTimers() const
{
	std::cout
		<< "Time to process a range of "
		<< _list.size()
		<< " elements with std::list: "
		<< _listTimer
		<< " μs\n";

	std::cout
		<< "Time to process a range of "
		<< _vector.size()
		<< " elements with std::vector: "
		<< _vectorTimer
		<< " μs\n";
}
