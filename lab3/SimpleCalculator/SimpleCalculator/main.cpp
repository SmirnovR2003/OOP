
#include <iostream>
#include "SimpleCalculator.h"
#include <windows.h>
#include <string>
#include <algorithm>
#include <regex>
#include <iomanip>
using namespace std;

void ShowCommand()
{
	cout << "Commands for using car:\n";
	cout << "	'stop' for end calculating\n";
	cout << "	'help' for show commands\n";
	cout << "	'var <identifier>' for create variable\n";
	cout << "	'let <identifier1> = <floating point number>' for set value of a floating-point number to a identifier\n";
	cout << "	'let <identifier1> = <identifier2>' for set the value of identifier2 to a identifier1\n";
	cout << "	'fn <identifier1> = <identifier2>' for create function'\n";
	cout << "	'fn <identifier1> = <identifier2><operation><identifier3> for create function'\n";
	cout << "	'print <identifier>' for see identifier's value\n";
	cout << "	'printvars' for see all variables values\n";
	cout << "	'printfns' for see all functions values\n";
	cout << "Identifier must consist only of a letter and some letters, digits or underlinings\n";
}

void VarCommand(SimpleCalculator& calc, const string& answer)
{
	const auto r = regex(R"([ ]+([A-Za-z_][0-9A-Za-z_]*)[ ]*)", regex_constants::icase);
	smatch matches;

	if (!regex_search(answer, matches, r))
	{
		cout << "Enter the notation according to the 'var' command structure\nFor more information use command 'help'\n";
		return;
	}
	if (matches.prefix().matched || matches.suffix().matched)
	{
		cout << "Enter the notation according to the 'var' command structure\nFor more information use command 'help'\n";
		return;
	}

	string variable = matches[1].str();
	try
	{
		calc.CreateVariable(variable);
	}
	catch (const invalid_argument& ex)
	{
		cout << ex.what() << endl;
	}
}

void LetCommand(SimpleCalculator& calc, const string& answer)
{
	const auto r = regex
	(
		R"([ ]+([A-Za-z_][0-9A-Za-z_]*)[ ]*?=[ ]*?(([-]?([0-9]*[.])?[0-9]+)|([A-Za-z_][0-9A-Za-z_]*))[ ]*)", 
		regex_constants::icase
	);
	smatch matches;

	if (!regex_search(answer, matches, r))
	{
		cout << "Enter the notation according to the 'let' command structure\nFor more information use command 'help'\n";
		return;
	}
	if (matches.prefix().matched || matches.suffix().matched)
	{
		cout << "Enter the notation according to the 'let' command structure\nFor more information use command 'help'\n";
		return;
	}

	string variable = matches[1].str();
	string value = matches[2].str();
	try
	{
		if (value[0] >= '0' && value[0] <= '9' || value[0] == '-')
		{
			calc.SetVariableValue(variable, stod(value));
		}
		else
		{
			calc.SetVariableValue(variable, value);
		}
	}
	catch (const invalid_argument& ex)
	{
		cout << ex.what() << endl;
	}
}

void FnCommand(SimpleCalculator& calc, const string& answer)
{
	const auto r = regex
	(
		R"([ ]+([A-Za-z_][0-9A-Za-z_]*)[ ]*?=[ ]*?([A-Za-z_][0-9A-Za-z_]*)[ ]*(([+\-*\/])[ ]*([A-Za-z_][0-9A-Za-z_]*))?[ ]*)", 
		regex_constants::icase
	);
	smatch matches;

	if (!regex_search(answer, matches, r))
	{
		cout << "Enter the notation according to the 'fn' command structure\nFor more information use command 'help'\n";
		return;
	}
	if (matches.prefix().matched || matches.suffix().matched)
	{
		cout << "Enter the notation according to the 'fn' command structure\nFor more information use command 'help'\n";
		return;
	}

	try
	{
		if (matches[3].matched)
		{
			Operations oper;
			switch (matches[4].str()[0])
			{
			case '+':
				oper = Operations::sum;
				break;
			case '*':
				oper = Operations::mult;
				break;
			case '-':
				oper = Operations::sub;
				break;
			case '/':
				oper = Operations::div;
				break;
			default:
				oper = Operations::nothing;
				break;
			} 
			calc.CreateFunction(matches[1].str(), matches[2].str(), matches[5].str(), oper);
		}
		else
		{
			calc.CreateFunction(matches[1].str(), matches[2].str());
		}
	}
	catch (const invalid_argument& ex)
	{
		cout << ex.what() << endl;
	}
}

void PrintCommand(SimpleCalculator& calc, const string& answer)
{
	const auto r = regex(R"([ ]+([A-Za-z_][0-9A-Za-z_]*)[ ]*)", regex_constants::icase);
	smatch matches;

	if (!regex_search(answer, matches, r))
	{
		cout << "Enter the notation according to the 'print' command structure\nFor more information use command 'help'\n";
		return;
	}
	if (matches.prefix().matched || matches.suffix().matched)
	{
		cout << "Enter the notation according to the 'print' command structure\nFor more information use command 'help'\n";
		return;
	}

	try
	{
		pair<string, double> identifier = calc.GetIdentifier(matches[1].str());
		cout << identifier.first << ":" << identifier.second << endl;
	}
	catch (const invalid_argument& ex)
	{
		cout << ex.what() << endl;
	}
}

void PrintVarsCommand(SimpleCalculator& calc, const string& answer)
{
	for (const auto& identifier : calc.GetAllVariables())
	{
		cout << identifier.first << ":" << identifier.second << endl;
	}
}

void PrintFnsCommand(SimpleCalculator& calc, const string& answer)
{
	for (const auto& identifier : calc.GetAllFunctions())
	{
		cout << identifier.first << ":" << identifier.second << endl;
	}
}

int main()
{
	
	SimpleCalculator calc;
	string answer;
	ShowCommand();

	//диалог с пользователем вынести
	cout << ">";
	cout << fixed << setprecision(2);
	while (getline(cin, answer))
	{
		//убрать substr сделать через >>
		//сделать команды через map
		if (answer.substr(0, 4) == "help")
		{
			ShowCommand();
		}
		else if (answer.substr(0, 3) == "var")
		{
			VarCommand(calc, answer.substr(3));
		}
		else if (answer.substr(0, 3) == "let")
		{
			LetCommand(calc, answer.substr(3));
		}
		else if (answer.substr(0, 2) == "fn")
		{
			FnCommand(calc, answer.substr(2));
		}
		else if (answer.substr(0, 9) == "printvars")
		{
			PrintVarsCommand(calc, answer.substr(9));
		}
		else if (answer.substr(0, 8) == "printfns")
		{
			PrintFnsCommand(calc, answer.substr(8));
		}
		else if (answer.substr(0, 5) == "print")
		{
			PrintCommand(calc, answer.substr(5));
		}
		else if (answer.substr(0, 4) == "stop")
		{
			break;
		}
		else
		{
			cout << "Invalid command\nUse command 'help' for show commands\n";
		}
		
		cout << ">";
	}
}
