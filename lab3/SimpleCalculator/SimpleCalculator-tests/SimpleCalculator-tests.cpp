// SimpleCalculator-tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../SimpleCalculator/SimpleCalculator.h"
#include "sstream"

using namespace std;

SCENARIO("CreateVariable function tests")
{
	SECTION("Check with not declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
	}

	SECTION("Check with declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
		CHECK_THROWS(!calc.CreateVariable("num1"));
	}
}

SCENARIO("SetVariableValue function tests")
{
	SECTION("Check with not declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.234));
	}

	SECTION("Check with declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(calc.SetVariableValue("num1", 10.234));
		REQUIRE(calc.SetVariableValue("num1", 11.234));
	}
}

SCENARIO("CreateFunction(string name, string identifier1) function tests")
{
	SECTION("Check with not declared function and variable")
	{
		SimpleCalculator calc;
		CHECK_THROWS(calc.CreateFunction("func1", "num1"));
	}

	SECTION("Check with not declared function and declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(calc.CreateFunction("func1", "num1"));
	}

	SECTION("Check with declared function")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(calc.CreateFunction("func1", "num1"));
		CHECK_THROWS(calc.CreateFunction("func1", "num1"));
	}

	SECTION("Create functions as variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(calc.CreateFunction("func1", "num1"));
		REQUIRE(calc.CreateFunction("func2", "func1"));
		REQUIRE(calc.CreateFunction("func3", "func2"));
	}
}

SCENARIO("CreateFunction(string name, string identifier1, string identifier2, Operations operation) function tests")
{
	SECTION("Check with not declared function and variable")
	{
		SimpleCalculator calc;
		CHECK_THROWS(calc.CreateFunction("func3", "num1", "num2", Operations::sum));
	}

	SECTION("Check with not declared function and declared variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.234));
		REQUIRE(calc.SetVariableValue("num2", 10.234));
		REQUIRE(calc.CreateFunction("func3", "num1", "num2", Operations::sum));
	}

	SECTION("Check with declared function and variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.234));
		REQUIRE(calc.SetVariableValue("num2", 10.234));
		REQUIRE(calc.CreateFunction("func1", "num1", "num2", Operations::sum));
		CHECK_THROWS(calc.CreateFunction("func1", "num1", "num2", Operations::sum));
	}

	SECTION("Create functions as variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.234));
		REQUIRE(calc.SetVariableValue("num2", 10.234));
		REQUIRE(calc.CreateFunction("func1", "num1", "num2", Operations::sum));
		REQUIRE(calc.CreateFunction("func2", "func1", "func1", Operations::mult));
		REQUIRE(calc.CreateFunction("func3", "func2", "func1", Operations::div));
		REQUIRE(calc.GetIdentifier("func3").second == 10.234 * 2);
	}


	SECTION("Create functions as variable and change first variable")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.234));
		REQUIRE(calc.SetVariableValue("num2", "num1"));

		REQUIRE(calc.CreateFunction("func1", "num1", "num2", Operations::sum));
		REQUIRE(calc.CreateFunction("func2", "func1", "func1", Operations::mult));
		REQUIRE(calc.CreateFunction("func3", "func2", "func1", Operations::div));
		REQUIRE(calc.GetIdentifier("func3").second == 10.234 * 2);

		REQUIRE(calc.SetVariableValue("num1", 5));
		REQUIRE(calc.GetIdentifier("num2").second == 10.234);
		REQUIRE(calc.GetIdentifier("func3").second == 15.234);
	}
}

SCENARIO("GetIdentifier function tests")
{
	SECTION("Check with not declared variable")
	{
		SimpleCalculator calc;

		CHECK_THROWS(calc.GetIdentifier("num1"));
	}

	SECTION("Check with variable is nan")
	{
		SimpleCalculator calc;

		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(isnan(calc.GetIdentifier("num1").second));
	}

	SECTION("Check with variable is not nan")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.GetIdentifier("num1").second == 10.123);
	}

	SECTION("Check with any variable are not nan")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.SetVariableValue("num2", 11.123));
		REQUIRE(calc.SetVariableValue("num3", 12.123));
		REQUIRE(calc.GetIdentifier("num2").second == 11.123);
	}

	SECTION("Check get function with one variable")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.GetIdentifier("num1").second == 10.123);
		REQUIRE(calc.CreateFunction("fn1", "num1"));
		REQUIRE(calc.GetIdentifier("fn1").second == 10.123);
	}

	SECTION("Check get function with sum two variables")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.SetVariableValue("num2", 10.123));
		REQUIRE(calc.CreateFunction("fn1", "num1", "num2", Operations::sum));
		REQUIRE(calc.GetIdentifier("fn1").second == 10.123 * 2);
	}
}

SCENARIO("GetAllVariables function tests")
{
	SECTION("Check with not declared variables")
	{
		SimpleCalculator calc;
		map<string, double> vars{};
		REQUIRE(calc.GetAllVariables() == vars);
	}

	SECTION("Check with variable is nan")
	{
		SimpleCalculator calc;
		map<string, double> vars{};
		vars["num1"] = NAN;
		REQUIRE(calc.CreateVariable("num1"));
		REQUIRE(calc.GetAllVariables().size() == vars.size());
		REQUIRE(isnan(calc.GetAllVariables().find("num1")->second));
	}

	SECTION("Check with variable is not nan")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.GetAllVariables().find("num1")->second == 10.123);
	}

	SECTION("Check with any variables are not nan")
	{
		SimpleCalculator calc;
		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.SetVariableValue("num2", 11.123));
		REQUIRE(calc.SetVariableValue("num3", 12.123));
		REQUIRE(calc.GetAllVariables().find("num1")->second == 10.123);
		REQUIRE(calc.GetAllVariables().find("num2")->second == 11.123);
		REQUIRE(calc.GetAllVariables().find("num3")->second == 12.123);
	}
}

SCENARIO("GetAllFunction function tests")
{
	SECTION("Check without functions")
	{
		SimpleCalculator calc;
		REQUIRE(calc.GetAllFunctions().size() == 0);
	}

	SECTION("Check with one function")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.CreateFunction("fn1", "num1"));
		REQUIRE(calc.GetAllFunctions().size() == 1);
	}

	SECTION("Check with any functions")
	{
		SimpleCalculator calc;

		REQUIRE(calc.SetVariableValue("num1", 10.123));
		REQUIRE(calc.SetVariableValue("num2", 10.123));
		REQUIRE(calc.CreateFunction("fn1", "num1", "num2", Operations::sum));
		REQUIRE(calc.CreateFunction("fn2", "num1", "num2", Operations::mult));
		REQUIRE(calc.CreateFunction("fn3", "num1", "num2", Operations::div));
		REQUIRE(calc.GetAllFunctions().size() == 3);
	}
}

//добавить тесты на вычисления