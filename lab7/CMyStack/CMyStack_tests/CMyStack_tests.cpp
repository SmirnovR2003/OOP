
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include "../../../catch2/catch.hpp"
#include "../CMyStack/CMyStack.h"
using namespace std;

//all test check CMyStack with string and int
SCENARIO("Constructors tests")
{
	SECTION("Check with empty stack")
	{
		//string
		CHECK_NOTHROW(CMyStack<string>());
		CMyStack<string> stackString;
		CHECK_NOTHROW(CMyStack<string>(stackString));
		CHECK_NOTHROW(CMyStack<string>(move(stackString)));

		//int
		CHECK_NOTHROW(CMyStack<int>());
		CMyStack<int> stackInt;
		CHECK_NOTHROW(CMyStack<int>(stackInt));
		CHECK_NOTHROW(CMyStack<int>(move(stackInt)));
	}

	SECTION("Check stack with one element")
	{
		//string
		CMyStack<string> stackString;
		stackString.Push("asd");
		CHECK_NOTHROW(CMyStack<string>(stackString));
		CHECK_NOTHROW(CMyStack<string>(move(stackString)));

		//int
		CMyStack<int> stackInt;
		stackInt.Push(1);
		CHECK_NOTHROW(CMyStack<int>(stackInt));
		CHECK_NOTHROW(CMyStack<int>(move(stackInt)));
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString;
		stackString.Push("asd");
		stackString.Push("asd");
		stackString.Push("asd");
		CHECK_NOTHROW(CMyStack<string>(stackString));
		CHECK_NOTHROW(CMyStack<string>(move(stackString)));

		CMyStack<int> stackInt;
		stackInt.Push(1);
		stackInt.Push(2);
		stackInt.Push(3);
		CHECK_NOTHROW(CMyStack<int>(stackInt));
		CHECK_NOTHROW(CMyStack<int>(move(stackInt)));
	}
}

SCENARIO("Push function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString;
		CHECK_NOTHROW(stackString.Push("asd"));

		CMyStack<int> stackInt;
		CHECK_NOTHROW(stackInt.Push(1));
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString;
		CHECK_NOTHROW(stackString.Push(""));
		CHECK_NOTHROW(stackString.Push("a"));
		CHECK_NOTHROW(stackString.Push("asd"));

		CMyStack<int> stackInt;
		CHECK_NOTHROW(stackInt.Push(12));
		CHECK_NOTHROW(stackInt.Push(0));
		CHECK_NOTHROW(stackInt.Push(-98));
	}
}

SCENARIO("Size function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString;
		CHECK(stackString.Size() == 0);

		CMyStack<int> stackInt;
		CHECK(stackInt.Size() == 0);
	}

	SECTION("Check stack with one element")
	{
		CMyStack<string> stackString;
		stackString.Push("asd");
		CHECK(stackString.Size() == 1);

		CMyStack<int> stackInt;
		stackInt.Push(1);
		CHECK(stackInt.Size() == 1);
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString;
		stackString.Push("asd");
		stackString.Push("asd");
		stackString.Push("asd");
		CHECK(stackString.Size() == 3);

		CMyStack<int> stackInt;
		stackInt.Push(1);
		stackInt.Push(1);
		stackInt.Push(1);
		CHECK(stackInt.Size() == 3);
	}
}

SCENARIO("Top function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString;
		CHECK_THROWS_AS(stackString.Top(), runtime_error);

		CMyStack<int> stackInt;
		CHECK_THROWS_AS(stackInt.Top(), runtime_error);
	}

	SECTION("Check stack with one element")
	{
		CMyStack<string> stackString;
		stackString.Push("asd");
		CHECK(stackString.Top() == "asd");

		CMyStack<int> stackInt;
		stackInt.Push(1);
		CHECK(stackInt.Top() == 1);
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString;
		stackString.Push("asd1");
		stackString.Push("asd2");
		stackString.Push("asd3");
		CHECK(stackString.Top() == "asd3");

		CMyStack<int> stackInt;
		stackInt.Push(1);
		stackInt.Push(2);
		stackInt.Push(3);
		CHECK(stackInt.Top() == 3);
	}
}

SCENARIO("Pop function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString;
		CHECK_THROWS_AS(stackString.Pop(), runtime_error);

		CMyStack<int> stackInt;
		CHECK_THROWS_AS(stackInt.Pop(), runtime_error);
	}

	SECTION("Check stack with one element")
	{
		CMyStack<string> stackString;
		stackString.Push("asd");
		CHECK(stackString.Top() == "asd");
		CHECK_NOTHROW(stackString.Pop());
		CHECK_THROWS_AS(stackString.Pop(), runtime_error);

		CMyStack<int> stackInt;
		stackInt.Push(1);
		CHECK(stackInt.Top() == 1);
		CHECK_NOTHROW(stackInt.Pop());
		CHECK_THROWS_AS(stackInt.Pop(), runtime_error);
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString;
		stackString.Push("asd1");
		stackString.Push("asd2");
		stackString.Push("asd3");
		CHECK(stackString.Top() == "asd3");
		CHECK_NOTHROW(stackString.Pop());
		CHECK(stackString.Top() == "asd2");

		CMyStack<int> stackInt;
		stackInt.Push(1);
		stackInt.Push(2);
		stackInt.Push(3);
		CHECK(stackInt.Top() == 3);
		CHECK_NOTHROW(stackInt.Pop());
		CHECK(stackInt.Top() == 2);
	}
}

SCENARIO("operator=(const CMyStack& other) function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		CHECK_NOTHROW(stackString2 = stackString1);

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		CHECK_NOTHROW(stackInt2 = stackInt1);
	}

	SECTION("Check stack with one element")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		stackString1.Push("asd");
		CHECK_NOTHROW(stackString2 = stackString1);
		CHECK(stackString2.Top() == "asd");

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		stackInt1.Push(1);
		CHECK_NOTHROW(stackInt2 = stackInt1);
		CHECK(stackInt2.Top() == 1);
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		stackString1.Push("asd1");
		stackString1.Push("asd2");
		stackString1.Push("asd3");
		CHECK_NOTHROW(stackString2 = stackString1);
		CHECK(stackString2.Top() == "asd3");

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		stackInt1.Push(1);
		stackInt1.Push(2);
		stackInt1.Push(3);
		CHECK_NOTHROW(stackInt2 = stackInt1);
		CHECK(stackInt2.Top() == 3);
	}
}

SCENARIO("operator=(CMyStack&& other) function tests")
{
	SECTION("Check with empty stack")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		CHECK_NOTHROW(stackString2 = move(stackString1));

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		CHECK_NOTHROW(stackInt2 = move(stackInt1));
	}

	SECTION("Check stack with one element")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		stackString1.Push("asd");
		CHECK_NOTHROW(stackString2 = move(stackString1));
		CHECK(stackString2.Top() == "asd");

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		stackInt1.Push(1);
		CHECK_NOTHROW(stackInt2 = move(stackInt1));
		CHECK(stackInt2.Top() == 1);
	}

	SECTION("Check stack with any elements")
	{
		CMyStack<string> stackString1;
		CMyStack<string> stackString2;
		stackString1.Push("asd1");
		stackString1.Push("asd2");
		stackString1.Push("asd3");
		CHECK_NOTHROW(stackString2 = move(stackString1));
		CHECK(stackString2.Top() == "asd3");

		CMyStack<int> stackInt1;
		CMyStack<int> stackInt2;
		stackInt1.Push(1);
		stackInt1.Push(2);
		stackInt1.Push(3);
		CHECK_NOTHROW(stackInt2 = move(stackInt1));
		CHECK(stackInt2.Top() == 3);
	}
}