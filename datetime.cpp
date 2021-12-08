#include "datetime.h"

#include <assert.h>
#include <sstream>
using std::stringstream;

TimeDelta::TimeDelta(Datetime &start, Datetime &end)
{
    *this = end - start;
}

TimeDelta::TimeDelta(const TimeDelta &other)
{
    *this = other;
}

TimeDelta::~TimeDelta()
{
}

TimeDelta &TimeDelta::operator=(const TimeDelta &other)
{
    this->days = other.days;
    this->minutes = other.minutes;
}

bool TimeDelta::operator>(const TimeDelta &other)
{
    return days > other.days || (days == other.days && minutes > other.minutes);
}

bool TimeDelta::operator<(const TimeDelta &other)
{
    return days < other.days || (days == other.days && minutes < other.minutes);
}

bool TimeDelta::operator>=(const TimeDelta &other)
{
    return !(*this < other);
}

bool TimeDelta::operator<=(const TimeDelta &other)
{
    return !(*this > other);
}

bool TimeDelta::operator==(const TimeDelta &other)
{
    return days == other.days && minutes == other.minutes;
}

bool TimeDelta::operator!=(const TimeDelta &other)
{
    return !(*this == other);
}

Datetime::Datetime(string &formatted_string)
{
    // format : "month/day/year hour:minute"
    stringstream ss(formatted_string);
    ss >> month;
    assert(ss.get() == '/');
    ss >> day;
    assert(ss.get() == '/');
    ss >> year >> hour;
    assert(ss.get() == ':');
    ss >> minute;
}

Datetime::Datetime(const Datetime &other)
{
    *this = other;
}

Datetime::~Datetime()
{
}

Datetime &Datetime::operator=(const Datetime &other)
{
    year = other.year;
    month = other.month;
    day = other.day;
    hour = other.hour;
    minute = other.minute;
}

int Datetime::get_year() const
{
    return this->year;
}

int Datetime::get_month() const
{
    return this->month;
}

int Datetime::get_day() const
{
    return this->day;
}

int Datetime::get_hour() const
{
    return this->hour;
}

int Datetime::get_minute() const
{
    return this->minute;
}

bool Datetime::operator>(const Datetime &other)
{
    if (year > other.year)
        return true;
    else if (year == other.year && month > other.month)
        return true;
    else if (month == other.month && day > other.day)
        return true;
    else if (day == other.day && hour > other.hour)
        return true;
    else if (hour == other.hour && minute > other.minute)
        return true;
    else
        return false;
}

bool Datetime::operator<(const Datetime &other)
{
    return !(*this > other || *this == other);
}

bool Datetime::operator>=(const Datetime &other)
{
    return !(*this < other);
}

bool Datetime::operator<=(const Datetime &other)
{
    return !(*this > other);
}

bool Datetime::operator!=(const Datetime &other)
{
    return year != other.year || month != other.month || day != other.day || hour != other.hour || minute != other.minute;
}

bool Datetime::operator==(const Datetime &other)
{
    return !(*this != other);
}

TimeDelta &Datetime::operator-(const Datetime &other)
{
    int days = 0, minutes = 0;
    // TODO: 时间差计算
    return TimeDelta(days, minutes);
}
