// Primes_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../Primes/Primes.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

using namespace std;

SCENARIO("GeneratePrimeNumbersSet function tests")
{
	SECTION("Check with 0")
	{
		set<int> set1 = GeneratePrimeNumbersSet(0), set2{};
		CHECK(set1 == set2);
	}

	SECTION("Check with 1")
	{
		set<int> set1 = GeneratePrimeNumbersSet(1), set2{};
		CHECK(set1 == set2);
	}

	SECTION("Check with 2")
	{
		set<int> set1 = GeneratePrimeNumbersSet(2), set2{ 2 };
		CHECK(set1 == set2);
	}

	SECTION("Check with 100")
	{
		set<int> set1 = GeneratePrimeNumbersSet(100), set2{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
		CHECK(set1 == set2);
	}

	SECTION("Check with 53(prime number)")
	{
		set<int> set1 = GeneratePrimeNumbersSet(53), set2{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53 };
		CHECK(set1 == set2);
	}

	SECTION("Check with negative numbers")
	{
		set<int> set1 = GeneratePrimeNumbersSet(-1);
		CHECK(set1.size() == 0);
	}

	//if not define debug
	SECTION("Check with 100000000")
	{
		set<int> set1 = GeneratePrimeNumbersSet(100000000);
		CHECK(set1.size() == 5761455);
	}

}