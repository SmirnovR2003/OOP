// ParseURL_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/ParseURL.h"

using namespace std;

SCENARIO("ParseURL function tests")
{
	SECTION("Check with norm url")
	{
		string url = R"(Http://www.mysite.com/docs/document1.html?page=30&lang=en#title)", host, document;
		int port;
		Protocol protocol;
		bool isValid = ParseURL(url, protocol, port, host, document);
		CHECK(isValid);
		CHECK(protocol == Protocol::HTTP);
		CHECK(port == 80);
		CHECK(host == "www.mysite.com");
		CHECK(document == "docs/document1.html?page=30&lang=en#title");

		url = R"(ftP://www.mysite.com)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(isValid);
		CHECK(protocol == Protocol::FTP);
		CHECK(port == 21);
		CHECK(host == "www.mysite.com");
		CHECK(document == "");

		url = R"(FTP://www:1234)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(isValid);
		CHECK(protocol == Protocol::FTP);
		CHECK(port == 1234);
		CHECK(host == "www");
		CHECK(document == "");

		url = R"(HtTpS://www.mysite.com/docs/document1.html?page=30&lang=en#title)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(isValid);
		CHECK(protocol == Protocol::HTTPS);
		CHECK(port == 443);
		CHECK(host == "www.mysite.com");
		CHECK(document == "docs/document1.html?page=30&lang=en#title");
	}

	SECTION("Check with not norm protocol")
	{
		string url = R"(hsttp://www.mysite.com:13/docs/document1.html?page=30&lang=en#title)", host, document;
		int port;
		Protocol protocol;
		bool isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);

		url = R"(ftps://www.mysite.com:13/docs/document1.html?page=30&lang=en#title)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);

		url = R"(htps://www.mysite.com:13/docs/document1.html?page=30&lang=en#title)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);
	}

	SECTION("Check with not norm host")
	{
		string url = R"(http://:13/docs/document1.html?page=30&lang=en#title)", host, document;
		int port;
		Protocol protocol;
		bool isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);

		url = R"(ftp://:13www.mysite.com/docs/document1.html?page=30&lang=en#title)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);

		url = R"(htps://ww:13w.mysite.com/docs/document1.html?page=30&lang=en#title)";
		document = "";
		isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);
	}

	SECTION("Check with empty url")
	{
		string url = R"()", host, document;
		int port;
		Protocol protocol;
		bool isValid = ParseURL(url, protocol, port, host, document);
		CHECK(!isValid);
	}
}