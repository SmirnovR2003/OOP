#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <algorithm>

using namespace std;

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

unsigned short GetDefaultPort(Protocol prootocl)
{
    return prootocl == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
}

string AddSlashToStartOfDocument(string const& document)
{
    if (document[0] == '/')
    {
        return document;
    }
    else
    {
        return '/' + document;
    }
}

string CheckDomain(string const& domain)
{
    if (domain.size() > 0)
    {
        return domain;
    }
    else
    {
        throw;
    }
}

Protocol ConvertStringToProtocol(const string& protocolString)
{
    for_each(protocolString.begin(), protocolString.end(), tolower);
    if (protocolString == "http")
    {
        return Protocol::HTTP;
    }
    else if (protocolString == "https")
    {
        return Protocol::HTTPS;
    }
    else
    {
        throw;
    }
}

string ConvertProtocolToString(const Protocol& protocolString)
{
    if (protocolString == Protocol::HTTP)
    {
        return "http";
    }
    else 
    {
        return "https";
    }
}

CHttpUrl ParseUrl(std::string const& url)
{
    if (url.empty()) throw ;

    const auto r = regex(R"((https?)://([0-9A-Za-z\-.\_]+)(:(\d+))?(/([0-9A-Za-z\-.\_]*))?)", std::regex_constants::icase);
    smatch matches;

    if (!regex_search(url, matches, r)) throw ;

    Protocol protocol = ConvertStringToProtocol( matches[1].str());

    string domain = CheckDomain(matches[2].str());

    unsigned short port = matches[4].matched ? stoi(matches[4].str()) : GetDefaultPort(protocol);

    string document = matches[5].matched ? AddSlashToStartOfDocument(matches[4].str()) : "/";

    return CHttpUrl(domain, document, protocol, port);
}

CHttpUrl::CHttpUrl(std::string const& url)
    :ParseUrl(url)
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
    : m_domain(CheckDomain(domain))
    , m_document(AddSlashToStartOfDocument(document))
    , m_protocol(protocol)
    , m_port(GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
    : m_domain(CheckDomain(domain))
    , m_document(AddSlashToStartOfDocument(document))
    , m_protocol(protocol)
    , m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	return ConvertProtocolToString(m_protocol) + "://" + m_domain + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
