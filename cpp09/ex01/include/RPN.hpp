#pragma once

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

class RPN
{
	private:
		std::stack<double> _stack;

		bool isOperator(char c) const;
		void executeOperation(char c);

	public:
		RPN();
		RPN(const RPN& other);
		~RPN();
		RPN& operator=(const RPN& other);
		double calculate(const std::string& input);
};
