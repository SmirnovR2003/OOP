#include "SimpleCalculator.h"
#include <stdexcept>
#include <queue>

using namespace std;

SimpleCalculator::SimpleCalculator()
:m_variables{}
,m_functions{}
{
}

bool SimpleCalculator::CreateVariable(const string& name)
{
	if (m_variables.count(name) == 1 || m_functions.count(name) == 1)
	{
		throw invalid_argument("This name already exist");
		return false;
	}
	else
	{
		m_variables[name].value = nan("inf");
		m_variables[name].dependensies = {};
		return true;
	}
}

bool SimpleCalculator::SetVariableValue(const string& name, double value)
{
	if (m_functions.contains(name))
	{
		throw invalid_argument("This name already is function name");
		return false;
	}
	else
	{
		m_variables[name].value = value;
		SetRelevantFunctionsValues(name);
		return true;
		
	}
	return false;
}

bool SimpleCalculator::SetVariableValue(const string& name, const string& identifier)
{
	if (m_functions.count(name) == 1)
	{
		throw invalid_argument("This name already is function name");
		return false;
	}
	else
	{
		try
		{
			ObjectType identifierType = DefineIdentifierType(identifier);

			identifierType == ObjectType::var
				? m_variables[name].value = m_variables.find(identifier)->second.value
				: m_variables[name].value = m_functions.find(identifier)->second.value;

			SetRelevantFunctionsValues(name);
			return true;
		}
		catch (invalid_argument ex)
		{
			throw;
			return false;
		}
	}
	return false;
}

bool SimpleCalculator::CreateFunction(const string& name, const string& identifier)
{
	if (m_variables.count(name) == 1 || m_functions.count(name) == 1)
	{
		throw invalid_argument("This name already exist");
		return false;
	}

	try
	{
		ObjectType identifierType = DefineIdentifierType(identifier);
		m_functions[name] = CreateFunctionStruct
		(
			name,
			{ identifier , identifierType },
			{ "" , ObjectType::nothing },
			Operations::nothing
		);

		if (identifierType == ObjectType::var)
		{
			m_variables[identifier].dependensies.push_back(name);
		}
		else
		{
			m_functions[identifier].dependensies.push_back(name);
		}
		return true;
	}
	catch (invalid_argument ex)
	{
		throw;
		return false;
	}
}

bool SimpleCalculator::CreateFunction(const string& name, const string& identifier1, const string& identifier2, Operations operation)
{
	if (m_variables.count(name) == 1 || m_functions.count(name) == 1)
	{
		throw invalid_argument("This name already exist");
		return false;
	}
	if (operation == Operations::nothing)
	{
		throw invalid_argument("operation can`t be 'nothing'");
		return false;
	}

	try
	{
		ObjectType identifierType1 = DefineIdentifierType(identifier1);
		ObjectType identifierType2 = DefineIdentifierType(identifier2);
		m_functions[name] = CreateFunctionStruct
		(
			name,
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
		throw;
		return false;
	}
}

map<string, double> SimpleCalculator::GetAllVariables()
{
	map<string, double> vars{};

	for (const auto &variable : m_variables)
	{
		vars[variable.first] = variable.second.value;
	}

	return vars;
}

map<string, double> SimpleCalculator::GetAllFunctions()
{
	map<string, double> funcs{};

	for (const auto& function : m_functions)
	{
		funcs[function.first] = function.second.value;
	}

	return funcs;
}

pair<string, double> SimpleCalculator::GetIdentifier(const string& name)
{
	if (m_variables.count(name) == 1)
	{
		return{ name, m_variables.find(name)->second.value };
	}
	else if (m_functions.count(name) == 1)
	{
		return{ name, m_functions.find(name)->second.value };
	}
	else
	{
		throw invalid_argument("identifier not exist");
		return pair<string, double>();
	}
}

void SimpleCalculator::SetRelevantFunctionsValues(const string& variableName)
{
	map<string, bool> updatedFunctions{};
	queue<Func*> q{};
	for (const auto& funcName : m_variables[variableName].dependensies)
	{
		if (updatedFunctions.count(funcName) == 0)
		{
			q.push(&m_functions.find(funcName)->second);
			updatedFunctions[funcName] = true;
		}
	}

	while (!q.empty())
	{
		Func* func = q.front();
		q.pop();

		for (const auto& dependenseName : func->dependensies)
		{
			if (updatedFunctions.count(dependenseName) == 0)
			{
				q.push(&m_functions.find(dependenseName)->second);
				updatedFunctions[dependenseName] = true;
			}
		}

		SetRelevantFunctionValue(func);
		
	}
}

void SimpleCalculator::SetRelevantFunctionValue(const Func* func)
{

	if (func->oper == Operations::nothing)
	{
		m_functions[func->name].value = *func->dep1;
	}
	else
	{
		m_functions[func->name].value = CalculateFunctionValue(*func->dep1, *func->dep2, func->oper);
	}

}

SimpleCalculator::Func SimpleCalculator::CreateFunctionStruct
(
	const string& name,
	const pair<string, ObjectType>& dep1, 
	const pair<string, ObjectType>& dep2, 
	Operations oper
)
{
	try
	{
		double* value1 = GetIdentifierPointer(dep1.first);
		double* value2 = (dep2.second != ObjectType::nothing) ? GetIdentifierPointer(dep2.first) : nullptr;
		return
		{ 
			name,
			dep2.second != ObjectType::nothing ?
				CalculateFunctionValue(*value1, *value2,  oper) : 
				*value1 ,
			value1 ,
			value2 ,
			{} , 
			oper 
		};
	}
	catch(invalid_argument ex)
	{
		throw;
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

ObjectType SimpleCalculator::DefineIdentifierType(const string& identifier)
{
	ObjectType identifierType = ObjectType::nothing;
	if (m_variables.count(identifier) == 1)
	{
		identifierType = ObjectType::var;
	}
	else if (m_functions.count(identifier) == 1)
	{
		identifierType = ObjectType::func;
	}
	else
	{
		throw invalid_argument("identifier not exist");
		return identifierType;
	}
	return identifierType;
}

void SimpleCalculator::UpdateDependensies(const string& funcName, const string& identifier, ObjectType identifierType)
{
	if (identifierType == ObjectType::var)
	{
		m_variables[identifier].dependensies.push_back(funcName);
	}
	else
	{
		m_functions[identifier].dependensies.push_back(funcName);
	}
}

double* SimpleCalculator::GetIdentifierPointer(const string& name)
{
	double* returnPoint = nullptr;
	if (m_variables.count(name) == 1)
	{
		returnPoint = &m_variables.find(name)->second.value;
	}
	else if (m_functions.count(name) == 1)
	{
		returnPoint = &m_functions.find(name)->second.value;
	}
	else
	{
		throw invalid_argument("identifier not exist");
	}
	return returnPoint;
}
