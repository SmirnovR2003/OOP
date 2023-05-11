#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string message)
	:m_message(message)
	,invalid_argument(message)
{
}

std::string CUrlParsingError::GetData() const
{
	return m_message;
}
