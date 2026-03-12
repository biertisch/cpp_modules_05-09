#pragma once

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;

		void loadDatabase(const std::string& database);
		double findRate(const std::string& date) const;
		bool isValidValue(double value, char* endptr, const std::string& line) const;
		bool isValidDate(const std::string& date) const;
		int daysInMonth(int month, int year) const;
		bool isLeapYear(int year) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& database);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void processInput(const std::string& filename) const;
};
