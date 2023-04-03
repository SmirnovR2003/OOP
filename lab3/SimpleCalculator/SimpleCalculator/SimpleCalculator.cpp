#include "SimpleCalculator.h"
#include <stdexcept>
#include <queue>

using namespace std;

SimpleCalculator::SimpleCalculator()
:variables{}
,functions{}
{
}

SimpleCalculator::~SimpleCalculator()
{
}

bool SimpleCalculator::CreateVariable(string name)
{
	if (variables.count(name) == 1 || functions.count(name) == 1)
	{
		throw new invalid_argument("This name already exist");
		return false;
	}
	else
	{
		variables[name].value = NAN;
		variables[name].dependensies = {};
		return true;
	}
}

bool SimpleCalculator::SetVariableValue(string name, double value)
{
	if (functions.contains(name))
	{
		throw new invalid_argument("This name already is function name");
		return false;
	}
	else
	{
		if (variables[name].value = value)
		{
			SetRelevantFunctionsValues(name);
			return true;
		}
	}
	return false;
}

bool SimpleCalculator::SetVariableValue(std::string name, std::string identifier)
{
	if (functions.count(name) == 1)
	{
		throw new invalid_argument("This name already is function name");
		return false;
	}
	else
	{
		try
		{
			ObjectType identifierType = DefineIdentifierType(identifier);

			identifierType == ObjectType::var
				? variables[name].value = variables.find(identifier)->second.value
				: variables[name].value = functions.find(identifier)->second.value;

			SetRelevantFunctionsValues(name);
			return true;
		}
		catch (invalid_argument ex)
		{
			throw ex;
			return false;
		}
	}
	return false;
}

bool SimpleCalculator::CreateFunction(string name, string identifier)
{
	if (variables.count(name) == 1 || functions.count(name) == 1)
	{
		throw new invalid_argument("This name already exist");
		return false;
	}

	try
	{
		ObjectType identifierType = DefineIdentifierType(identifier);
		functions[name] = CreateFunctionStruct
		(
			{ identifier , identifierType },
			{ "" , ObjectType::nothing },
			Operations::nothing
		);

		if (identifierType == ObjectType::var)
		{
			variables[identifier].dependensies.push_back(name);
		}
		else
		{
			functions[identifier].dependensies.push_back(name);
		}
		return true;
	}
	catch (invalid_argument ex)
	{
		throw ex;
		return false;
	}
}

bool SimpleCalculator::CreateFunction(string name, string identifier1, string identifier2, Operations operation)
{
	if (variables.count(name) == 1 || functions.count(name) == 1)
	{
		throw new invalid_argument("This name already exist");
		return false;
	}
	if (operation == Operations::nothing)
	{
		throw new invalid_argument("operation can`t be 'nothing'");
		return false;
	}

	try
	{
		ObjectType identifierType1 = DefineIdentifierType(identifier1);
		ObjectType identifierType2 = DefineIdentifierType(identifier2);
		functions[name] = CreateFunctionStruct
		(
			{ identifier1 , identifierType1 },
			{ identifier2 , identifierType2 },
			operation
		);

		UpdateDependensies(name, identifier1, identifierType1);
		UpdateDependensies(name, identifier2, identifierType2);

		return true;
	}
	catch (invalid_argument ex)
	{
		throw ex;
		return false;
	}
}

map<string, double> SimpleCalculator::GetAllVariables()
{
	map<string, double> vars{};

	for (auto &variable : variables)
	{
		vars[variable.first] = variable.second.value;
	}

	return vars;
}

map<string, double> SimpleCalculator::GetAllFunctions()
{
	map<string, double> funcs{};

	for (auto& function : functions)
	{
		funcs[function.first] = function.second.value;
	}

	return funcs;
}

pair<string, double> SimpleCalculator::GetVariable(string name)
{
	pair<string, double> variable;
	variable.first = name;
	if (variables.count(name) == 0)
	{
		throw new invalid_argument("variable not exist");
		return pair<string, double>();
	}
	variable.second = variables.find(name)->second.value;
	return variable;
}

pair<string, double> SimpleCalculator::GetFunction(string name)
{
	pair<string, double> function;
	function.first = name;
	if (functions.count(name) == 0)
	{
		throw new invalid_argument("function not exist");
		return pair<string, double>();
	}
	function.second = functions.find(name)->second.value;
	return function;
}

void SimpleCalculator::SetRelevantFunctionsValues(std::string variableName)
{
	queue<string> q{};
	for (const auto& funcName : variables[variableName].dependensies)
	{
		q.push(funcName);
	}

	while (!q.empty())
	{
		string funcName = q.front();
		q.pop();

		if (functions.count(funcName) == 1)
		{
			Func func = functions.find(funcName)->second;

			for (const auto& dependenseName : func.dependensies)
			{
				q.push(dependenseName);
			}

			double num1, num2;

			(func.dep1.second == ObjectType::var)
				? num1 = variables.find(func.dep1.first)->second.value
				: num1 = functions.find(func.dep1.first)->second.value;

			if (func.oper == Operations::nothing)
			{
				func.value = num1;
			}
			else
			{
				(func.dep2.second == ObjectType::var)
					? num2 = variables.find(func.dep2.first)->second.value
					: num2 = functions.find(func.dep2.first)->second.value;

				functions[funcName].value = CalculateFunctionValue(num1, num2, func.oper);
			}
		}
	}
}

SimpleCalculator::Func SimpleCalculator::CreateFunctionStruct(pair<std::string, ObjectType> dep1, pair<std::string, ObjectType> dep2, Operations oper)
{
	try
	{
		double value1 = NAN, value2 = NAN;
		value1 = CalculateFirstFunctionValue(dep1);
		if (dep2.second != ObjectType::nothing)
		{
			value2 = CalculateSecondFunctionValue(dep2);
		}
		return
		{ 
			dep2.second != ObjectType::nothing ?
				CalculateFunctionValue(value1, value2,  oper) : 
				value1 ,
			dep1 , 
			dep2 , 
			{} , 
			oper 
		};
	}
	catch(invalid_argument ex)
	{
		throw ex;
		return Func();
	}
}

double SimpleCalculator::CalculateFunctionValue(double value1, double value2, Operations oper)
{
	if (value1 == NAN || value2 == NAN)
	{
		return NAN;
	}
	switch (oper)
	{
	case Operations::sum:
	{
		return value1 + value2;
	}
	case Operations::sub:
	{
		return value1 - value2;
	}
	case Operations::div:
	{
		return value1 / value2;
	}
	case Operations::mult:
	{
		return value1 * value2;
	}
	default:
	{
		return NAN;
	}
	}
}

double SimpleCalculator::CalculateFirstFunctionValue(pair<string, ObjectType> dep1)
{
	double value1 = NAN;
	if (dep1.second == ObjectType::var)
	{
		if (!(value1 = variables.find(dep1.first)->second.value))
		{
			throw new invalid_argument("first identifier must de declarated");
		}
	}
	else if (dep1.second == ObjectType::func)
	{
		if (!(value1 = functions.find(dep1.first)->second.value))
		{
			throw new invalid_argument("first identifier must de declarated");
		}
	}
	else
	{
		throw new invalid_argument("first identifier must de declarated");
	}
	return value1;
}

double SimpleCalculator::CalculateSecondFunctionValue(pair<string, ObjectType> dep2)
{
	double value2 = NAN;
	if (dep2.second == ObjectType::var)
	{
		if (!(value2 = variables.find(dep2.first)->second.value))
		{
			throw new invalid_argument("second identifier must de declarated");
		}
	}
	else if (dep2.second == ObjectType::func)
	{
		if (!(value2 = functions.find(dep2.first)->second.value))
		{
			throw new invalid_argument("second identifier must de declarated");
		}
	}
	return value2;
}

ObjectType SimpleCalculator::DefineIdentifierType(string identifier)
{
	ObjectType identifierType = ObjectType::nothing;
	if (variables.count(identifier) == 1)
	{
		identifierType = ObjectType::var;
	}
	else if (functions.count(identifier) == 1)
	{
		identifierType = ObjectType::func;
	}
	else
	{
		throw new invalid_argument("identifier not exist");
		return ObjectType();
	}
	return identifierType;
}

void SimpleCalculator::UpdateDependensies(std::string funcName, std::string identifier, ObjectType identifierType)
{
	if (identifierType == ObjectType::var)
	{
		variables[identifier].dependensies.push_back(funcName);
	}
	else
	{
		functions[identifier].dependensies.push_back(funcName);
	}
}
