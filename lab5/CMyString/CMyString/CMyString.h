#pragma once
#include <string>
#include <iterator>
#include <iostream>


class CMyString
{
public:
	class CIterator;
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
	//�������� friend
	CMyString& operator=(CMyString const& other);

	CMyString& operator=(CMyString&& other)noexcept;

	CMyString operator+(CMyString const& other)const;

	CMyString operator+(std::string const& str)const;

	CMyString operator+(const char* other)const;

	CMyString operator+=(CMyString const& other);

	//��� ������ �� const � �� const
	class CConstIterator //�������� ��� ������ ��������
	{
		friend CMyString;

		CConstIterator(char* curr, char* first, char* last);

	public:

		typedef char iterator_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef const iterator_type& reference;
		typedef const iterator_type* pointer;


		CConstIterator() = default;

		reference operator*();

		 CConstIterator operator++();

		 CConstIterator operator++(int);

		 //���������� ������
		 //������
		 CConstIterator operator=(const CConstIterator& other);

		 CConstIterator operator--();

		 CConstIterator operator--(int);

		 //�� size_t � ptrdiff_t
		 friend CConstIterator operator+(size_t count, const CConstIterator& other1);

		 CConstIterator operator+(size_t number)const;

		//ptrdiff_t
		 friend difference_type operator-(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator==(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator!=(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator<(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator<=(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator>(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator>=(const CConstIterator& other1, const CConstIterator& other2);

		 //ptrdiff_t
		 reference operator[](size_t number);

	private:
		iterator_type* m_curr = nullptr;

		iterator_type* m_first = nullptr;

		iterator_type* m_last = nullptr;
	};

	class CIterator : public CConstIterator //�������� ��� ������ ��������
	{
		friend CMyString;

		CIterator(char* curr, char* first, char* last);

	public:

		typedef char iterator_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

		CIterator() = default;

		reference operator*()const;

		CIterator operator++();

		CIterator operator++(int);

		CIterator operator=(const CIterator& other);

		CIterator operator--();

		CIterator operator--(int);

		friend CIterator operator+(size_t count, const CIterator& other1);

		CIterator operator+(size_t number)const;

		CIterator operator-(size_t number)const;

		//ptrdiff_t
		friend difference_type operator-(const CIterator& other1, const CIterator& other2);

		friend bool operator==(const CIterator& other1, const CIterator& other2);

		friend bool operator!=(const CIterator& other1, const CIterator& other2);

		friend bool operator<(const CIterator& other1, const CIterator& other2);

		friend bool operator<=(const CIterator& other1, const CIterator& other2);

		friend bool operator>(const CIterator& other1, const CIterator& other2);

		friend bool operator>=(const CIterator& other1, const CIterator& other2);

		reference operator[](size_t number);

	private:
		iterator_type* m_curr = nullptr;

		iterator_type* m_first = nullptr;

		iterator_type* m_last = nullptr;
	};

	CIterator begin();

	CIterator end();

	CConstIterator begin()const;

	CConstIterator end()const;

private:
	CMyString(char* data, size_t length, size_t capacity);

	char* m_str = nullptr;

	size_t m_length = 0;

	size_t m_capacity = 0;
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



