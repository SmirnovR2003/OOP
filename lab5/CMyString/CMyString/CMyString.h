#pragma once
#include <string>
#include <iterator>
#include <iostream>

struct MyChar
{
	char ch;
	MyChar* MyCharPtr;
};

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	CMyString& operator=(CMyString const& other);

	CMyString& operator=(CMyString&& other)noexcept;

	CMyString operator+(CMyString const& other)const;

	CMyString operator+(std::string const& str)const;

	CMyString operator+(const char* other)const;

	CMyString operator+=(CMyString const& other);

	bool operator==(CMyString const& other)const;

	bool operator!=(CMyString const& other)const;

	bool operator<(CMyString const& other)const;

	bool operator<=(CMyString const& other)const;

	bool operator>(CMyString const& other)const;

	bool operator>=(CMyString const& other)const;

	const char& operator[](const size_t index)const;

	char& operator[](const size_t index);

	class CIterator 
	{
		friend CMyString;

		CIterator(char* ch);

	public:

		CIterator() = default;

		const char operator*()const;

		char& operator*();

		CIterator operator++();

		CIterator operator++(int);

		CIterator operator--();

		CIterator operator--(int);

		friend CIterator operator+(int count, CIterator other);

		CIterator operator+(int number);

		int operator-(const CIterator& other);

		bool operator==(const CIterator& other);

		bool operator!=(const CIterator& other);

	private:
		char* m_curr = nullptr;
	};

	CIterator begin();

	const CIterator end()const;

private:

	char* m_str;

	size_t m_lenght = 0;
};

inline std::ostream& operator<<(std::ostream& stream, CMyString const& other)
{
	stream << other.GetStringData();
	return stream;
}

inline std::istream& operator>>(std::istream& stream, CMyString& other)
{
	char* s = new char;
	if (stream >> s)
	{
		other = s;
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}



