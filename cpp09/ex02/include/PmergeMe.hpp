#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <limits>
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
		typedef std::vector<std::pair<unsigned int, unsigned int> > PairVector;

		typedef std::deque<unsigned int> Deque;
		typedef std::deque<std::pair<unsigned int, unsigned int> > PairDeque;

	private:
		Vector _vector;
		Deque _deque;
		long long _vectorTimer;
		long long _dequeTimer;

		// Parsing
		void parseInput(int ac, char** argv);
		unsigned int parseNumber(const std::string& arg) const;

		// Sorting std::vector
		void mergeInsertionSort(Vector& vector);
		PairVector groupPairs(const Vector& vector) const;
		PairVector reorderPairs(const Vector& largest, const PairVector& pairs);
		void insertRemaining(Vector& sorted, const PairVector& pairs) const;
		size_t findInsertPosition(const Vector& list, unsigned int value, size_t right) const;
		void handleStraggler(const Vector& vector, Vector& sorted) const;

		// Sorting std::deque
		void mergeInsertionSort(Deque& deque);
		PairDeque groupPairs(const Deque& deque) const;
		PairDeque reorderPairs(const Deque& largest, const PairDeque& pairs);
		void insertRemaining(Deque& sorted, const PairDeque& pairs) const;
		size_t findInsertPosition(const Deque& list, unsigned int value, size_t right) const;
		void handleStraggler(const Deque& deque, Deque& sorted) const;

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
