// HTMLDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTMLDecode/HTMLDecode.h"
#include "string"

using namespace std;

SCENARIO("HtmlDecode function tests")
{
	SECTION("Check with empty string")
	{
		string html = "";
		CHECK(HtmlDecode(html) == html);
	}

	SECTION("Check without replacing")
	{
		string html = "asdf qwerty123";
		CHECK(HtmlDecode(html) == html);
	}

	SECTION("Check with replace in the center of string")
	{
		string html = "asdf &gt;qwerty123";
		string decodedHtml = R"(asdf >qwerty123)";
		CHECK(HtmlDecode(html) == decodedHtml);
	}

	SECTION("Check with replace in the start and end of string")
	{
		string html = "&quot;asdf qwerty123&quot;";
		string decodedHtml = R"("asdf qwerty123")";
		CHECK(HtmlDecode(html) == decodedHtml);
	}

	SECTION("Check with all replaces variations")
	{
		string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		string decodedHtml = R"(Cat <says> "Meow". M&M's)";
		CHECK(HtmlDecode(html) == decodedHtml);
	}
}