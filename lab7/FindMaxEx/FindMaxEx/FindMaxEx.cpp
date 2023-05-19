// FindMaxEx.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	auto it = arr.begin();
	for (auto i = arr.begin(); i != arr.end(); ++i)
	{
		if (less(maxValue, *i)) it = i;
	}

	maxValue = *it;
	return true;
}

struct Sportsman
{
	string sername;
	string name;
	string patronymic;
	short height = 0;
	short weight = 0;
};

bool LessHeight(Sportsman sportsman1, Sportsman sportsman2)
{
	if (sportsman1.height < sportsman2.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LessWeight(Sportsman sportsman1, Sportsman sportsman2)
{
	if (sportsman1.weight < sportsman2.weight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, const Sportsman& sportsmam)
{
	os << sportsmam.sername << " " << sportsmam.name << " " << sportsmam.patronymic << " "
		<< sportsmam.height << " " << sportsmam.weight << endl;
	return os;
}

int main()
{
	vector<Sportsman> vec;
	Sportsman sportsman{ "Ivanov", "Ivan", "Ivanovich", 80, 170 };
	if (!FindMax(vec, sportsman, LessHeight)) cout << "vecor is empty\n";
	vec =
	{
		{"Ivanov", "Ivan", "Ivanovich", 170, 80 },
		{"Ivanov", "Ivan", "Ivanovich", 175, 89},
		{"Ivanov", "Ivan", "Ivanovich", 170,90},
		{"Ivanov", "Ivan", "Romanovich", 180, 100},
		{"Ivanov", "Romanov", "Ivanovich", 170, 91},
		{"Roman", "Ivan", "Ivanovich", 200, 89},
	};

	FindMax(vec, sportsman, LessHeight);
	cout << sportsman;
	FindMax(vec, sportsman, LessWeight);
	cout << sportsman;

}
