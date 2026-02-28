#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <set>
#include <stdexcept>
#include <string>
#include <sys/time.h>
#include <vector>
#include <utility>

class PmergeMe
{
	private:
		std::list<unsigned int> _list;
		std::vector<unsigned int> _vector;
		long long _listTimer;
		long long _vectorTimer;

		void parseInput(int ac, char** argv);
		unsigned int parseNumber(const std::string& arg) const;

		void mergeInsertionSort(std::list<unsigned int>& list);
		void mergeInsertionSort(std::vector<unsigned int>& vector);
		size_t findInsertIndex(const std::vector<unsigned int>& list, unsigned int value, size_t right) const;

		long long getTime() const;
		void printSequence(const std::string& description) const;
		void printTimers() const;

	public:
		PmergeMe();
		PmergeMe(int ac, char** argv);
		PmergeMe(const PmergeMe& other);
		~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);
};
