#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <algorithm>

using namespace std;

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;


const int MIN_PORT = 1;
const int MAX_PORT = 65535;



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

bool CheckDomainChars(string const& domain)
{
    for (auto ch : domain)
    {
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '.' || ch == '-' || ch == '_' ))
        {
            throw CUrlParsingError("Invalid domain");
        }
    }
    return true;
}
//вренуть bool
bool CheckDomain(string const& domain)
{
    try
    {
        if (!domain.empty() && CheckDomainChars(domain))
        {
            return true;
        }
        else
        {
            throw CUrlParsingError("Invalid domain");
        }
    }
    catch (const CUrlParsingError&)
    {
        throw;
    }
}

Protocol ConvertStringToProtocol( string protocolString)
{
    for_each(protocolString.begin(), protocolString.end(), [](char& ch) {return tolower(ch);});
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
        throw CUrlParsingError("Invalid protocol");
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
//сделать приватным
void CHttpUrl::ParseUrl(std::string const& url)
{
    if (url.empty()) 
    { 
        throw CUrlParsingError("Url is empty");
    }

    const auto r = regex(R"((https?)://([0-9A-Za-z\-.\_]+)(:(\d+)?)?(/[\/0-9A-Za-z\-.\_]*)?)", std::regex_constants::icase);
    smatch matches;

    if (!regex_search(url, matches, r) || matches.suffix().matched || matches.prefix().matched) 
    { 
        throw CUrlParsingError("Invalid url"); 
    }
    
    try
    {
        //присваивать полям
        m_protocol = ConvertStringToProtocol(matches[1].str());
        //убрать CheckDomain
        m_domain = CheckDomain(matches[2].str());

        int port = matches[3].matched ? stoi(matches[4].str()) : GetDefaultPort(m_protocol);
        if (port<MIN_PORT || port > MAX_PORT) 
        { 
            throw CUrlParsingError("Invalid port"); 
        }
        m_port = port;
        //убрать AddSlashToStartOfDocument
         m_document = matches[5].matched ? AddSlashToStartOfDocument(matches[5].str()) : "/";
    }
    catch (const CUrlParsingError&)
    {
        throw;
    }
    catch (const invalid_argument&)
    {
        throw CUrlParsingError("Invalid port");
    }
}

CHttpUrl::CHttpUrl(std::string const& url)
//убрать пустые try catch
    : m_domain()
    , m_document()
    , m_protocol()
    , m_port()
{
    ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
    : m_domain(CheckDomain(domain) ? domain : throw CUrlParsingError("Invalid port"))
    , m_document(AddSlashToStartOfDocument(document))
    , m_protocol(protocol)
    , m_port(GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
    : m_domain(CheckDomain(domain) ? domain : throw CUrlParsingError("Invalid port"))
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
