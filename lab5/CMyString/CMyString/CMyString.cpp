#include "CMyString.h"
#include<string.h>
#include <stdexcept> 

using namespace std;


char ZERO_CHAR = '\0';

char* STRING_WITH_ZERO_CHAR = &ZERO_CHAR;

//аналог strcmp, но сравнивает с учетом длины
int StrcmpWithLengths(const char* s1, const char* s2, size_t length1, size_t length2)
{
	size_t minLength = std::min(length1, length2);

	for (size_t i = 0; i != minLength; i++)
	{
		if (s1[i] < s2[i])
		{
			return -1;
		}
		else if (s1[i] > s2[i])
		{
			return 1;
		}
	}

	if (length1 == length2)
	{
		return 0;
	}
	else if (length1 > length2)
	{
		return 1;
	}
	else 
	{
		return -1;
	}
}/*
CMyString(char* data, std::ptrdiff_t length, std::ptrdiff_t capacity)
{

};*/

CMyString ConcatStrings(const char* s1, const char* s2, size_t length1, size_t length2)
{
	size_t bufferSize = length1 + length2 + 1;
	char* concatString = (new char[bufferSize]);

	memcpy(concatString, s1, length1);
	memcpy(concatString + length1, s2, length2);
	concatString[bufferSize] = '\0';

	CMyString temp(concatString, bufferSize - 1);//утечка памяти если выбросится исключение

	delete[] concatString;

	return temp; // симво '\0'
}

CMyString::CMyString()
	: m_str(new char[1])
	, m_length(0)
	, m_capacity(0)
{
	m_str[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString ? pString : STRING_WITH_ZERO_CHAR, pString ? strlen(pString) : 0)
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_str(new char[length+1])
	, m_length(length)
	, m_capacity(length)
{
	memcpy(m_str, pString, length);
	m_str[length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_str ? other.m_str : STRING_WITH_ZERO_CHAR, other.m_str ? other.m_length : 0)
	
{
}

CMyString::CMyString(CMyString&& other) noexcept
{
	if (&other != this)
	{
		std::swap(m_str, other.m_str);
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);

		if (other.m_str != STRING_WITH_ZERO_CHAR)
		{
			delete[] other.m_str;
			other.m_str = nullptr;
			other.m_length = 0;
			other.m_capacity = 0;
		}
		
	}
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	if(m_str != STRING_WITH_ZERO_CHAR) delete[] m_str;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	//создать массив ['\0'] и возвращать его
	return m_str ? m_str : STRING_WITH_ZERO_CHAR;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)//исключуние
	{
		throw std::out_of_range("out of range");
	}

	if ((m_length < length) || (start + length > m_length))
	{
		length = m_length - start;
	}
	CMyString res(new char[length + 1], length);

	memcpy(res.m_str, m_str + start, length);//nullptr
	
	return res;
}

void CMyString::Clear()
{
	//сделать capacity
	m_length = 0;
	if(m_str) m_str[0] = '\0';//разыименнование nullptr
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (&other != this)
	{
		CMyString tmpCopy(other);

		std::swap(m_str, tmpCopy.m_str);
		std::swap(m_length, tmpCopy.m_length);
		std::swap(m_capacity, tmpCopy.m_capacity);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		std::swap(m_str, other.m_str);
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);

		//nullptr
		if (other.m_str != STRING_WITH_ZERO_CHAR)
		{
			delete[]m_str;
			other.m_str = nullptr;
		}
		other.m_length = 0;
		other.m_capacity = 0;
	}
	return *this;
}
//дублирование кода
CMyString CMyString::operator+(CMyString const& other) const
{
	return ConcatStrings(m_str ? m_str : STRING_WITH_ZERO_CHAR, other.m_str ? other.m_str : STRING_WITH_ZERO_CHAR, m_length, other.m_length);
}

CMyString CMyString::operator+(std::string const& str) const
{
	return ConcatStrings(m_str ? m_str : STRING_WITH_ZERO_CHAR, str.c_str(), m_length,str.size());
}

CMyString CMyString::operator+(const char* other) const
{
	return ConcatStrings(m_str ? m_str : STRING_WITH_ZERO_CHAR, other ? other : STRING_WITH_ZERO_CHAR, m_length, other ? strlen(other) : 0);
}

CMyString CMyString::operator+=(CMyString const& other)
{
	size_t bufferSize = m_length + other.m_length + 1;
	if (bufferSize < m_capacity)
	{
		if (m_str == STRING_WITH_ZERO_CHAR)
		{
			m_str = new char[other.m_length];
		}
		memcpy(m_str + m_length, other.m_str ? other.m_str : STRING_WITH_ZERO_CHAR, other.m_str ? other.m_length + 1 : 1);


	}
	else
	{
		char* concatString = new char[bufferSize];

		memcpy(concatString, m_str ? m_str : STRING_WITH_ZERO_CHAR, m_length + 1);
		memcpy(concatString + m_length, other.m_str ? other.m_str : STRING_WITH_ZERO_CHAR, other.m_length + 1);

		if(m_str!=STRING_WITH_ZERO_CHAR) delete[] m_str;
		m_str = concatString;
		m_capacity = bufferSize - 1;
	}
	m_length = bufferSize-1;

	return *this;
}

CMyString::CConstIterator CMyString::begin()const
{
	return CConstIterator(m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR);
}

CMyString::CConstIterator CMyString::end()const
{
	return CConstIterator(m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR, m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR);
}

CMyString::CIterator CMyString::begin()
{
	return CIterator(m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR);
}

CMyString::CIterator CMyString::end()
{
	return CIterator(m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR, m_str ? m_str : STRING_WITH_ZERO_CHAR, m_str ? m_str + m_length : STRING_WITH_ZERO_CHAR);
}

CMyString::CConstIterator::CConstIterator(char* curr, char* first, char* last)
	:m_curr(curr)
	, m_first(first)
	, m_last(last)
{
}

CMyString::CIterator::CIterator(char* curr, char* first, char* last)
	:m_curr(curr)
	, m_first(first)
	, m_last(last)
{
}

CMyString::CIterator::reference CMyString::CIterator::operator*()const
{
	return *m_curr;
}

CMyString::CConstIterator::reference CMyString::CConstIterator::operator*()
{
	return *m_curr;
}

CMyString::CConstIterator CMyString::CConstIterator::operator++()
{
	if (m_curr == m_last)throw std::out_of_range("out of range");
	m_curr++;
	return *this;
}

CMyString::CConstIterator CMyString::CConstIterator::operator++(int)
{
	if (m_curr == m_last)throw std::out_of_range("out of range");
	CMyString::CConstIterator Temp(*this);
	++(*this);
	return Temp;
}

CMyString::CConstIterator CMyString::CConstIterator::operator--()
{
	if (m_curr == m_first)throw std::out_of_range("out of range");
	m_curr--;
	return *this;
}

CMyString::CConstIterator CMyString::CConstIterator::operator--(int)
{
	if (m_curr == m_first)throw std::out_of_range("out of range");
	CMyString::CConstIterator Temp(*this);
	--(*this);
	return Temp;
}

CMyString::CConstIterator operator+(std::ptrdiff_t count, const CMyString::CConstIterator& other1)
{
	if (other1.m_curr + count > other1.m_last)throw std::out_of_range("out of range");
	CMyString::CConstIterator it(other1.m_curr + count, other1.m_first, other1.m_last);
	return it;
}

CMyString::CConstIterator CMyString::CConstIterator::operator+(std::ptrdiff_t number) const
{
	//переделать без выхода за пределы массива
	if (m_curr + number > m_last)throw std::out_of_range("out of range");
	CMyString::CConstIterator it(m_curr + number, m_first, m_last);
	return it;
}

CMyString::CConstIterator::difference_type operator-(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr - other2.m_curr;
}

bool operator==(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr == other2.m_curr;
}

bool operator!=(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr != other2.m_curr;
}

bool operator<(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr < other2.m_curr;
}

bool operator<=(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr <= other2.m_curr;
}

bool operator>(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr > other2.m_curr;
}

bool operator>=(const CMyString::CConstIterator& other1, const CMyString::CConstIterator& other2)
{
	return other1.m_curr >= other2.m_curr;
}

CMyString::CConstIterator::reference CMyString::CConstIterator::operator[](std::ptrdiff_t number)
{
	if (m_curr + number < m_first || m_curr + number >= m_last) throw std::out_of_range("out of range");
	return *(m_curr + number);
}

CMyString::CIterator CMyString::CIterator::operator++()
{
	if (m_curr == m_last)throw std::out_of_range("out of range");
	m_curr++;
	return *this;
}

CMyString::CIterator CMyString::CIterator::operator++(int)
{
	if (m_curr == m_last)throw std::out_of_range("out of range");
	CMyString::CIterator Temp(*this);
	++(*this);
	return Temp;
}

CMyString::CIterator CMyString::CIterator::operator--()
{
	if (m_curr == m_first)throw std::out_of_range("out of range");
	m_curr--;
	return *this;
}

CMyString::CIterator CMyString::CIterator::operator--(int)
{
	if (m_curr == m_first)throw std::out_of_range("out of range");
	CMyString::CIterator Temp(*this);
	--(*this);
	return Temp;
}

CMyString::CIterator operator+(std::ptrdiff_t count, const CMyString::CIterator& other1)
{
	if (other1.m_curr + count >= other1.m_last)throw std::out_of_range("out of range");
	CMyString::CIterator it(other1.m_curr + count, other1.m_first, other1.m_last);
	return it;
}

CMyString::CIterator CMyString::CIterator::operator+(std::ptrdiff_t number) const
{
	if (m_curr + number >= m_last)throw std::out_of_range("out of range");
	CMyString::CIterator it(m_curr + number, m_first, m_last);
	return it;
}

CMyString::CIterator CMyString::CIterator::operator-(std::ptrdiff_t number) const
{
	if (m_curr - number < m_first) throw std::out_of_range("out of range");
	CMyString::CIterator it(m_curr - number, m_first, m_last);
	return it;
}

CMyString::CIterator::difference_type operator-(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr - other2.m_curr;
}

bool operator==(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr == other2.m_curr;
}

bool operator!=(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr != other2.m_curr;
}

bool operator<(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr < other2.m_curr;
}

bool operator<=(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr <= other2.m_curr;
}

bool operator>(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr > other2.m_curr;
}

bool operator>=(const CMyString::CIterator& other1, const CMyString::CIterator& other2)
{
	return other1.m_curr >= other2.m_curr;
}

CMyString::CIterator::reference CMyString::CIterator::operator[](std::ptrdiff_t number)
{
	if (m_curr + number < m_first || m_curr + number >= m_last) throw std::out_of_range("out of range");
	return *(m_curr + number);
}