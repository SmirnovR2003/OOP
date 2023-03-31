// SimpleCalculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <functional>

using namespace std;

double my_divide(double x, double y) { return x / y; }
double& my_divide1(double x, double y) { double a = x / y; return a; }

int main()
{
	double x = 10, y = 2, a;

	auto fn_invert = bind(my_divide, ref(x), ref(y));

	cout << fn_invert() << endl;
	x = 40;
	cout << fn_invert() << endl;

	auto fn_invert1 = bind(my_divide, ref(x), ref(y));
	cout << fn_invert1() << endl;

	auto d = fn_invert1();
	auto c = d;

	auto fn_invert2 = bind(my_divide, ref(d), ref(y));
	cout << fn_invert2() << endl;

	x = 400;
	cout << fn_invert() << endl;
	cout << fn_invert1() << endl;
}
