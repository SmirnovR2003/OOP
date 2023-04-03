
#include <iostream>
#include "SimpleCalculator.h"
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

void ShowCommand()
{
	cout << "Commands for using car\n";
	cout << "	'stop' for end calculating\n";
	cout << "	'help' for show commands\n";
	cout << "	'var <identifier>' for create variable\n";
	cout << "	'let <identifier1> = <floating point number>' or 'let <identifier1> = <identifier2>' for set variable's value\n";
	cout << "	'fn <identifier1> = <identifier2>' or 'fn <identifier1> = <identifier2><operation><identifier3> for create function'\n";
	cout << "	'print <identifier>' for see identifier's value\n";
	cout << "	'printvars' for see all variables values\n";
	cout << "	'printfns' for see all functions values\n";
}


int main()
{
	SimpleCalculator calc;
	string answer;
	ShowCommand();

	cout << ">";
	getline(cin, answer);

	while (answer.substr(0, 4) != "stop")
	{
		if (answer.substr(0, 4) == "help")
		{
			ShowCommand();
		}
		else if (answer.substr(0, 3) == "var")
		{

		}
		else if (answer.substr(0, 3) == "let")
		{

		}
		else if (answer.substr(0, 2) == "fn")
		{

		}
		else if (answer.substr(0, 6) == "print " || answer.substr(0, 6) == "print<")
		{

		}
		else if (answer.substr(0, 6) == "print " || answer.substr(0, 6) == "printvars<")
		{

		}
		else if (answer.substr(0, 6) == "print " || answer.substr(0, 6) == "printfns<")
		{

		}
		else
		{
			cout << "Invalid command\nUse command 'help' for show commands\n";
		}
		
		cout << ">";
		getline(cin, answer);
	}
}
