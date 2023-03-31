#pragma once
#include <map>
#include <string>
#include <functional>
typedef std::remove_cv<std::_Binder<std::remove_cv<std::_Unforced>::type, double(&)(double x, double y), std::reference_wrapper<double>, std::reference_wrapper<double>>>::type FuncValues;

class SimpleCalculator
{
public:
	enum class Operations
	{
		sum,
		difference,
		division,
		multiplication,
		nothing
	};

	SimpleCalculator();

	~SimpleCalculator();

	bool CreateVariable(std::string name, double num = NAN);

	bool CreateFunction(std::string name, double num1 = NAN,  double num2 = NAN, Operations oper = Operations::nothing);

	std::map<std::string, int> GetAllVariables();

	std::map<std::string, int> GetAllFunctions();

	std::pair<std::string, int> GetVariableValue(std::string name);

	std::pair<std::string, int> GetFunctionValue(std::string name);

private:

	struct Func
	{
		Operations oper = Operations::nothing;
		FuncValues funcValue;
		double dubValue;
		std::vector <std::string> dependensies;
	};

	std::map<std::string, int> variables{};

	std::map<std::string, Func> functions{};

	void SetRelevantFunctionsValues(std::string funcName);
};

