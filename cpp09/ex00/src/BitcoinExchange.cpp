#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string& database)
{
	loadDatabase(database);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

void BitcoinExchange::loadDatabase(const std::string& database)
{
	std::ifstream file(database.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not load database.");

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = line.substr(0, comma);
		char *endptr = NULL;
		double rate = std::strtod(line.substr(comma + 1).c_str(), &endptr);
		if (!isValidDate(date) || (endptr && *endptr) || rate < 0)
			continue;

		_data[date] = rate;
	}

	file.close();
}

void BitcoinExchange::processInput(const std::string& filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(file, line);
	if (line != "date | value")
		throw std::runtime_error("Error: header should be 'date | value'.");

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t delimiter = line.find(" | ");
		if (delimiter == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << '\n';
			continue;
		}

		std::string date = line.substr(0, delimiter);
		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << line << '\n';
			continue;
		}

		char *endptr = NULL;
		double value = std::strtod(line.substr(delimiter + 2).c_str(), &endptr);
		if (!isValidValue(value, endptr, line))
			continue;

		try
		{
			double result = value * findRate(date);
			std::cout << date << " => " << value << " = " << result << "\n";
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << "\n";
		}
	}

	file.close();
}

double BitcoinExchange::findRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _data.lower_bound(date);

	if (it == _data.end() || it->first != date)
	{
		if (it == _data.begin())
			throw std::runtime_error("Error: date too early.");
		--it;
	}
	return it->second;
}

bool BitcoinExchange::isValidValue(double value, char* endptr, const std::string& line) const
{
	if (endptr && *endptr)
	{
		std::cout << "Error: bad input => " << line << '\n';
		return false;
	}

	if (value < 0 || value > 1000)
	{
		if (value < 0)
			std::cout << "Error: not a positive number.\n";
		else
			std::cout << "Error: too large a number.\n";
		return false;
	}

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return false;

	for (std::size_t i = 0; i < date.length(); ++i)
	{
		if ((i == 4 || i == 7) && date[i] != '-')
			return false;
		else if (i != 4 && i != 7 && !std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	return (year >= 0 && month >= 1 && month <= 12
		&& day >= 1 && day <= daysInMonth(month, year));
}

int BitcoinExchange::daysInMonth(int month, int year) const
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	if (month == 2)
		return (isLeapYear(year) ? 29 : 28);
	return 31;
}

bool BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
