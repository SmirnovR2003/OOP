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

	bool CreateVariable(const std::string& name);

	bool SetVariableValue(const std::string& name, double value);

	bool SetVariableValue(const std::string& name, const std::string& identifier);

	bool CreateFunction(const std::string& name, const std::string& identifier);

	bool CreateFunction(const std::string& name, const std::string& identifier1, const std::string& identifier2, Operations operation);

	std::map<std::string, double> GetAllVariables();

	std::map<std::string, double> GetAllFunctions();

	std::pair<std::string, double> GetIdentifier(const std::string& name);

private:

	struct Func
	{
		std::string name;
		double value = NAN;
		double* dep1 = nullptr; //ссылка на значение первого идентификатора от которго зависит функция
		double* dep2 = nullptr; //ссылка на значение второго идентификатора от которго зависит функция. если oper == nothing, то nullptr
		std::vector <std::string> dependensies; //имена функций зависящих от данниой функции
		Operations oper = Operations::nothing;
	};

	struct Variable
	{
		double value = NAN;
		std::vector <std::string> dependensies; //имена функций зависящих от данниой переменной
	};

	std::map<std::string, Variable> m_variables;

	std::map<std::string, Func> m_functions;

	void SetRelevantFunctionsValues(const std::string& variableName);

	void SetRelevantFunctionValue(const Func* func);

	Func CreateFunctionStruct
	(
		const std::string& name,
		const std::pair<std::string, ObjectType>& dep1,
		const std::pair<std::string, ObjectType>& dep2,
		Operations oper
	);

	double CalculateFunctionValue(double value1, double value2, Operations oper);

	ObjectType DefineIdentifierType(const std::string& identifier);

	void UpdateDependensies(const std::string& funcName, const std::string& identifier, ObjectType identifierType);

	double* GetIdentifierPointer(const std::string& name);
};

