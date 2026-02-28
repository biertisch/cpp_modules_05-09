#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorTimer(0), _listTimer(0) {}

PmergeMe::PmergeMe(int ac, char** argv)
{
	parseInput(ac, argv);
	size_t inputSize = _vector.size();
	printSequence("Before");

	// Sort with timer
	long long start = getTime();
	mergeInsertionSort(_vector);
	_vectorTimer = getTime() - start;

	start = getTime();
	mergeInsertionSort(_list);
	_listTimer = getTime() - start;

	// Validate sorting
	if (_vector.size() != inputSize
		|| _list.size() != inputSize
		|| !isSorted(_vector)
		|| !isSorted(_list)
	)
		throw std::runtime_error("failed to sort input");

	printSequence("After");
	printTimers();
}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_vector(other._vector),
	_list(other._list),
	_vectorTimer(other._vectorTimer),
	_listTimer(other._listTimer) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_list = other._list;
		_vectorTimer = other._vectorTimer;
		_listTimer = other._listTimer;
	}
	return *this;
}

// PARSING

void PmergeMe::parseInput(int ac, char** argv)
{
	if (ac < 1)
		throw std::invalid_argument("invalid number of arguments");

	for (int i = 0; i < ac && argv[i]; ++i)
	{
		unsigned int n = parseNumber(argv[i]);
		_vector.push_back(n);
		_list.push_back(n);
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

// SORTING STD::VECTOR

void PmergeMe::mergeInsertionSort(Vector& vector)
{
	if (vector.size() <= 1)
		return;

	// Group pairs
	PairVector pairs = groupPairs(vector);

	// Group largest of each pair
	Vector sorted = groupLargest(pairs);

	// Recursively sort largest of each pair
	mergeInsertionSort(sorted);

	// Insert pair of smallest element at the start
	insertSmallestPair(sorted, pairs);

	// Insert remaining elements following Jacobsthal sequence and binary search
	sorted.reserve(vector.size());
	insertRemaining(sorted, pairs);

	// Handle straggler from odd-sized input
	handleStraggler(vector, sorted);

	vector.swap(sorted);
}

PmergeMe::PairVector PmergeMe::groupPairs(const Vector& vector) const
{
	PairVector pairs;
	pairs.reserve(vector.size() / 2);

	for (size_t i = 0; i < vector.size() - 1; i += 2)
		pairs.push_back(std::make_pair(
				std::max(vector[i], vector[i + 1]),
				std::min(vector[i], vector[i + 1])
			));

	return pairs;
}

PmergeMe::Vector PmergeMe::groupLargest(const PairVector& pairs) const
{
	Vector largest;
	largest.reserve(pairs.size() + 1);

	for(size_t i = 0; i < pairs.size(); ++i)
		largest.push_back(pairs[i].first);

	return largest;
}

void PmergeMe::insertSmallestPair(Vector& sorted, PairVector& pairs) const
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (sorted[0] == pairs[i].first)
		{
			sorted.insert(sorted.begin(), pairs[i].second);
			pairs.erase(pairs.begin() + i);
			break;
		}
	}
}

void PmergeMe::insertRemaining(Vector& sorted, const PairVector& pairs) const
{
	int start = 0;
	int size = 2;
	int subgroup = 0;
	int total = static_cast<int>(pairs.size());
	while (start < total)
	{
		int end = std::min(start + size, total) - 1;
		for (int i = end; i >= start; --i)
		{
			size_t bound = getInsertBound(sorted, pairs[i].first);
			// Insert using binary search
			size_t index = findInsertPosition(sorted, pairs[i].second, bound);
			sorted.insert(sorted.begin() + index, pairs[i].second);
		}
		start += size;
		++subgroup;
		size = (1 << (subgroup + 1)) - size; // g(n) = 2^(n+1) - g(n-1)
	}
}

size_t PmergeMe::getInsertBound(const Vector& vector, unsigned int value) const
{
	size_t bound = 0;
	while (bound < vector.size() && vector[bound] != value)
		++bound;
	return bound;
}

size_t PmergeMe::findInsertPosition(const Vector& vector, unsigned int value, size_t right) const
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

void PmergeMe::handleStraggler(const Vector& vector, Vector& sorted) const
{
	if (vector.size() % 2 == 0)
		return;

	size_t index = findInsertPosition(sorted, vector.back(), sorted.size());
	sorted.insert(sorted.begin() + index, vector.back());
}

// SORTING STD::LIST

void PmergeMe::mergeInsertionSort(std::list<unsigned int>& list)
{
	if (list.size() <= 1)
		return;

	// Group pairs
	PairList pairs = groupPairs(list);

	// Group largest of each pair
	List sorted = groupLargest(pairs);

	// Recursively sort largest of each pair
	mergeInsertionSort(sorted);

	// Insert pair of smallest element at the start
	insertSmallestPair(sorted, pairs);

	// Insert remaining elements following Jacobsthal sequence and linear search
	insertRemaining(sorted, pairs);

	// Handle straggler from odd-sized input
	handleStraggler(list, sorted);

	list.swap(sorted);
}

PmergeMe::PairList PmergeMe::groupPairs(const List& list) const
{
	PairList pairs;

	ConstIter it = list.begin();
	while (it != list.end())
	{
		ConstIter next = it;
		++next;
		if (next != list.end())
		{
			pairs.push_back(std::make_pair(
				std::max(*it, *next),
				std::min(*it, *next)
			));
		}
		++it;
		if (it != list.end())
			++it;
	}

	return pairs;
}

PmergeMe::List PmergeMe::groupLargest(const PairList& pairs) const
{
	List largest;

	for (ConstPairIter it = pairs.begin(); it != pairs.end(); ++it)
		largest.push_back(it->first);

	return largest;
}

void PmergeMe::insertSmallestPair(List& sorted, PairList& pairs) const
{
	for (PairIter it = pairs.begin(); it != pairs.end(); ++it)
	{
		if (it->first == sorted.front())
		{
			sorted.insert(sorted.begin(), it->second);
			pairs.erase(it);
			break;
		}
	}
}

void PmergeMe::insertRemaining(List& sorted, const PairList& pairs) const
{
	ConstPairIter start = pairs.begin();
	int size = 2;
	int subgroup = 0;

	while (start != pairs.end())
	{
		ConstPairIter end = start;
		for (int i = 0; i < size && end != pairs.end(); ++i)
			++end;

		ConstPairIter it = end;
		while (it != start)
		{
			--it;
			Iter pos = findInsertPosition(sorted, it->second);
			sorted.insert(pos, it->second);
		}

		for (int i = 0; i < size && start != pairs.end(); ++i)
			++start;
		++subgroup;
		size = (1 << (subgroup + 1)) - size; // g(n) = 2^(n+1) - g(n-1)
	}
}

PmergeMe::Iter PmergeMe::findInsertPosition(List& list, unsigned int value) const
{
	Iter it = list.begin();
	while (it != list.end() && *it < value)
		++it;
	return it;
}

void PmergeMe::handleStraggler(const List& list, List& sorted) const
{
	if (list.size() % 2 == 0)
		return;

	Iter it = findInsertPosition(sorted, list.back());
	sorted.insert(it, list.back());
}

// UTILS

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
		<< _vector.size()
		<< " elements with std::vector: "
		<< _vectorTimer
		<< " μs\n";

	std::cout
		<< "Time to process a range of "
		<< _list.size()
		<< " elements with std::list:   "
		<< _listTimer
		<< " μs\n";
}
