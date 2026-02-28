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
	public:
		PmergeMe();
		PmergeMe(int ac, char** argv);
		PmergeMe(const PmergeMe& other);
		~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);

		typedef std::vector<unsigned int> Vector;
		typedef std::list<unsigned int> List;
		typedef std::vector<std::pair<unsigned int, unsigned int> > PairVector;
		typedef std::list<std::pair<unsigned int, unsigned int> > PairList;
		typedef std::list<unsigned int>::iterator Iter;
		typedef std::list<unsigned int>::const_iterator ConstIter;
		typedef std::list<std::pair<unsigned int, unsigned int> >::iterator PairIter;
		typedef std::list<std::pair<unsigned int, unsigned int> >::const_iterator ConstPairIter;


	private:
		Vector _vector;
		List _list;
		long long _vectorTimer;
		long long _listTimer;

		// Parsing
		void parseInput(int ac, char** argv);
		unsigned int parseNumber(const std::string& arg) const;

		// Sorting std::vector
		void mergeInsertionSort(Vector& vector);
		PairVector groupPairs(const Vector& vector) const;
		Vector groupLargest(const PairVector& pairs) const;
		void insertSmallestPair(Vector& sorted, PairVector& pairs) const;
		void insertRemaining(Vector& sorted, const PairVector& pairs) const;
		size_t getInsertBound(const Vector& vector, unsigned int value) const;
		size_t findInsertPosition(const Vector& list, unsigned int value, size_t right) const;
		void handleStraggler(const Vector& vector, Vector& sorted) const;

		// Sorting std::list
		void mergeInsertionSort(std::list<unsigned int>& list);
		PairList groupPairs(const List& list) const;
		List groupLargest(const PairList& pairs) const;
		void insertSmallestPair(List& sorted, PairList& pairs) const;
		void insertRemaining(List& sorted, const PairList& pairs) const;
		Iter findInsertPosition(List& list, unsigned int value) const;
		void handleStraggler(const List& list, List& sorted) const;

		template <typename T>
		bool isSorted(T& container) const
		{
			return (std::adjacent_find(
					container.begin(),
					container.end(),
					std::greater<typename T::value_type>())
				== container.end());
		}

		// Utils
		long long getTime() const;
		void printSequence(const std::string& description) const;
		void printTimers() const;
};
