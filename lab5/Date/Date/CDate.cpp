#include "CDate.h"
const unsigned DAY_COUNTER_FROM_1970_TO_9999_YEARS = 2932896;

const unsigned  DAYS_IN_USUAL_YEAR = 365;
const unsigned  DAYS_IN_LEAP_YEAR = 366;

const std::vector<unsigned> DAYS_IN_MONTH_IN_USUAL_YEAR{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const std::vector<unsigned> DAYS_IN_MONTH_IN_LEAP_YEAR{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const unsigned DAYS_IN_400_YEAR = 146097;

//начинается с четверга так как 1.01.1970 - четверг
const std::vector<WeekDay> ORDER_OF_WEEK{ WeekDay::THURSDAY, WeekDay::FRIDAY, WeekDay::SATURDAY, WeekDay::SUNDAY, WeekDay::MONDAY, WeekDay::TUESDAY, WeekDay::WEDNESDAY };

//const std::vector<Month> ORDER_OF_MONTH
//{
//    Month::JANUARY,
//    Month::FEBRUARY,
//    Month::MARCH,
//    Month::APRIL,
//    Month::MAY,
//    Month::JUNE,
//    Month::JULY,
//    Month::AUGUST,
//    Month::SEPTEMBER,
//    Month::OCTOBER,
//    Month::NOVEMBER,
//    Month::DECEMBER
//};

bool CheckLeapYear(unsigned year)
{
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}


bool CalculateDaysInYear
(
    unsigned& current_day,
    unsigned& current_month,
    unsigned& current_year,
    const unsigned daysInYear,
    const std::vector<unsigned>& daysInMonthInYear
)
{
    if (current_day >= daysInYear)
    {
        current_day -= daysInYear;
        current_year++;
        return false;
    }
    else
    {
        for (int month = 0; month < 12; month++)
        {
            if (current_day > daysInMonthInYear[month])
            {
                current_day -= daysInMonthInYear[month];
            }
            else
            {
                current_month = month;
                current_day++;
                break;
            }
        }
        return true;
    }
}

unsigned CalculateDaysInYear(const Date& date)
{
    unsigned daysCounter = date.day - 1;// -1 так как при 01.01.1970 daysCounter должен быть 0

    bool isLeapYear = CheckLeapYear(date.year);

    if (isLeapYear)
    {
        for (int month = 0; static_cast<Month>(month+1) < (date.month); month++)
        {
            daysCounter += DAYS_IN_MONTH_IN_LEAP_YEAR[month];
        }
    }
    else
    {
        for (int month = 0; static_cast<Month>(month+1) < (date.month); month++)
        {
            daysCounter += DAYS_IN_MONTH_IN_USUAL_YEAR[month];
        }
    }

    return daysCounter;
}

unsigned ConvertFromDateToDayCounter(const Date& date)
{
    if (date.year < 1970 || date.year > 9999)
    {
        throw std::runtime_error("date is not valid\n");
    }
    unsigned daysCounter = CalculateDaysInYear(date);

    daysCounter += ((date.year - 1970) / 400) * DAYS_IN_400_YEAR;

    for (unsigned currentYear = date.year - ((date.year - 1970) % 400); currentYear < date.year; currentYear++)
    {
        CheckLeapYear(currentYear) ? daysCounter += DAYS_IN_LEAP_YEAR : daysCounter += DAYS_IN_USUAL_YEAR;
    }
    return daysCounter;
}

void CalculateDateWithDayCounter(unsigned& current_day, unsigned& current_month, unsigned& current_year)
{

    while (true)
    {
        bool isLeapYear = CheckLeapYear(current_year);

        if (isLeapYear)
        {
            if (CalculateDaysInYear(current_day, current_month, current_year, DAYS_IN_LEAP_YEAR, DAYS_IN_MONTH_IN_LEAP_YEAR))
            {
                break;
            }
        }
        else
        {
            if (CalculateDaysInYear(current_day, current_month, current_year, DAYS_IN_USUAL_YEAR, DAYS_IN_MONTH_IN_USUAL_YEAR))
            {
                break;
            }
        }
    }
}
//убрать валидность
CDate::CDate(unsigned day, Month month, unsigned year)
    :m_dayCounter(ConvertFromDateToDayCounter({ day, month, year }))
{
}

CDate::CDate(unsigned timestamp)
    : m_dayCounter(timestamp <= DAY_COUNTER_FROM_1970_TO_9999_YEARS ? timestamp : throw std::out_of_range("out of range\n"))
{
}

unsigned CDate::GetDay() const
{
    return ConvertFromCurrentDayCounterToDate().day;
}

Month CDate::GetMonth() const
{
    return ConvertFromCurrentDayCounterToDate().month;
}

unsigned CDate::GetYear() const
{
    return ConvertFromCurrentDayCounterToDate().year;
}

WeekDay CDate::GetWeekDay() const
{
    return ConvertFromCurrentDayCounterToDate().weekDay;
}


CDate CDate::operator+(unsigned const dayCounter)const
{
    return m_dayCounter + dayCounter;
}

CDate CDate::operator++()
{
    if (m_dayCounter > DAY_COUNTER_FROM_1970_TO_9999_YEARS - 1)
    {
        throw std::out_of_range("out of range\n");
    }
    m_dayCounter = m_dayCounter + 1;
    return m_dayCounter;
}

CDate CDate::operator++(int)
{
    if (m_dayCounter > DAY_COUNTER_FROM_1970_TO_9999_YEARS - 1)
    {
        throw std::out_of_range("out of range\n");
    }
    CDate tmpCopy(*this);
    ++*this;
    return tmpCopy;
}

CDate CDate::operator+=(unsigned const dayCounter)
{
    if (m_dayCounter > DAY_COUNTER_FROM_1970_TO_9999_YEARS - dayCounter)
    {
        throw std::out_of_range("out of range\n");
    }
    m_dayCounter = m_dayCounter + dayCounter;
    return m_dayCounter;
}

CDate CDate::operator-(unsigned const dayCounter)const
{
    return m_dayCounter - dayCounter;
}

int CDate::operator-(const CDate& date)const
{
    return m_dayCounter - date.m_dayCounter;
}

CDate CDate::operator--()
{
    if (m_dayCounter == 0)
    {
        throw std::out_of_range("out of range\n");
    }
    m_dayCounter = m_dayCounter - 1;
    return m_dayCounter;
}

CDate CDate::operator--(int)
{
    if (m_dayCounter == 0)
    {
        throw std::out_of_range("out of range\n");
    }
    CDate tmpCopy(*this);
    --* this;
    return tmpCopy;
}

CDate CDate::operator-=(unsigned const dayCounter)
{
    if (m_dayCounter < dayCounter)
    {
        throw std::out_of_range("out of range\n");
    }
    m_dayCounter = m_dayCounter - dayCounter;
    return m_dayCounter;
}

bool CDate::operator==(const CDate& date)const
{
    return m_dayCounter == date.m_dayCounter;
}

bool CDate::operator!=(const CDate& date)const
{
    return m_dayCounter != date.m_dayCounter;
}

bool CDate::operator<(const CDate& date)const
{
    return m_dayCounter < date.m_dayCounter;
}

bool CDate::operator<=(const CDate& date)const
{
    return m_dayCounter <= date.m_dayCounter;
}

bool CDate::operator>(const CDate& date)const
{
    return m_dayCounter > date.m_dayCounter;
}

bool CDate::operator>=(const CDate& date)const
{
    return m_dayCounter >= date.m_dayCounter;
}

Date CDate::ConvertFromCurrentDayCounterToDate()const
{
    
    unsigned current_year = 1970 + m_dayCounter / DAYS_IN_400_YEAR * 400;
    unsigned current_day = m_dayCounter % DAYS_IN_400_YEAR;
    unsigned current_month = 0;

    CalculateDateWithDayCounter(current_day, current_month, current_year);

    return
    {
        current_day,
        static_cast<Month>(current_month+1),
        current_year,
        ORDER_OF_WEEK[m_dayCounter % 7]
    };
}

