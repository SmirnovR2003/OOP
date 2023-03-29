#include "ParseURL.h"
#include <string>
#include <regex>
#include <iostream>

using namespace std;

const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const int DEFAULT_FTP_PORT = 21;

vector<string> Split(const string& str, const string& delimetr) {
    const auto r = regex(delimetr);
    return vector<string>
    {
        sregex_token_iterator(str.begin(), str.end(), r, -1),
            sregex_token_iterator()
    };
}

bool checkProtocol(string& prot, Protocol& protocol)
{
    for (auto& s : prot) s = tolower(s);
    //вынести в константы
    if (prot == "http") protocol = Protocol::HTTP;
    else if (prot == "https") protocol = Protocol::HTTPS;
    else if (prot == "ftp") protocol = Protocol::FTP;
    else return false;
    return true;
}

bool checkPort(const vector<string>& str3, Protocol protocol, int& port)
{
    try
    {
        string s = str3[str3.size() - 1];
        port = stoi(s);
    }
    catch (invalid_argument e)
    {
        switch (protocol)
        {
            case(Protocol::HTTP): port = DEFAULT_HTTP_PORT; break;
            case(Protocol::HTTPS): port = DEFAULT_HTTPS_PORT; break;
            case(Protocol::FTP): port = DEFAULT_FTP_PORT; break;
            default: break;
        }
    }
    
    if (port > 0) return true;
    else return false;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    if (url.empty()) return false;

    const auto r = regex(R"((ftp|https?)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)", std::regex_constants::icase);
    smatch matches;

    if(!regex_search(url, matches, r)) return false;

    string protocolString = matches[1].str();
    string hostString = matches[2].str();
    string portString = matches[3].str();
    string documentString = matches[4].str();

    vector<string> str1 = Split(url, "://");
    if (str1.size() != 2) return false;

    if (!checkProtocol(protocolString, protocol)) return false;

    vector<string> str2 = Split(str1[1], "/");
    if (str2.size() < 1 || str2[0] == "") return false;

    vector<string> str3 = Split(str2[0], ":");

    //проверка хоста
    if (str3[0] != "") host = str3[0];
    else return false;

    if(!checkPort(str3, protocol, port)) return false;

    //проверка документа
    for (int i = 1; i < str2.size(); i++)
    {
        document += str2[i] + "/";
    }
    if(document.size() > 0) document.resize(document.size() - 1);

	return true;
}
