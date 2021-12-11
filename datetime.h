#ifndef _DATE_TIME__
#define _DATE_TIME__

#include <string>

using std::string;

class TimeDelta;
class Datetime;

class TimeDelta
{
public:
    TimeDelta(int d, int h, int m) : days(d), hours(h), minutes(m) {} // TODO: 增加范围验证
    TimeDelta(Datetime &start, Datetime &end);
    TimeDelta(const TimeDelta &other);
    ~TimeDelta();

    string format();

    TimeDelta &operator=(const TimeDelta &other);
    bool operator>(const TimeDelta &other);
    bool operator<(const TimeDelta &other);
    bool operator>=(const TimeDelta &other);
    bool operator<=(const TimeDelta &other);
    bool operator==(const TimeDelta &other);
    bool operator!=(const TimeDelta &other);

    friend std::ostream& operator<<(std::ostream &os, const TimeDelta &td);

private:
    int days;
    int hours; // 0 ~ 24
    int minutes; // 0 ~ 60
};

class Datetime
{
public:
    Datetime() {}
    Datetime(int y, int m, int d, int h, int min)
        : year(y), month(m), day(d), hour(h), minute(min) {}
    Datetime(string &formatted_string); // format : "month/day/year hour:minute"
    Datetime(const Datetime &other);
    ~Datetime();

    string format();

    int get_year() const;
    int get_month() const;
    int get_day() const;
    int get_hour() const;
    int get_minute() const;

    Datetime &operator=(const Datetime &other);
    bool operator>(const Datetime &other);
    bool operator<(const Datetime &other);
    bool operator>=(const Datetime &other);
    bool operator<=(const Datetime &other);
    bool operator==(const Datetime &other);
    bool operator!=(const Datetime &other);

    friend std::ostream& operator<<(std::ostream &os, const Datetime &dt);

    TimeDelta operator-(const Datetime &other);

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

#include "datetime.cpp"

#endif