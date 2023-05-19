
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "../../../catch2/catch.hpp"
#include "../CHttpUrl/CHttpUrl.h"
#include "../CHttpUrl/CUrlParsingError.h"
using namespace std;

SCENARIO("Constructors tests")
{
	SECTION("Check with empty url")
	{
		CHECK_THROWS_AS(CHttpUrl(""), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("", "", Protocol::HTTP), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 1), CUrlParsingError);
	}

	SECTION("Check with uncorrect protocol")
	{
		CHECK_THROWS_AS(CHttpUrl("htps://a"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("ht://a"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("ttps://a"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("ftp://a"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("://a"), CUrlParsingError);
	}

	SECTION("Check with uncorrect domain")
	{
		CHECK_THROWS_AS(CHttpUrl("https://:123/ad"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("https://:/ad"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("?", "", Protocol::HTTP), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl(":", "", Protocol::HTTP, 1), CUrlParsingError);
	}
}

SCENARIO("GetDomain function tests")
{
	SECTION("Check with one char domain")
	{
		CHECK(CHttpUrl("https://s:123/ad").GetDomain() == "s");
		CHECK(CHttpUrl("s", "", Protocol::HTTP).GetDomain() == "s");
		CHECK(CHttpUrl("s", "", Protocol::HTTP, 0).GetDomain() == "s");
	}

	SECTION("Check with any chars domain")
	{
		CHECK(CHttpUrl("https://sasd:123/asds").GetDomain() == "sasd");
		CHECK(CHttpUrl("sasd", "", Protocol::HTTP).GetDomain() == "sasd");
		CHECK(CHttpUrl("sasd", "", Protocol::HTTP, 1).GetDomain() == "sasd");
	}
}

SCENARIO("GetDocument function tests")
{
	SECTION("Check with empty document")
	{
		CHECK(CHttpUrl("https://s:123").GetDocument() == "/");
		CHECK(CHttpUrl("s", "", Protocol::HTTP).GetDocument() == "/");
		CHECK(CHttpUrl("s", "", Protocol::HTTP, 0).GetDocument() == "/");
	}

	SECTION("Check with one char document")
	{
		CHECK(CHttpUrl("https://s:123/r").GetDocument() == "/r");
		CHECK(CHttpUrl("s", "r", Protocol::HTTP).GetDocument() == "/r");
		CHECK(CHttpUrl("s", "r", Protocol::HTTP, 0).GetDocument() == "/r");
	}

	SECTION("Check with any chars document")
	{
		CHECK(CHttpUrl("https://sasd:123/zxc").GetDocument() == "/zxc");
		CHECK(CHttpUrl("sasd", "zxc", Protocol::HTTP).GetDocument() == "/zxc");
		CHECK(CHttpUrl("sasd", "zxc", Protocol::HTTP, 1).GetDocument() == "/zxc");
	}
}

SCENARIO("GetProtocol function tests")
{
	SECTION("Check with http protocol")
	{
		CHECK(CHttpUrl("http://s:123").GetProtocol() == Protocol::HTTP);
		CHECK(CHttpUrl("s", "", Protocol::HTTP).GetProtocol() == Protocol::HTTP);
		CHECK(CHttpUrl("s", "", Protocol::HTTP, 0).GetProtocol() == Protocol::HTTP);
	}

	SECTION("Check with https protocol")
	{
		CHECK(CHttpUrl("https://s:123/r").GetProtocol() == Protocol::HTTPS);
		CHECK(CHttpUrl("s", "r", Protocol::HTTPS).GetProtocol() == Protocol::HTTPS);
		CHECK(CHttpUrl("s", "r", Protocol::HTTPS, 0).GetProtocol() == Protocol::HTTPS);
	}
}

SCENARIO("GetPort function tests")
{
	SECTION("Check with unspecified port")
	{
		CHECK(CHttpUrl("http://s/r").GetPort() == 80);
		CHECK(CHttpUrl("https://s/r").GetPort() == 443);
		CHECK(CHttpUrl("s", "r", Protocol::HTTPS).GetPort() == 443);
		CHECK(CHttpUrl("s", "r", Protocol::HTTP).GetPort() == 80);
	}

	SECTION("Check with specified port")
	{
		CHECK(CHttpUrl("https://s:123/r").GetPort() == 123);
		CHECK(CHttpUrl("s", "r", Protocol::HTTPS, 123).GetPort() == 123);
		CHECK(CHttpUrl("s", "r", Protocol::HTTP, 123).GetPort() == 123);
	}
}

SCENARIO("GetUrl function tests")
{
	CHECK(CHttpUrl("http://s/r").GetURL() == "http://s/r");
	CHECK(CHttpUrl("https://s:123/r").GetURL() == "https://s/r");
	CHECK(CHttpUrl("https://s:123").GetURL() == "https://s/");
	CHECK(CHttpUrl("http://s:123").GetURL() == "http://s/");

}
