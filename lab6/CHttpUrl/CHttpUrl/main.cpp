// CHttpUrl.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <limits>
#include"CHttpUrl.h"
#include"CUrlParsingError.h"
using namespace std;

ostream& operator<<(ostream& os, Protocol protocol)
{
	if (Protocol::HTTP == protocol)
	{
		os << "http";
	}
	else if (Protocol::HTTPS == protocol)
	{
		os << "https";
	}
	return os;
}

void PrintInfo(const CHttpUrl& url)
{
	cout << url.GetURL() << endl;
	cout << "\tprotocol:" << url.GetProtocol() << endl;
	cout << "\tdomain:" << url.GetDomain() << endl;
	cout << "\tport:" << url.GetPort() << endl;
	cout << "\tdocument:" << url.GetDocument() << endl;
}

int main()
{
	string stringUrl;

	while (cin >> stringUrl)
	{
		try
		{
			CHttpUrl url(stringUrl);
			PrintInfo(url);
		}
		catch(const CUrlParsingError& ex)
		{
			cout << ex.what() << endl;
		}
	}
}
