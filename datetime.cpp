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
    this->hours = other.hours;
    this->minutes = other.minutes;
    return *this;
}

bool TimeDelta::operator>(const TimeDelta &other)
{
    return days > other.days || (days == other.days && 60 * hours + minutes > 60 * other.hours + other.minutes);
}

bool TimeDelta::operator<(const TimeDelta &other)
{
    return days < other.days || (days == other.days && 60 * hours + minutes < 60 * other.hours + other.minutes);
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

std::ostream& operator<<(std::ostream &os, const TimeDelta &td)
{
    printf("<%d Day(s), %d Hour(s), %d Minute(s)>", td.days, td.hours, td.minutes);
    return os;
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
    return *this;
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
    else if (year == other.year && month == other.month)
        return day * 24 * 60 + hour * 60 + minute > other.day * 24 * 60 + other.hour * 60 + other.minute;
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

TimeDelta Datetime::operator-(const Datetime &other)
{
    assert(*this >= other);
    int days = 0, hours = 0, minutes = 0;
    // FIXME: 需修复跨年和跨月无法计算的问题
    int m1 = this->hour * 60 + this->minute;
    int m2 = other.hour * 60 + other.minute;
    if (m1 >= m2)
    {
        days = this->day - other.day;
        minutes = m1 - m2;
        hours = minutes / 60;
        minutes = minutes % 60;
    }
    else
    {
        days = this->day - other.day - 1;
        minutes = m1 - m2 + 24 * 60;
        hours = minutes / 60;
        minutes = minutes % 60;
    }
    TimeDelta delta(days, hours, minutes);
    return delta;
}

std::ostream& operator<<(std::ostream &os, const Datetime &dt)
{
    printf("%d/%d/%d %d:%d", dt.month, dt.day, dt.year, dt.hour, dt.minute);
    return os;
}
