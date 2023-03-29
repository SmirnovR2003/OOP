// vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Vector.h"

using namespace std;


int main()
{

	vector<double> vecDouble = ReadVector(cin);

	if (vecDouble.empty())
	{
		cout << "No floating point numbers\n";
		return 1;
	}

	MultiplyAllByMinEllement(vecDouble);

	SortVector(vecDouble);

	WriteVector(vecDouble, cout);

	return 0;
}