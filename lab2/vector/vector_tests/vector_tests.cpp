// vector_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/Vector.h"
#include "string"
#include "sstream"


using namespace std;

SCENARIO("ReadVector function tests")
{

	SECTION("Check with empty file")
	{
		istringstream fIn("");
		vector<double> vecDouble = {  };
		vector<double> vecDouble2 = { };
		vecDouble = ReadVector(fIn);
		CHECK(vecDouble == vecDouble2);
	}

	SECTION("Check with not empty file")
	{
		istringstream fIn("12.2 1253.2 12.5 2.0");
		vector<double> vecDouble = {  };
		vector<double> vecDouble2 = { 12.2, 1253.2, 12.5, 2.0 };
		vecDouble = ReadVector(fIn);
		CHECK(vecDouble == vecDouble2);
	}

	SECTION("Check with uncorrect chars")
	{
		istringstream fIn("12.2 1253.2 s 5541 12.5 2.0");
		vector<double> vecDouble = {  };
		vector<double> vecDouble2 = { 12.2, 1253.2 };
		vecDouble = ReadVector(fIn);
		CHECK(vecDouble == vecDouble2);
	}
}

SCENARIO("MultiplyAllByMinEllement function tests")
{

	SECTION("Check with empty vector")
	{
		vector<double> vecDouble{};
		MultiplyAllByMinEllement(vecDouble);
		CHECK(vecDouble.empty());
	}

	SECTION("Check with not empty vector")
	{
		//более просты значения
		vector<double> vecDouble2{ 24.4, 2506.4, 25.0, 4.0 };
		vector<double> vecDouble = { 12.2, 1253.2, 12.5, 2.0 };
		MultiplyAllByMinEllement(vecDouble);
		CHECK(vecDouble == vecDouble2);
	}

	SECTION("Check with element of vector is zero")
	{
		vector<double> vecDouble = { 12.2, 1253.2, 12.5, 0.0 };
		vector<double> vecDouble2 = { 0.0 , 0.0 , 0.0 , 0.0 };
		MultiplyAllByMinEllement(vecDouble);
		CHECK(vecDouble == vecDouble2);
	}

	SECTION("Check with vector  negatives numbers ")
	{
		vector<double> vecDouble = { 12.2, 1253.2, 12.5, 0.0, -3.4, -100.0 };
		vector<double> vecDouble2 = { -1220.0, -125320.0, -1250.0, -0.0, 340.0, 10000.0 };
		MultiplyAllByMinEllement(vecDouble);
		CHECK(vecDouble == vecDouble2);
	}

}


SCENARIO("SortVector function tests")
{
	SECTION("Check with empty vector")
	{
		vector<double> vecDouble = { };
		vector<double> vecDouble2 = {  };
		SortVector(vecDouble);
		CHECK(vecDouble == vecDouble2);
	}

	SECTION("Check with not empty and not sort vector")
	{
		vector<double> vecDouble = { 12.2, 1253.2, 12.5, 0.0, -3.4, -100.0 };
		vector<double> vecDouble2 = { -100.0, -3.4, 0.0, 12.2, 12.5, 1253.2 };
		SortVector(vecDouble);
		CHECK(vecDouble == vecDouble2);
	}
}

SCENARIO("WriteVector function tests")
{
	SECTION("Check with empty vector")
	{
		ostringstream fOut("");
		string stringOut = "";
		vector<double> vecDouble = {  };
		WriteVector(vecDouble, fOut);
		CHECK(fOut.str() == stringOut);
	}

	SECTION("Check with not empty and not sort vector")
	{
		ostringstream fOut("");
		string stringOut = "24.400 2506.400 25.100 4.000 ";
		vector<double> vecDouble{ 24.4, 2506.4, 25.1, 4.0 };
		WriteVector(vecDouble, fOut);
		CHECK(fOut.str() == stringOut);
	}
}
