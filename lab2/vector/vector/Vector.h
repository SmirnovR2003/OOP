#pragma once
#include <vector>

std::vector<double> ReadVector(std::istream& fIn);

void MultiplyAllByMinEllement(std::vector<double>& vecDouble);

void SortVector(std::vector<double>& vecDouble);

void WriteVector(const std::vector<double>& vecDouble, std::ostream& fOut);