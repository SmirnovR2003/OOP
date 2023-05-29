#pragma once
#include <string>
#include <iterator>
#include <iostream>

class CMyString
{
public:
	class CIterator;
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из 
	// символьного массива заданной длины
	CMyString(const char* pString, std::size_t length);

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
	std::size_t GetLength()const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(std::size_t start, std::size_t length = SIZE_MAX)const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();
	//добавить friend
	CMyString& operator=(CMyString const& other);

	CMyString& operator=(CMyString&& other)noexcept;

	CMyString operator+(CMyString const& other)const;

	CMyString operator+(std::string const& str)const;

	CMyString operator+(const char* other)const;

	CMyString operator+=(CMyString const& other);

	//два класса дл const и не const
	class CConstIterator //почитать как делать итератор
	{
		friend CMyString;

		CConstIterator(char* curr, char* first, char* last);

	public:

		typedef char iterator_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const iterator_type& reference;
		typedef const iterator_type* pointer;


		CConstIterator() = default;

		reference operator*();

		 CConstIterator operator++();

		 CConstIterator operator++(int);

		 CConstIterator operator--();

		 CConstIterator operator--(int);

		 //не size_t а ptrdiff_t
		 friend CConstIterator operator+(std::ptrdiff_t count, const CConstIterator& other1);

		 CConstIterator operator+(std::ptrdiff_t number)const;

		//ptrdiff_t
		 friend difference_type operator-(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator==(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator!=(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator<(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator<=(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator>(const CConstIterator& other1, const CConstIterator& other2);

		 friend bool operator>=(const CConstIterator& other1, const CConstIterator& other2);

		 //ptrdiff_t
		 reference operator[](std::ptrdiff_t number);

	private:
		iterator_type* m_curr = nullptr;

		iterator_type* m_first = nullptr;

		iterator_type* m_last = nullptr;
	};

	class CIterator : public CConstIterator 
	{
		friend CMyString;

		CIterator(char* curr, char* first, char* last);

	public:

		typedef char iterator_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef std::ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

		CIterator() = default;

		reference operator*()const;

		CIterator& operator++();

		CIterator& operator++(int);

		CIterator operator--();

		CIterator operator--(int);

		friend CIterator operator+(std::ptrdiff_t count, const CIterator& other1);

		CIterator operator+(std::ptrdiff_t number)const;

		CIterator operator-(std::ptrdiff_t number)const;

		//ptrdiff_t
		friend difference_type operator-(const CIterator& other1, const CIterator& other2);

		friend bool operator==(const CIterator& other1, const CIterator& other2);

		friend bool operator!=(const CIterator& other1, const CIterator& other2);

		friend bool operator<(const CIterator& other1, const CIterator& other2);

		friend bool operator<=(const CIterator& other1, const CIterator& other2);

		friend bool operator>(const CIterator& other1, const CIterator& other2);

		friend bool operator>=(const CIterator& other1, const CIterator& other2);

		reference operator[](std::ptrdiff_t number);

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
	//CMyString(char* data, std::ptrdiff_t length, std::ptrdiff_t capacity);

	char* m_str = nullptr;

	std::size_t m_length = 0;

	std::size_t m_capacity = 0;
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



