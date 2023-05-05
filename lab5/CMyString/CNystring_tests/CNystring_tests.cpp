// CNystring_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "../../../catch2/catch.hpp"
#include "../CMyString/CMyString.h"
using namespace std;

bool CheckEquals(const char* s1, const char* s2)
{
	if (strlen(s1) != strlen(s2)) return false;
	int i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])return false;
		i++;
	}
	return true;
}

SCENARIO("Constructors tests")
{
	SECTION("Check with empty string")
	{
		CHECK_NOTHROW(CMyString(""));
		CHECK_NOTHROW(CMyString("", 0));
		CHECK_NOTHROW(CMyString(string("")));
		CHECK_NOTHROW(CMyString(CMyString("", 0)));
	}

	SECTION("Check with one char")
	{
		CHECK_NOTHROW(CMyString("s"));
		CHECK_NOTHROW(CMyString("s", 1));
		CHECK_NOTHROW(CMyString(string("s")));
		CHECK_NOTHROW(CMyString(CMyString("s", 1)));
	}

	SECTION("Check with 'asd' string")
	{
		CHECK_NOTHROW(CMyString("asd"));
		CHECK_NOTHROW(CMyString("asd", 3));
		CHECK_NOTHROW(CMyString(string("asd")));
		CHECK_NOTHROW(CMyString(CMyString("asd", 3)));
	}
}

SCENARIO("GetLength tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");
		CMyString str2("", 0);
		CMyString str3(string(""));
		CMyString str4(CMyString("", 0));

		CHECK(str1.GetLength() == 0);
		CHECK(str2.GetLength() == 0);
		CHECK(str3.GetLength() == 0);
		CHECK(str4.GetLength() == 0);
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");
		CMyString str2("s", 1);
		CMyString str3(string("s"));
		CMyString str4(CMyString("s"));

		CHECK(str1.GetLength() == 1);
		CHECK(str2.GetLength() == 1);
		CHECK(str3.GetLength() == 1);
		CHECK(str4.GetLength() == 1);
	}

	SECTION("Check with 'asd' string")
	{
		CMyString str1("asd");
		CMyString str2("asd", 3);
		CMyString str3(string("asd"));
		CMyString str4(CMyString("asd"));

		CHECK(str1.GetLength() == 3);
		CHECK(str2.GetLength() == 3);
		CHECK(str3.GetLength() == 3);
		CHECK(str4.GetLength() == 3);
	}
}

SCENARIO("GetStringData tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");
		CMyString str2("", 0);
		CMyString str3(string(""));
		CMyString str4(CMyString("", 0));

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));
		CHECK(CheckEquals(str3.GetStringData(), ""));
		CHECK(CheckEquals(str4.GetStringData(), ""));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");
		CMyString str2("s", 1);
		CMyString str3(string("s"));
		CMyString str4(CMyString("s"));

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "s"));
		CHECK(CheckEquals(str4.GetStringData(), "s"));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");
		CMyString str2("asd", 3);
		CMyString str3(string("asd"));
		CMyString str4(CMyString("asd"));

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "asd"));
		CHECK(CheckEquals(str4.GetStringData(), "asd"));
	}
}

SCENARIO("SubString tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		CHECK(CheckEquals((str1.SubString(0,1)).GetStringData(), ""));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");

		CHECK(CheckEquals((str1.SubString(0, 1)).GetStringData(), "s"));
		CHECK(CheckEquals((str1.SubString(0, 0)).GetStringData(), ""));
	}

	SECTION("Check with some chars")
	{
		CMyString str1("asd");

		CHECK(CheckEquals((str1.SubString(0, 1)).GetStringData(), "a"));
		CHECK(CheckEquals((str1.SubString(1, 1)).GetStringData(), "s"));
		CHECK(CheckEquals((str1.SubString(1, 10)).GetStringData(), "sd"));
		CHECK(CheckEquals((str1.SubString(1)).GetStringData(), "sd"));
		CHECK(CheckEquals((str1.SubString(3)).GetStringData(), ""));
	}
}

SCENARIO("Clear tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		str1.Clear();
		CHECK(CheckEquals( str1.GetStringData(), ""));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");

		str1.Clear();
		CHECK(CheckEquals(str1.GetStringData(), ""));
	}

	SECTION("Check with some chars")
	{
		CMyString str1("asd");

		str1.Clear();
		CHECK(CheckEquals(str1.GetStringData(), ""));
	}
}

SCENARIO("operator=(CMyString const& other) tests")
{
	SECTION("Check with some string")
	{
		CMyString str1("s");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		str1 = str2;
		CHECK(CheckEquals(str1.GetStringData(), ""));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "a"));

		str1 = str2;
		CHECK(CheckEquals(str1.GetStringData(), "a"));
	}

	SECTION("Check with one string")
	{
		CMyString str1("asd");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));

		str1 = str1;
		CHECK(CheckEquals(str1.GetStringData(), "asd"));
	}
}

SCENARIO("operator+(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK(CheckEquals((str1 + str2).GetStringData(), ""));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "a"));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa"));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds"));
	}
}

SCENARIO("operator+(std::string const& str) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		string str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(str2 == "");

		CHECK(CheckEquals((str1 + str2).GetStringData(), ""));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		string str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(str2 == "a");

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa"));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		string str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(str2 == "s");

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds"));
	}
}

SCENARIO("operator+(const char* other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		const char* str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2, ""));

		CHECK(CheckEquals((str1 + str2).GetStringData(), ""));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		const char* str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2, "a"));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa"));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		const char* str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2, "s"));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds"));
	}
}

SCENARIO("operator+=(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), ""));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "a"));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), "sa"));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), "asds"));
	}
}

SCENARIO("operator==(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK(str1 == str2);
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK(str1 == str2);
		CHECK(!(str1 == str3));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(str1 == str2);
		CHECK(!(str1 == str3));
		CHECK(!(str4 == str3));
	}
}

SCENARIO("operator!=(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK(!(str1 != str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK(!(str1 != str2));
		CHECK(str1 != str3);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "asd"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(!(str1 != str2));
		CHECK(str1 != str3);
		CHECK(str4 != str3);
	}
}

SCENARIO("operator<(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK(!(str1 < str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK(!(str1 < str2));
		CHECK(str3 < str1);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "as"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(str1 < str2);
		CHECK(str2 < str3);
		CHECK(!(str3 < str4));
		CHECK(!(str3 < str3));
	}
}

SCENARIO("operator<=(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK((str1 <= str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK((str1 <= str2));
		CHECK(str3 <= str1);
		CHECK(!(str1 <= str3));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "as"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(str1 <= str2);
		CHECK(str2 <= str3);
		CHECK(!(str3 <= str4));
		CHECK((str3 <= str3));
	}
}

SCENARIO("operator>(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK(!(str1 > str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK(!(str1 > str2));
		CHECK(str1 > str3);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "as"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(!(str1 > str2));
		CHECK(!(str2 > str3));
		CHECK((str3 > str4));
		CHECK(!(str3 > str3));
	}
}

SCENARIO("operator>=(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), ""));
		CHECK(CheckEquals(str2.GetStringData(), ""));

		CHECK((str1 >= str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s"));
		CHECK(CheckEquals(str2.GetStringData(), "s"));
		CHECK(CheckEquals(str3.GetStringData(), "a"));

		CHECK((str1 >= str2));
		CHECK((str1 >= str3));
		CHECK((str1 >= str3));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "as"));
		CHECK(CheckEquals(str2.GetStringData(), "asd"));
		CHECK(CheckEquals(str3.GetStringData(), "ssd"));
		CHECK(CheckEquals(str4.GetStringData(), "asdd"));

		CHECK(!(str1 >= str2));
		CHECK((str3 >= str2));
		CHECK((str3 >= str4));
		CHECK((str3 >= str3));
	}
}

SCENARIO("const char& operator[](const int index) tests")
{
	SECTION("Check with empty string")
	{
		const CMyString str1("");

		CHECK_THROWS(str1[0]);
	}

	SECTION("Check with one char string")
	{
		const CMyString str1("s");

		CHECK_NOTHROW(str1[0]);
		CHECK(str1[0] == 's');

		CHECK_THROWS(str1[1]);
	}

	SECTION("Check with some string")
	{
		const CMyString str1("asd");

		CHECK_NOTHROW(str1[0]);
		CHECK(str1[0] == 'a');

		CHECK_NOTHROW(str1[1]);
		CHECK(str1[1] == 's');

		CHECK_NOTHROW(str1[2]);
		CHECK(str1[2] == 'd');
		CHECK_THROWS(str1[3]);
	}
}

SCENARIO("char& operator[](const int index) tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		CHECK_THROWS(str1[0]);
	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		CHECK_NOTHROW(str1[0]);
		CHECK(str1[0] == 's');

		str1[0] = 'a';

		CHECK(str1[0] == 'a');

		CHECK_THROWS(str1[1]);
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		CHECK_NOTHROW(str1[0]);
		CHECK(str1[0] == 'a');

		CHECK_NOTHROW(str1[1]);
		CHECK(str1[1] == 's');

		CHECK_NOTHROW(str1[2]);
		CHECK(str1[2] == 'd');

		str1[0] = '1';
		str1[1] = '2';
		str1[2] = '3';

		CHECK(str1[0] == '1');
		CHECK(str1[1] == '2');
		CHECK(str1[2] == '3');

		CHECK_THROWS(str1[3]);
	}
}