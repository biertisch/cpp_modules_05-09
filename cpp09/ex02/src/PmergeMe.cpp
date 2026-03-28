#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorTimer(0), _dequeTimer(0) {}

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
	mergeInsertionSort(_deque);
	_dequeTimer = getTime() - start;

	// Validate sorting
	if (_vector.size() != inputSize
		|| _deque.size() != inputSize
		|| !isSorted(_vector)
		|| !isSorted(_deque)
	)
	{
		throw std::runtime_error("failed to sort input");
	}
	
	printSequence("After");
	printTimers();
}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_vector(other._vector),
	_deque(other._deque),
	_vectorTimer(other._vectorTimer),
	_dequeTimer(other._dequeTimer) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
		_vectorTimer = other._vectorTimer;
		_dequeTimer = other._dequeTimer;
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
		_deque.push_back(n);
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

	Vector sorted;
	sorted.reserve(vector.size());
	// Group largest of each pair
	for(size_t i = 0; i < pairs.size(); ++i)
		sorted.push_back(pairs[i].first);

	// Recursively sort largest
	mergeInsertionSort(sorted);

	// Reconstitute link between pairs
	pairs = reorderPairs(sorted, pairs);

	// Insert smallest from first pair
	sorted.insert(sorted.begin(), pairs[0].second);
	pairs.erase(pairs.begin());

	// Insert remaining following Jacobsthal sequence and binary search
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
	{
		if (vector[i] > vector[i + 1])
			pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
		else
			pairs.push_back(std::make_pair(vector[i + 1], vector[i]));
	}
	return pairs;
}

PmergeMe::PairVector PmergeMe::reorderPairs(const Vector& largest, const PairVector& pairs)
{
	PairVector reorderedPairs;
	reorderedPairs.reserve(pairs.size());

	for (size_t i = 0; i < largest.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == largest[i])
			{
				reorderedPairs.push_back(pairs[j]);
				break;
			}
		}
	}

	return reorderedPairs;
}

void PmergeMe::insertRemaining(Vector& sorted, const PairVector& pairs) const
{
	int start = 0;
	int size = 2;
	int subgroup = 0;
	int total = static_cast<int>(pairs.size());
	int inserted = 1;

	while (start < total)
	{
		int end = std::min(start + size, total) - 1;
		for (int i = end; i >= start; --i)
		{
			// Insert using binary search
			size_t bound = i + inserted + 1;
			size_t index = findInsertPosition(sorted, pairs[i].second, bound);
			sorted.insert(sorted.begin() + index, pairs[i].second);
			++inserted;
		}
		start += size;
		++subgroup;
		size = (1 << (subgroup + 1)) - size; // g(n) = 2^(n+1) - g(n-1)
		// Jacobstahl sequence: 2, 2, 6, 10, 22, 42, ...
	}
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

// SORTING STD::DEQUE
void PmergeMe::mergeInsertionSort(Deque& deque)
{
	if (deque.size() <= 1)
		return;

	// Group pairs
	PairDeque pairs = groupPairs(deque);

	Deque sorted;
	// Group largest of each pair
	for(size_t i = 0; i < pairs.size(); ++i)
		sorted.push_back(pairs[i].first);

	// Recursively sort largest
	mergeInsertionSort(sorted);

	// Reconstitute link between pairs
	pairs = reorderPairs(sorted, pairs);

	// Insert smallest from first pair
	sorted.insert(sorted.begin(), pairs[0].second);
	pairs.erase(pairs.begin());

	// Insert remaining following Jacobsthal sequence and binary search
	insertRemaining(sorted, pairs);

	// Handle straggler from odd-sized input
	handleStraggler(deque, sorted);

	deque.swap(sorted);
}

PmergeMe::PairDeque PmergeMe::groupPairs(const Deque& deque) const
{
	PairDeque pairs;

	for (size_t i = 0; i < deque.size() - 1; i += 2)
	{
		if (deque[i] > deque[i + 1])
			pairs.push_back(std::make_pair(deque[i], deque[i + 1]));
		else
			pairs.push_back(std::make_pair(deque[i + 1], deque[i]));
	}
	return pairs;
}

PmergeMe::PairDeque PmergeMe::reorderPairs(const Deque& largest, const PairDeque& pairs)
{
	PairDeque reorderedPairs;

	for (size_t i = 0; i < largest.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == largest[i])
			{
				reorderedPairs.push_back(pairs[j]);
				break;
			}
		}
	}

	return reorderedPairs;
}

void PmergeMe::insertRemaining(Deque& sorted, const PairDeque& pairs) const
{
	int start = 0;
	int size = 2;
	int subgroup = 0;
	int total = static_cast<int>(pairs.size());
	int inserted = 1;

	while (start < total)
	{
		int end = std::min(start + size, total) - 1;
		for (int i = end; i >= start; --i)
		{
			// Insert using binary search
			size_t bound = i + inserted + 1;
			size_t index = findInsertPosition(sorted, pairs[i].second, bound);
			sorted.insert(sorted.begin() + index, pairs[i].second);
			++inserted;
		}
		start += size;
		++subgroup;
		size = (1 << (subgroup + 1)) - size; // g(n) = 2^(n+1) - g(n-1)
		// Jacobstahl sequence: 2, 2, 6, 10, 22, 42, ...
	}
}

size_t PmergeMe::findInsertPosition(const Deque& deque, unsigned int value, size_t right) const
{
	size_t left = 0;

	while (left < right)
	{
		size_t mid = (left + right) / 2;
		if (value < deque[mid])
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

void PmergeMe::handleStraggler(const Deque& deque, Deque& sorted) const
{
	if (deque.size() % 2 == 0)
		return;

	size_t index = findInsertPosition(sorted, deque.back(), sorted.size());
	sorted.insert(sorted.begin() + index, deque.back());
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
		<< _deque.size()
		<< " elements with std::deque: "
		<< _dequeTimer
		<< " μs\n";
}
