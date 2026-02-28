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

template <typename T, typename U>
void groupPairs(const T& container, U& pairContainer)
{
	typedef typename T::const_iterator Iter;
	Iter it = container.begin();

	while (it != container.end())
	{
		Iter next = it;
		++next;
		if (next != container.end())
		{
			pairContainer.push_back(std::make_pair(
				std::max(*it, *next),
				std::min(*it, *next)
			));
		}
		++it;
		if (it != container.end())
			++it;
	}
}

template <typename T>
bool isSorted(T& container)
{
	return (std::adjacent_find(
			container.begin(),
			container.end(),
			std::greater<typename T::value_type>())
		== container.end());
}

void PmergeMe::mergeInsertionSort(std::list<unsigned int>& list)
{
	(void)list;
}

void PmergeMe::mergeInsertionSort(std::vector<unsigned int>& vector)
{
	if (vector.size() <= 1)
		return;

	std::vector<std::pair<unsigned int, unsigned int> > pairs;
	groupPairs(vector, pairs);

	// for (size_t i = 0; i < vector.size() - 1; i += 2)
	// 	pairs.push_back(std::make_pair(
	// 			std::max(vector[i], vector[i + 1]),
	// 			std::min(vector[i], vector[i + 1])
	// 		));

	// Refactor to template
	// Group largest of each pair
	std::vector<unsigned int> sorted;
	sorted.reserve(pairs.size() + 1);
	for(size_t i = 0; i < pairs.size(); ++i)
		sorted.push_back(pairs[i].first);

	// Recursively sort largest of each pair
	mergeInsertionSort(sorted);

	// Refactor to template
	// Insert pair of smallest element at the start
	sorted.reserve(vector.size());
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (sorted[0] == pairs[i].first)
		{
			sorted.insert(sorted.begin(), pairs[i].second);
			pairs.erase(pairs.begin() + i);
			break;
		}
	}

	// Refactor to separate function?
	// Insert remaining elements following Jacobsthal sequence
	// 2, 2, 6, 10, 22, 42, ...
	int start = 0;
	int size = 2;
	int subgroup = 0;
	int total = static_cast<int>(pairs.size());
	while (start < total)
	{
		int end = std::min(start + size, total) - 1;
		for (int i = end; i >= start; --i)
		{
			// Refactor to template
			size_t bound = 0;
			while (bound < sorted.size() && sorted[bound] != pairs[i].first)
				++bound;
			// Insert using binary search
			size_t index = findInsertIndex(sorted, pairs[i].second, bound);
			sorted.insert(sorted.begin() + index, pairs[i].second);
		}
		start += size;
		++subgroup;
		size = (1 << (subgroup + 1)) - size; // g(n) = 2^(n+1) - g(n-1)
	}

	// Handle straggler
	if (vector.size() % 2 != 0)
	{
		size_t index = findInsertIndex(sorted, vector.back(), sorted.size());
		sorted.insert(sorted.begin() + index, vector.back());
	}

	// Validate sorting
	if (sorted.size() != vector.size() || !isSorted(sorted))
		throw std::runtime_error("failed to sort input");

	vector.swap(sorted);
}

size_t PmergeMe::findInsertIndex(const std::vector<unsigned int>& vector, unsigned int value, size_t right) const
{
	size_t left = 0;

	while (left < right)
	{
		size_t mid = (left + right) / 2;
		if (value < vector[mid])
			right = mid;
		else
			left = mid + 1;
	}
	return left;
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
