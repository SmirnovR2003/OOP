// Car.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Car.h"
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

void ShowCommand()
{
	cout << "Commands for using car\n";
	cout << "	'Stop' for end of driving\n";
	cout << "	'Help' for show commands\n";
	cout << "	'Info' for see information about car\n";
	cout << "	'EngineOn' for turn on the engine\n";
	cout << "	'EngineOff' for turn off the engine\n";
	cout << "	'SetGear <gear>' for set gear (-1 <= gear <= 5)\n";
	cout << "	'SetSpeed <speed>' for set speed\n";
	cout << "		gear = -1 -> 0 <= speed <= 20\n";
	cout << "		gear = 0 -> speed less than the current speed\n";
	cout << "		gear = 1 -> 0 <= speed <= 30\n";
	cout << "		gear = 2 -> 20 <= speed <= 50\n";
	cout << "		gear = 3 -> 30 <= speed <= 60\n";
	cout << "		gear = 4 -> 40 <= speed <= 90\n";
	cout << "		gear = 5 -> 50 <= speed <= 150\n";
}

int main()
{
	Car car;
	string answer;
	int intAnswer = 0;
	ShowCommand();
	cout << ">";
	cin >> answer;
	transform(answer.begin(), answer.end(), answer.begin(), [](char ch) { return tolower(ch);});
	while (answer != "Stop")
	{
		if (answer == "Help")
		{
			ShowCommand();
		}
		else if (answer == "Info")
		{
			cout << "Engine condition: " << (car.IsTurnedOn() ? "On" : "Off") << endl;
			cout << "Gear is " << car.GetGear() << endl;
			cout << "Speed is " << car.GetSpeed() << endl;
			cout << "Direction is " << car.GetDirection() << endl;
		}
		else if (answer == "EngineOn")
		{
			if (car.TurnOnEngine())
			{
				cout << "Engine is on\n";
			}
			else
			{
				cout << "Error\nTry again\n";
			}
		}
		else if (answer == "EngineOff")
		{
			if (car.TurnOffEngine())
			{
				cout << "Engine is off\n";
			}
			else
			{
				cout << "Error\nGear and speed must be zero\n";
			}
		}
		else if (answer == "SetGear")
		{
			try
			{
				getline(cin, answer);
				intAnswer = stoi(answer);
				if (!car.SetGear(intAnswer))
				{
					if (!car.IsTurnedOn())
					{
						cout << "Turn on the engine\n";
					}
					else 
					{
						cout << "Invalid gear\n";
						cout << "Enter a gear appropriated current speed or switch to the appropriate speed\n";
					}
				}
				else
				{
					cout << "The selected gear is set\n";
				}
			}
			catch (exception ex)
			{
				cout << "Error reading the gear\n";
				cout << "Enter a gear from -1 to 5\n";
			}
		}
		else if (answer == "SetSpeed")
		{
			try
			{
				getline(cin, answer);
				intAnswer = stoi(answer);
				if (!car.SetSpeed(intAnswer))
				{
					if (!car.IsTurnedOn())
					{
						cout << "Turn on the engine\n";
					}
					else if (pair<int, int> speedLimit = car.GetSpeedsInGear(); intAnswer < speedLimit.first || intAnswer > speedLimit.first)
					{
						cout << "Invalid speed\n";
						cout << "Enter a speed appropriated current gear or switch to the appropriate gear\n";
					}
				}
				else
				{
					cout << "The selected speed is set\n";
				}
			}
			catch (exception ex)
			{
				cout << "Error reading the speed\n";
				cout << "Enter a speed appropriated current gear\n";
			}
		}
		else
		{
			cout << "Invalid command\nUse command 'Help' for show commands\n";
		}
		cout << ">";
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), [](char ch) { return tolower(ch);});
	} 
}
