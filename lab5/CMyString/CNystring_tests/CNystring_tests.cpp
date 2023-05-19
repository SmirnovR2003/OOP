
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "../../../catch2/catch.hpp"
#include "../CMyString/CMyString.h"
using namespace std;

//проверяет на равенство с учетом длины
bool CheckEquals(const char* s1, const char* s2, size_t length1, size_t length2)
{
	if (length1 != length2) return false;
	
	for (int i = 0; i != length1; i++)
	{
		if (s1[i] != s2[i]) return false;
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

		CHECK(CheckEquals(str1.GetStringData(), "", str1.GetLength(), 0));
		CHECK(CheckEquals(str2.GetStringData(), "", str2.GetLength(), 0));
		CHECK(CheckEquals(str3.GetStringData(), "", str3.GetLength(), 0));
		CHECK(CheckEquals(str4.GetStringData(), "", str4.GetLength(), 0));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");
		CMyString str2("s", 1);
		CMyString str3(string("s"));
		CMyString str4(CMyString("s"));

		CHECK(CheckEquals(str1.GetStringData(), "s", str1.GetLength(), 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", str2.GetLength(), 1));
		CHECK(CheckEquals(str3.GetStringData(), "s", str3.GetLength(), 1));
		CHECK(CheckEquals(str4.GetStringData(), "s", str4.GetLength(), 1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");
		CMyString str2("asd", 3);
		CMyString str3(string("asd"));
		CMyString str4(CMyString("asd"));

		CHECK(CheckEquals(str1.GetStringData(), "asd", str1.GetLength(), 3));
		CHECK(CheckEquals(str2.GetStringData(), "asd", str2.GetLength(), 3));
		CHECK(CheckEquals(str3.GetStringData(), "asd", str3.GetLength(), 3));
		CHECK(CheckEquals(str4.GetStringData(), "asd", str4.GetLength(), 3));
	}
}

SCENARIO("SubString tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		CHECK_THROWS((str1.SubString(0,1)));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");

		CHECK(CheckEquals((str1.SubString(0, 1)).GetStringData(), "s", 1, 1));
		CHECK(CheckEquals((str1.SubString(0, 0)).GetStringData(), "", 0 , 0));
	}

	SECTION("Check with some chars")
	{
		CMyString str1("asd");

		CHECK(CheckEquals((str1.SubString(0, 1)).GetStringData(), "a", 1, 1));
		CHECK(CheckEquals((str1.SubString(1, 1)).GetStringData(), "s", 1, 1));
		CHECK(CheckEquals((str1.SubString(1, 10)).GetStringData(), "sd", 2, 2));
		CHECK(CheckEquals((str1.SubString(1)).GetStringData(), "sd", 2, 2));
		CHECK_THROWS((str1.SubString(3)));
	}
}

SCENARIO("Clear tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		str1.Clear();
		CHECK(CheckEquals( str1.GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");

		str1.Clear();
		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
	}

	SECTION("Check with some chars")
	{
		CMyString str1("asd");

		str1.Clear();
		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
	}
}

SCENARIO("operator=(CMyString const& other) tests")
{
	SECTION("Check with some string")
	{
		CMyString str1("s");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		str1 = str2;
		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "a", 1, 1));

		str1 = str2;
		CHECK(CheckEquals(str1.GetStringData(), "a", 1, 1));
	}

	SECTION("Check with one string")
	{
		CMyString str1("asd");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));

		str1 = str1;
		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
	}
}

SCENARIO("operator+(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "a", 1, 1));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa", 2, 2));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds", 4, 4));
	}
}

SCENARIO("operator+(std::string const& str) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		string str2("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(str2 == "");

		CHECK(CheckEquals((str1 + str2).GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		string str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(str2 == "a");

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa", 2, 2));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		string str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(str2 == "s");

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds", 4, 4));
	}
}

SCENARIO("operator+(const char* other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		const char* str2("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2, "", 0, 0));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "", 0, 0));
	}

	SECTION("Check with nullptr")
	{
		CMyString str1("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));

		CHECK(CheckEquals((str1 + nullptr).GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		const char* str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2, "a", 1, 1));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "sa", 2, 2));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		const char* str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str2, "s", 1, 1));

		CHECK(CheckEquals((str1 + str2).GetStringData(), "asds", 4, 4));
	}
}

SCENARIO("operator+=(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "a", 1, 1));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), "sa", 2, 2));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("s");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));

		str1 += str2;
		CHECK(CheckEquals(str1.GetStringData(), "asds", 4, 4));
	}
}

SCENARIO("operator==(CMyString const& other) tests")
{
	SECTION("Check with empty strings")
	{
		CMyString str1("");
		CMyString str2("");

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK(str1 == str2);
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

		CHECK(str1 == str2);
		CHECK(!(str1 == str3));
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

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

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK(!(str1 != str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

		CHECK(!(str1 != str2));
		CHECK(str1 != str3);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("asd");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

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

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK(!(str1 < str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

		CHECK(!(str1 < str2));
		CHECK(str3 < str1);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");

		CHECK(CheckEquals(str1.GetStringData(), "as", 2, 2));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

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

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK((str1 <= str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

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

		CHECK(CheckEquals(str1.GetStringData(), "as", 2, 2));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

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

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK(!(str1 > str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

		CHECK(!(str1 > str2));
		CHECK(str1 > str3);
	}

	SECTION("Check with some strings")
	{
		CMyString str1("as");
		CMyString str2("asd");
		CMyString str3("ssd");
		CMyString str4("asdd");


		CHECK(CheckEquals(str1.GetStringData(), "as", 2, 2));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

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

		CHECK(CheckEquals(str1.GetStringData(), "", 0, 0));
		CHECK(CheckEquals(str2.GetStringData(), "", 0, 0));

		CHECK((str1 >= str2));
	}

	SECTION("Check with one char strings")
	{
		CMyString str1("s");
		CMyString str2("s");
		CMyString str3("a");

		CHECK(CheckEquals(str1.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str2.GetStringData(), "s", 1, 1));
		CHECK(CheckEquals(str3.GetStringData(), "a", 1, 1));

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

		CHECK(CheckEquals(str1.GetStringData(), "as", 2, 2));
		CHECK(CheckEquals(str2.GetStringData(), "asd", 3, 3));
		CHECK(CheckEquals(str3.GetStringData(), "ssd", 3, 3));
		CHECK(CheckEquals(str4.GetStringData(), "asdd", 4, 4));

		CHECK(!(str1 >= str2));
		CHECK((str3 >= str2));
		CHECK((str3 >= str4));
		CHECK((str3 >= str3));
	}
}


//CIterator tests

SCENARIO("operator*() and CIterator begin() tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it = str1.begin();

		CHECK(*it == '\0');
	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it = str1.begin();

		CHECK(*it == 's');
	}
}

SCENARIO("CIterator end() tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it = str1.end();

		CHECK(*it == '\0');
	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it = str1.end();

		CHECK(*it == '\0');
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it = str1.end();

		CHECK(*it == '\0');
	}
}

SCENARIO("CIterator operator++() and CIterator operator++(int) tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it = str1.begin();
		CHECK_THROWS(++it);

		it = str1.begin();
		CHECK_THROWS(it++);
	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it = str1.begin();
		CHECK(*it == 's');

		++it;
		CHECK(*it == '\0');

		it = str1.begin();
		it++;
		CHECK(*it == '\0');
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it = str1.begin();
		CHECK(*it == 'a');
		++it;
		CHECK(*it == 's');
		++it;
		CHECK(*it == 'd');

		it = str1.begin();
		CHECK(*it == 'a');
		it++;
		CHECK(*it == 's');
		it++;
		CHECK(*it == 'd');
	}
}

SCENARIO("CIterator operator--() and CIterator operator--(int) tests")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it = str1.end();
		CHECK_THROWS(--it);

		it = str1.end();
		CHECK_THROWS(it--);
	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it = str1.end();
		CHECK(*it == '\0');

		--it;
		CHECK(*it == 's');

		it = str1.end();
		it--;
		CHECK(*it == 's');
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it = str1.end();
		CHECK(*it == '\0');
		--it;
		CHECK(*it == 'd');
		--it;
		CHECK(*it == 's');
		--it;
		CHECK(*it == 'a');

		it = str1.end();
		CHECK(*it == '\0');
		it--;
		CHECK(*it == 'd');
		it--;
		CHECK(*it == 's');
		it--;
		CHECK(*it == 'a');
	}
}

SCENARIO("CIterator operator+(int count, CIterator other)")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it = str1.begin();
		CHECK(*(it + 0) == '\0');

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it = str1.begin();
		CHECK(*it == 's');

		it = it + 1;
		CHECK(*it == '\0');
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it = str1.begin();

		it = it + 2;
		CHECK(*it == 'd');
	}
}

SCENARIO("size_t operator-(const CIterator& other1, const CIterator& other2)")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(it2 - it1 == 0);

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(it2 - it1 == 1);
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(it2 - it1 == 3);
	}
}

SCENARIO("bool operator==")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(it2 == it1);

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it2 == it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it2 == it1));
	}
}

SCENARIO("bool operator!=")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it2 != it1));

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it2 != it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it2 != it1));
	}
}

SCENARIO("bool operator<")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it2 < it1));

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it1 < it2));
		CHECK(!(it2 < it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it1 < it2));
		CHECK(!(it2 < it1));
	}
}

SCENARIO("bool operator<=")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it2 <= it1));

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it1 <= it2));
		CHECK(!(it2 <= it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it1 <= it2));
		CHECK(!(it2 <= it1));
	}
}

SCENARIO("bool operator>")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it2 > it1));
		CHECK(!(it1 > it2));

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it1 > it2));
		CHECK((it2 > it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it1 > it2));
		CHECK((it2 > it1));
	}
}

SCENARIO("bool operator>=")
{
	SECTION("Check with empty string")
	{
		CMyString str1("");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK((it2 >= it1));

	}

	SECTION("Check with one char string")
	{
		CMyString str1("s");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it1 >= it2));
		CHECK((it2 >= it1));
	}

	SECTION("Check with some string")
	{
		CMyString str1("asd");

		auto it1 = str1.begin();
		auto it2 = str1.end();

		CHECK(!(it1 >= it2));
		CHECK((it2 >= it1));
	}
}