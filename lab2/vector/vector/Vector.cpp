#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Vector.h"

using namespace std;

vector<double> ReadVector(istream& fIn)
{
	vector<double> vecDouble(istream_iterator<double>(fIn), (istream_iterator<double>()));
	return vecDouble;
}

void MultiplyAllByMinEllement(vector<double>& vecDouble)
{
	if (vecDouble.empty()) return;

	double minElement = *min_element(vecDouble.begin(), vecDouble.end());

	transform(vecDouble.begin(), vecDouble.end(),
		vecDouble.begin(), [minElement](double e) { return e * minElement; });
}

void SortVector(vector<double>& vecDouble)
{
	sort(vecDouble.begin(), vecDouble.end());

}

void WriteVector(const vector<double>& vecDouble, ostream& fOut)
{
	if (vecDouble.empty()) return;

	fOut << fixed << setprecision(3);
	copy(vecDouble.begin(), vecDouble.end(),
		ostream_iterator<double>(fOut, " "));
}