
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "../../../catch2/catch.hpp"
#include "../CStringStack/CStringStack.h"
using namespace std;


SCENARIO("Constructors tests")
{
	SECTION("Check with empty stack")
	{
		CHECK_NOTHROW(CStringStack());
		CStringStack stack;
		CHECK_NOTHROW(CStringStack(stack));
		CHECK_NOTHROW(CStringStack(move(stack)));
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack;
		stack.Push("asd");
		CHECK_NOTHROW(CStringStack(stack));
		CHECK_NOTHROW(CStringStack(move(stack)));
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack;
		stack.Push("asd");
		stack.Push("asd");
		stack.Push("asd");
		CHECK_NOTHROW(CStringStack(stack));
		CHECK_NOTHROW(CStringStack(move(stack)));
	}
}

SCENARIO("Push function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack;
		CHECK_NOTHROW(stack.Push("asd"));
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack;
		CHECK_NOTHROW(stack.Push(""));
		CHECK_NOTHROW(stack.Push("asd"));
		CHECK_NOTHROW(stack.Push("asd"));
	}
}

SCENARIO("Size function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack;
		CHECK(stack.Size() == 0);
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack;
		stack.Push("asd");
		CHECK(stack.Size() == 1);
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack;
		stack.Push("asd");
		stack.Push("asd");
		stack.Push("asd");
		CHECK(stack.Size() == 3);
	}
}

SCENARIO("Top function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack;
		CHECK_THROWS_AS(stack.Top(), runtime_error);
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack;
		stack.Push("asd");
		CHECK(stack.Top() == "asd");
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack;
		stack.Push("asd1");
		stack.Push("asd2");
		stack.Push("asd3");
		CHECK(stack.Top() == "asd3");
	}
}

SCENARIO("Pop function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack;
		CHECK_THROWS_AS(stack.Pop(), runtime_error);
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack;
		stack.Push("asd");
		CHECK(stack.Top() == "asd");
		CHECK_NOTHROW(stack.Pop());
		CHECK_THROWS_AS(stack.Pop(), runtime_error);
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack;
		stack.Push("asd1");
		stack.Push("asd2");
		stack.Push("asd3");
		CHECK(stack.Top() == "asd3");
		CHECK_NOTHROW(stack.Pop());
		CHECK(stack.Top() == "asd2");
	}
}

SCENARIO("operator=(const CStringStack& other) function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack1;
		CStringStack stack2;
		CHECK_NOTHROW(stack2 = stack1);
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack1;
		CStringStack stack2;
		stack1.Push("asd");
		CHECK_NOTHROW(stack2 = stack1);
		CHECK(stack2.Top() == "asd");
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack1;
		CStringStack stack2;
		stack1.Push("asd1");
		stack1.Push("asd2");
		stack1.Push("asd3");
		CHECK_NOTHROW(stack2 = stack1);
		CHECK(stack2.Top() == "asd3");
	}
}

SCENARIO("operator=(CStringStack&& other) function tests")
{
	SECTION("Check with empty stack")
	{
		CStringStack stack1;
		CStringStack stack2;
		CHECK_NOTHROW(stack2 = move(stack1));
	}

	SECTION("Check stack with one element")
	{
		CStringStack stack1;
		CStringStack stack2;
		stack1.Push("asd");
		CHECK_NOTHROW(stack2 = move(stack1));
		CHECK(stack2.Top() == "asd");
	}

	SECTION("Check stack with any elements")
	{
		CStringStack stack1;
		CStringStack stack2;
		stack1.Push("asd1");
		stack1.Push("asd2");
		stack1.Push("asd3");
		CHECK_NOTHROW(stack2 = move(stack1));
		CHECK(stack2.Top() == "asd3");
	}
}