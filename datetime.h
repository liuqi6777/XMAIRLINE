#ifndef _DATE_TIME__
#define _DATE_TIME__

#include <string>

using std::string;

class TimeDelta;
class Datetime;

class TimeDelta
{
public:
    TimeDelta(int d, int m) : days(d), minutes(m) {}
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

private:
    int days;
    int minutes; // 0 ~ 60 * 24
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

    TimeDelta &operator-(const Datetime &other);

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

#endif