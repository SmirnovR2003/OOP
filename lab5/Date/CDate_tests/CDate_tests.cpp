 //CDate_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.



#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../../catch2/catch.hpp"
#include "../Date/CDate.h"

bool CheckDate(const CDate& date, const Date& expectedDate)
{
	return (
		date.GetDay() == expectedDate.day &&
		date.GetMonth() == expectedDate.month &&
		date.GetWeekDay() == expectedDate.weekDay &&
		date.GetYear() == expectedDate.year
		);
	
}


SCENARIO("CDate(unsigned timestamp = 0) and CDate(unsigned day, Month month, unsigned year) function tests")
{
	SECTION("Check with zero")
	{
		CDate date1(0);
		CDate date2(1, Month::JANUARY, 1970);
		CHECK(date2.GetDay() == 1);
		CHECK(date2.GetMonth() == Month::JANUARY);
		CHECK(date2.GetYear() == 1970);
		CHECK(date2.GetWeekDay() == WeekDay::THURSDAY);
		CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
		CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	}

	SECTION("Check with 1")
	{
		CDate date1(1);
		CDate date2(2, Month::JANUARY, 1970);
		CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
		CHECK(CheckDate(date2, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	}

	SECTION("Check with max date")
	{
		CDate date1(2932896);
		CDate date2(31, Month::DECEMBER, 9999);
		CHECK(CheckDate(date1, { 31, Month::DECEMBER, 9999, WeekDay::FRIDAY }));
		CHECK(CheckDate(date2, { 31, Month::DECEMBER, 9999, WeekDay::FRIDAY }));
	}

	SECTION("Check with 2932897(выход из диапазона)")
	{
		CHECK_THROWS(CDate(2932897));
		CHECK_THROWS(CDate(1, Month::JANUARY, 10000));
	}
}

SCENARIO("GetDay tests")
{
	CDate date1(0);
	CHECK(date1.GetDay() == 1);
	date1++;
	CHECK(date1.GetDay() == 2);
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000).GetDay());
}

SCENARIO("GetMonth tests")
{
	CDate date1(0);
	CHECK(date1.GetMonth() == Month::JANUARY);
	date1 += 32;
	CHECK(date1.GetMonth() == Month::FEBRUARY);
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000).GetMonth());
}

SCENARIO("GetYear tests")
{
	CDate date1(0);
	CHECK(date1.GetYear() == 1970);
	date1 += 365;
	CHECK(date1.GetYear() == 1971);
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000).GetYear());
}

SCENARIO("GetWeekDay tests")
{
	CDate date1(0);
	CDate date2(24, Month::APRIL, 2023);
	CHECK(date1.GetWeekDay() == WeekDay::THURSDAY);
	CHECK(date2.GetWeekDay() == WeekDay::MONDAY);
	date1++;
	CHECK(date1.GetWeekDay() == WeekDay::FRIDAY);
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000).GetWeekDay());
}

SCENARIO("operator+ tests")
{
	CDate date1(0);
	date1 = date1 + 1;
	CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000) + 2);
}

SCENARIO("operator++ tests")
{
	CDate date1(0);
	CDate date2(0);
	date2 = ++date1;
	CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK(CheckDate(date2, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK_THROWS(++CDate(31, Month::DECEMBER, 9999));

}

SCENARIO("operator++(int) tests")
{
	CDate date1(0);
	CDate date2(0);
	date2 = date1++;
	CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK_THROWS(CDate(31, Month::DECEMBER, 9999)++);
}

SCENARIO("operator+= tests")
{
	CDate date1(0);
	date1 += 8;
	CHECK(CheckDate(date1, { 9, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK_THROWS(CDate(31, Month::DECEMBER, 9999) += 2);
}

SCENARIO("operator-(unsigned const dayCounter)")
{
	CDate date1(8);
	date1 = date1 - 8;
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000) - 2);
}

SCENARIO("operator-(const CDate& date)")
{
	CDate date1(8);
	CDate date2(0);
	CHECK(CheckDate(date1, { 9, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(date1 - date2 == 8);
	CHECK_THROWS(CDate(31, Month::DECEMBER, 10000) - CDate(31, Month::DECEMBER, 10000));

}

SCENARIO("operator--()")
{
	CDate date1(1);
	CDate date2(1);
	date2 = --date1;
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK_THROWS(--CDate(1, Month::JANUARY, 1970));

}

SCENARIO("operator--(int)")
{
	CDate date1(1);
	CDate date2(1);
	date2 = date1--;
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK_THROWS(CDate(1, Month::JANUARY, 1970)--);

}

SCENARIO("operator-=")
{
	CDate date1(8);
	date1 -= 8;
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK_THROWS(CDate(1, Month::JANUARY, 1970) -= 2);
}

SCENARIO("operator==")
{
	CDate date1(0);
	CDate date2(0);
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK((date1 == date2));
	date1++;
	CHECK(!(date1 == date2));

}

SCENARIO("operator!=")
{
	CDate date1(0);
	CDate date2(0);
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(!(date1 != date2));
	date1++;
	CHECK((date1 != date2));

}

SCENARIO("operator<")
{
	CDate date1(0);
	CDate date2(1);
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK((date1 < date2));
	date1++;
	CHECK(!(date1 < date2));

}

SCENARIO("operator<=")
{
	CDate date1(0);
	CDate date2(1);
	CHECK(CheckDate(date1, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date2, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK((date1 <= date2));
	date1++;
	CHECK((date1 <= date2));
	date1++;
	CHECK(!(date1 <= date2));

}

SCENARIO("operator>")
{
	CDate date2(0);
	CDate date1(1);
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK((date1 > date2));
	date2++;
	CHECK(!(date1 > date2));

}

SCENARIO("operator>=")
{
	CDate date2(0);
	CDate date1(1);
	CHECK(CheckDate(date2, { 1, Month::JANUARY, 1970, WeekDay::THURSDAY }));
	CHECK(CheckDate(date1, { 2, Month::JANUARY, 1970, WeekDay::FRIDAY }));
	CHECK((date1 >= date2));
	date2++;
	CHECK((date1 >= date2));
	date2++;
	CHECK(!(date1 >= date2));

}