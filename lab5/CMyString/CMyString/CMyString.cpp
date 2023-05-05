#include "CMyString.h"
#include<string.h>
#include <stdexcept> 

void DeleteMyString(MyChar* ch)
{
	if (!ch) return;
	DeleteMyString(ch->MyCharPtr);
	delete ch;
}

CMyString::CMyString()
	: m_str(new char[1])
	, m_lenght(0)
{
	m_str[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: m_str(new char[strlen(pString)+1])
	, m_lenght(strlen(pString))
{
	memmove(m_str, pString, m_lenght);
	m_str[m_lenght] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
	: m_str(new char[length+1])
	, m_lenght(length)
{
	memmove(m_str, pString, length);
	m_str[length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: m_str(new char[other.m_lenght+1])
	, m_lenght(other.m_lenght)
{
	memmove(m_str, other.m_str, m_lenght);
	m_str[m_lenght] = '\0';
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_str(other.m_str)
	, m_lenght(other.m_lenght)
{
	other.m_str = NULL;
	other.m_lenght = 0;
}

CMyString::CMyString(std::string const& stlString)
	: m_str(new char[stlString.size()+1])
	, m_lenght(stlString.size())
{
	const char* s = stlString.c_str();

	memmove(m_str, s, m_lenght);
	m_str[m_lenght] = '\0';
}

CMyString::~CMyString()
{
	if(m_str)delete[] m_str;
}

size_t CMyString::GetLength() const
{
	return m_lenght;
}

const char* CMyString::GetStringData() const
{
	return m_str;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_lenght)
	{
		return "";
	}

	if ((m_lenght < length) || (start + length > m_lenght))
	{
		length = m_lenght - start;
	}

	char* res = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		res[i] = *(m_str + start + i);

	}

	res[length] = '\0';
	return res;
}

void CMyString::Clear()
{
	delete[] m_str;

	m_str = new char[1];
	m_str[0] = '\0';
	m_lenght = 0;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);

		std::swap(m_str, tmpCopy.m_str);
		std::swap(m_lenght, tmpCopy.m_lenght);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		if (m_str)
		{
			delete[] m_str;
		}

		m_str = other.m_str;
		m_lenght = other.m_lenght;

		other.m_str = NULL;
		other.m_lenght = 0;
	}
	return *this;
}


CMyString CMyString::operator+(CMyString const& other) const
{
	size_t bufferSize = strlen(m_str) + strlen(other.m_str) + 1;
	char* concatString = new char[bufferSize];

	memmove(concatString, m_str, strlen(m_str)+1);
	strcat_s(concatString, bufferSize, other.m_str);

	return CMyString(concatString, bufferSize-1);
}

CMyString CMyString::operator+(std::string const& str) const
{
	size_t bufferSize = strlen(m_str) + str.size() + 1;
	char* concatString = new char[bufferSize];

	memmove(concatString, m_str, strlen(m_str) + 1);
	strcat_s(concatString, bufferSize, str.c_str());

	return CMyString(concatString, bufferSize-1);
}

CMyString CMyString::operator+(const char* other) const
{
	size_t bufferSize = strlen(m_str) + strlen(other) + 1;
	char* concatString = new char[bufferSize];

	memmove(concatString, m_str, strlen(m_str) + 1);
	strcat_s(concatString, bufferSize, other);

	return CMyString(concatString, bufferSize-1);
}

CMyString CMyString::operator+=(CMyString const& other)
{
	size_t bufferSize = strlen(m_str) + strlen(other.m_str) + 1;
	char* concatString = new char[bufferSize];

	memmove(concatString, m_str, m_lenght+1);
	strcat_s(concatString, bufferSize, other.m_str);

	delete[] m_str;
	memmove(m_str, concatString, bufferSize);

	m_str = concatString;
	m_lenght = bufferSize-1;

	return *this;
}

bool CMyString::operator==(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) == 0;
}

bool CMyString::operator!=(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) != 0;
}

bool CMyString::operator<(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) < 0;
}

bool CMyString::operator<=(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) <= 0;
}

bool CMyString::operator>(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) > 0;
}

bool CMyString::operator>=(CMyString const& other) const
{
	return strcmp(m_str, other.m_str) >= 0;
}

const char& CMyString::operator[](const size_t index) const
{
	if (index >= m_lenght) throw new std::out_of_range("out of range");
	return m_str[index];

}

char& CMyString::operator[](const size_t index)
{
	if (index >= m_lenght) throw new std::out_of_range("out of range");
	return m_str[index];
}

CMyString::CIterator CMyString::begin()
{
	return CIterator(m_str);
}

const CMyString::CIterator CMyString::end()const
{
	return CIterator(m_str + m_lenght);
}

CMyString::CIterator::CIterator(char* ch)
	:m_curr(ch)
{
}

const char CMyString::CIterator::operator*() const
{
	return *m_curr;
}

char& CMyString::CIterator::operator*() 
{
	return *m_curr;
}

CMyString::CIterator CMyString::CIterator::operator++()
{
	m_curr++;
	return *this;
}

CMyString::CIterator CMyString::CIterator::operator++(int)
{
	CMyString::CIterator Temp(*this);
	++(*this);
	return Temp;
}

CMyString::CIterator CMyString::CIterator::operator--()
{
	m_curr--;
	return *this;
}

CMyString::CIterator  CMyString::CIterator::operator--(int)
{
	CMyString::CIterator Temp(*this);
	--(*this);
	return Temp;
}

CMyString::CIterator CMyString::CIterator::operator+(int number)
{
	m_curr = m_curr + number;
	return *this;
}

CMyString::CIterator operator+(int count, CMyString::CIterator other)
{
	return count + other.m_curr;
}

int CMyString::CIterator::operator-(const CIterator& other)
{
	return m_curr - other.m_curr;
}

bool CMyString::CIterator::operator==(const CIterator& other)
{
	return m_curr == other.m_curr;
}

bool CMyString::CIterator::operator!=(const CIterator& other)
{
	return m_curr != other.m_curr;
}

