#pragma once
#include<stdexcept>


class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string message);

	std::string GetData()const;
private:
	std::string m_message;
};

