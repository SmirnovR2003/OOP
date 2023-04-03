#pragma once
#include <map>
#include <string>
#include <functional>
#include <vector>

enum class Operations
{
	sum,
	sub,
	div,
	mult,
	nothing
};

enum class ObjectType
{
	var,
	func,
	nothing
};

class SimpleCalculator
{
public:

	SimpleCalculator();

	~SimpleCalculator();

	bool CreateVariable(std::string name);

	bool SetVariableValue(std::string name, double value);

	bool SetVariableValue(std::string name, std::string identifier);

	bool CreateFunction(std::string name, std::string identifier);

	bool CreateFunction(std::string name, std::string identifier1, std::string identifier2, Operations operation);

	std::map<std::string, double> GetAllVariables();

	std::map<std::string, double> GetAllFunctions();

	std::pair<std::string, double> GetVariable(std::string name);

	std::pair<std::string, double> GetFunction(std::string name);

private:

	struct Func
	{
		double value = NAN;
		std::pair<std::string, ObjectType> dep1, dep2; //имена функций или переменных от которых зависит данная функция
		std::vector <std::string> dependensies; //имена функций зависящих от данниой функции
		Operations oper = Operations::nothing;
	};

	struct Variable
	{
		double value = NAN;
		std::vector <std::string> dependensies; //имена функций зависящих от данниой переменной
	};

	std::map<std::string, Variable> variables;

	std::map<std::string, Func> functions;

	void SetRelevantFunctionsValues(std::string variableName);

	Func CreateFunctionStruct(
		std::pair<std::string, ObjectType> dep1,
		std::pair<std::string, ObjectType> dep2,
		Operations oper
	);

	double CalculateFunctionValue(double value1, double value2, Operations oper);

	double CalculateFirstFunctionValue(std::pair<std::string, ObjectType> dep1);

	double CalculateSecondFunctionValue(std::pair<std::string, ObjectType> dep2);

	ObjectType DefineIdentifierType(std::string identifier);

	void UpdateDependensies(std::string funcName, std::string identifier, ObjectType identifierType);
};

