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
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из 
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из 
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength()const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

	// очистка строки (строка становится снова нулевой длины)
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



