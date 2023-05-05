#pragma once
#include <iostream>
#include <vector>
// Месяц
enum class Month
{ //использовать static cast
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

struct Date
{
	unsigned day;
	Month month;
	unsigned year;
	WeekDay weekDay;
};

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate
{
public:
	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	CDate(unsigned timestamp = 0);

	// возвращает день месяца (от 1 до 31)
	unsigned GetDay()const;

	// возвращает месяц
	Month GetMonth()const;

	// возвращает год
	unsigned GetYear()const;

	// возвращает день недели
	WeekDay GetWeekDay()const;

	//добавить const
	CDate operator+(unsigned const dayCounter)const;

	CDate operator++();

	CDate operator++(int);

	CDate operator+=(unsigned const dayCounter);

	CDate operator-(unsigned const dayCounter)const;

	int operator-(const CDate& date)const;

	CDate operator--();

	CDate operator--(int);

	CDate operator-=(unsigned const dayCounter);

	bool operator==(const CDate& date1)const;

	bool operator!=(const CDate& date)const;

	bool operator<(const CDate& date)const;

	bool operator<=(const CDate& date)const;

	bool operator>(const CDate& date)const;

	bool operator>=(const CDate& date)const;


private:

	//вычислить без цикла
	Date ConvertFromCurrentDayCounterToDate()const;

	//вынести
	//unsigned ConvertFromDateToDayCounter(const Date& date)const;


	//счетчик дней от 01.01.1970
	unsigned m_dayCounter = 0;
};


inline std::ostream& operator<<(std::ostream& stream, const Month& month)
{
	switch (month)
	{
	case Month::JANUARY: std::cout << "01";break;
	case Month::FEBRUARY: std::cout << "02";break;
	case Month::MARCH: std::cout << "03";break;
	case Month::APRIL: std::cout << "04";break;
	case Month::MAY: std::cout << "05";break;
	case Month::JUNE: std::cout << "06";break;
	case Month::JULY: std::cout << "07";break;
	case Month::AUGUST: std::cout << "08";break;
	case Month::SEPTEMBER: std::cout << "09";break;
	case Month::OCTOBER: std::cout << "10";break;
	case Month::NOVEMBER: std::cout << "11";break;
	case Month::DECEMBER: std::cout << "12";break;
	}

	return stream;
}

inline std::istream& operator>>(std::istream& stream, Month& month)
{
	unsigned monthInt;
	stream >> monthInt;
	switch (monthInt)
	{
	case 1: month = Month::JANUARY; break;
	case 2: month = Month::FEBRUARY;break;
	case 3: month = Month::MARCH;break;
	case 4: month = Month::APRIL;break;
	case 5: month = Month::MAY;break;
	case 6: month = Month::JUNE;break;
	case 7: month = Month::JULY;break;
	case 8: month = Month::AUGUST;break;
	case 9: month = Month::SEPTEMBER;break;
	case 10: month = Month::OCTOBER;break;
	case 11: month = Month::NOVEMBER;break;
	case 12: month = Month::DECEMBER;break;
	default: stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}


inline std::ostream& operator<<(std::ostream& stream, const CDate& date)
{
	stream << date.GetDay() << '.' << date.GetMonth() << '.' << date.GetYear() << std::endl;
	stream << "Date is invalid\n";
	return stream;
}


inline std::istream& operator>>(std::istream& stream, CDate& date)
{
	unsigned day, year;
	Month month;
	if (
		(stream >> day) && (stream.get() == '.')
		&& (stream >> month) && (stream.get() == '.')
		&& (stream >> year) && (stream.rdstate() == std::ios_base::goodbit)
		)
	{
		date = CDate(day, month, year);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}
	return stream;
}

