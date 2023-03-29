// Primes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Primes.h"
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid argument count\n"
			<< "Usage: flipbyte.exe <number>\n";
		return 1;
	}

	if (argv[1][0] < '0' || argv[1][0] > '9')
	{
		cout << "Invalid argument\nEnter number from 0 to 100000000\n";
		return 1;
	}

	int number;
	number = stoi(argv[1]);

	if(number < 0 || number > 100000000)
	{
		cout << "Invalid argument\nEnter number from 0 to 100000000\n";
		return 1;
	}

	set<int>primes = GeneratePrimeNumbersSet(number);

	if (primes.empty())cout << "There are no prime numbers in a given interval\n";
	else copy(primes.begin(), primes.end(), ostream_iterator<int>(cout, "\n"));
}

