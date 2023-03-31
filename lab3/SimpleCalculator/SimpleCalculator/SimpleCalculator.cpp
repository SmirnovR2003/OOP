#include "SimpleCalculator.h"

SimpleCalculator::SimpleCalculator()
{
}

SimpleCalculator::~SimpleCalculator()
{
}

bool SimpleCalculator::CreateVariable(std::string name, double num)
{
	return false;
}

bool SimpleCalculator::CreateFunction(std::string name, double num1, Operations oper, double num2)
{
	return false;
}

std::map<std::string, int> SimpleCalculator::GetAllVariables()
{
	return std::map<std::string, int>();
}

std::map<std::string, int> SimpleCalculator::GetAllFunctions()
{
	return std::map<std::string, int>();
}

std::pair<std::string, int> SimpleCalculator::GetVariableValue(std::string name)
{
	return std::pair<std::string, int>();
}

std::pair<std::string, int> SimpleCalculator::GetFunctionValue(std::string name)
{
	return std::pair<std::string, int>();
}
