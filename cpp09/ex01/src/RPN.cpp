#include "RPN.hpp"

RPN::RPN() : _stack() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

double RPN::calculate(const std::string& input)
{
	for (size_t i = 0; i < input.length(); ++i)
	{
		if (input[i] == ' ')
			continue;

		else if (std::isdigit(input[i]))
		{
			double value = std::atof(input.substr(i).c_str());
			if (value > 9)
				throw std::invalid_argument("operand too big (>9)");
			_stack.push(value);
		}

		else if (isOperator(input[i]))
			executeOperation(input[i]);

		else
			throw std::invalid_argument("invalid character");
	}

	if (_stack.size() != 1)
		throw std::invalid_argument("too many operands");
	return _stack.top();
}

bool RPN::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::executeOperation(char c)
{
	if (_stack.size() < 2)
		throw std::invalid_argument("too few operands");

	double b = _stack.top();
	_stack.pop();
	double a = _stack.top();
	_stack.pop();

	switch (c)
	{
		case '+':
			_stack.push(a + b);
			break;
		case '-':
			_stack.push(a - b);
			break;
		case '*':
			_stack.push(a * b);
			break;
		case '/':
			if (b == 0)
				throw std::runtime_error("attempt to divide by 0");
			_stack.push(a / b);
			break;
		default:
			break;
	}
}
