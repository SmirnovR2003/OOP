#include "CMyString.h"
#include<string.h>
#include <stdexcept> 

const char* STRING_WITH_ZERO_CHAR = "\0";

//аналог strcmp, но сравнивает с учетом длины
int strcmpWithLengths(const char* s1, const char* s2, size_t length1, size_t length2)
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
}

CMyString ConcatStrings(const char* s1, const char* s2, size_t length1, size_t length2)
{
	size_t bufferSize = length1 + length2 + 1;
	char* concatString = (new char[bufferSize]);

	memcpy(concatString, s1, length1 + 1);
	memcpy(concatString + length1, s2, length2 + 1);

	return concatString;
}

CMyString::CMyString()
	: m_str(new char[1])
	, m_length(0)
	, m_capacity(0)
{
	m_str[0] = '\0';
}

//делегирующий конструктор
CMyString::CMyString(const char* pString)
//вычисление дважды length
	: CMyString(pString, strlen(pString))
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
	: CMyString(other.m_str, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other.m_str, other.m_length)
{
	other.m_str = nullptr;
	other.m_length = 0;
	other.m_capacity = 0;
}

CMyString::CMyString(std::string const& stlString)
	: m_str(new char[stlString.size()+1])
	, m_length(stlString.size())
{
	const char* s = stlString.c_str();

	memcpy(m_str, s, m_length);
	m_str[m_length] = '\0';
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

	memcpy(res.m_str, m_str + start, length);
	
	return res;
}

void CMyString::Clear()
{
	//сделать capacity
	m_length = 0;
	m_str[0] = '\0';
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
		if (other.m_str)
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
	return ConcatStrings(m_str, other.m_str, m_length, other.m_length);
}

CMyString CMyString::operator+(std::string const& str) const
{
	return ConcatStrings(m_str, str.c_str(), m_length,str.size());
}

CMyString CMyString::operator+(const char* other) const
{
	return ConcatStrings(m_str, other, m_length, strlen(other));
}

CMyString CMyString::operator+=(CMyString const& other)
{
	size_t bufferSize = m_length + other.m_length + 1;
	if (bufferSize < m_capacity)
	{
		memcpy(m_str + m_length, other.m_str, other.m_length + 1);
	}
	else
	{
		char* concatString = new char[bufferSize];

		memcpy(concatString, m_str, m_length + 1);
		memcpy(concatString + m_length, other.m_str, other.m_length + 1);

		delete[] m_str;
		m_str = concatString;
		m_capacity = bufferSize - 1;
	}
	m_length = bufferSize-1;

	return *this;
}

bool CMyString::operator==(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) == 0;
}

bool CMyString::operator!=(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) != 0;
}

bool CMyString::operator<(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) < 0;
}

bool CMyString::operator<=(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) <= 0;
}

bool CMyString::operator>(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) > 0;
}

bool CMyString::operator>=(CMyString const& other) const
{
	return strcmpWithLengths(m_str, other.m_str, m_length, other.m_length) >= 0;
}

CMyString::CConstIterator CMyString::begin()const
{
	return CConstIterator(m_str, m_str, m_str + m_length);
}

CMyString::CConstIterator CMyString::end()const
{
	return CConstIterator(m_str + m_length, m_str, m_str + m_length);
}

CMyString::CIterator CMyString::begin()
{
	return CIterator(m_str, m_str, m_str + m_length);
}

CMyString::CIterator CMyString::end()
{
	return CIterator(m_str + m_length, m_str, m_str + m_length);
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

CMyString::CIterator::reference CMyString::CIterator::operator*()
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

CMyString::CConstIterator CMyString::CConstIterator::operator=(const CConstIterator& other)
{
	m_curr = other.m_curr;
	m_first = other.m_first;
	m_last = other.m_last;
	return *this;
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

CMyString::CConstIterator operator+(size_t count, const CMyString::CConstIterator& other1)
{
	if (other1.m_curr + count > other1.m_last)throw std::out_of_range("out of range");
	CMyString::CConstIterator it(other1.m_curr + count, other1.m_first, other1.m_last);
	return it;
}

CMyString::CConstIterator CMyString::CConstIterator::operator+(size_t number) const
{
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

CMyString::CConstIterator::reference CMyString::CConstIterator::operator[](size_t number)
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

CMyString::CIterator CMyString::CIterator::operator=(const CIterator& other)
{
	m_curr = other.m_curr;
	m_first = other.m_first;
	m_last = other.m_last;
	return *this;
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

CMyString::CIterator operator+(size_t count, const CMyString::CIterator& other1)
{
	if (other1.m_curr + count > other1.m_last)throw std::out_of_range("out of range");
	CMyString::CIterator it(other1.m_curr + count, other1.m_first, other1.m_last);
	return it;
}

CMyString::CIterator CMyString::CIterator::operator+(size_t number) const
{
	if (m_curr + number > m_last)throw std::out_of_range("out of range");
	CMyString::CIterator it(m_curr + number, m_first, m_last);
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

CMyString::CIterator::reference CMyString::CIterator::operator[](int number)
{
	if (m_curr + number < m_first || m_curr + number >= m_last) throw std::out_of_range("out of range");
	return *(m_curr + number);
}