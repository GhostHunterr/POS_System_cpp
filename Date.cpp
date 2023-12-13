#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <iomanip>

#include "Date.h"
#include "POS.h"
#include "Error.h"

using namespace std;
using namespace sdds;

namespace sdds
{

    Date::Date()
    {
        date_only = false;
        set(date_only);
    }

    Date::Date(int year, int month, int day)
    {
        if ((year >= MIN_YEAR && year <= MAX_YEAR) &&
            (month >= 1 && month <= 12) &&
            (day >= 1 && day < daysOfMonth(year, month)))
        {

            date_only = true;
            d_year = year;
            d_month = month;
            d_day = day;
        }
        else
        {
            date_only = false;
            set(date_only);
        }
    }

    Date::Date(int year, int month, int day, int hour, int minute)
    {
        date_only = false;

        if ((year >= MIN_YEAR && year <= MAX_YEAR) &&
            (month >= 1 && month <= 12) &&
            (day >= 1 && day < daysOfMonth(year, month)) &&
            (hour >= 0 && hour < 23) &&
            (minute >= 0 && minute <= 59))
        {
            d_year = year;
            d_month = month;
            d_day = day;
            d_hour = hour;
            d_minute = minute;
        }
        else
        {
            set(date_only);
        }
    }

    bool Date::operator==(const Date &rOp) const
    {
        if ((rOp.date_only == true) && (date_only == true))
        {
            return (d_year == rOp.d_year) && (d_month == rOp.d_month) && (d_day == rOp.d_day);
        }
        else if ((rOp.date_only == false) && (date_only == false))
        {
            return (d_year == rOp.d_year) && (d_month == rOp.d_month) && (d_day == rOp.d_day) && (d_hour == rOp.d_hour) && (d_minute == rOp.d_minute);
        }
        else
        {
            return false;
        }
    }

    bool Date::operator!=(const Date &rOp) const
    {
        return !(*this == rOp);
    }

    bool Date::operator<(const Date &rOp) const
    {
        bool flag = false;

        if (d_year < rOp.d_year)
        {
            flag = true;
        }
        else if ((d_year == rOp.d_year) && (d_month < rOp.d_month))
        {
            flag = true;
        }
        else if ((d_year == rOp.d_year) && (d_month == rOp.d_month) && (d_day < rOp.d_day))
        {
            flag = true;
        }
        else if ((d_year == rOp.d_year) && (d_month == rOp.d_month) && (d_day == rOp.d_day) && date_only == false && rOp.date_only == false)
        {
            if ((d_hour < rOp.d_hour))
            {
                flag = true;
            }
            else if ((d_hour == rOp.d_hour) && d_minute < rOp.d_minute)
            {
                flag = true;
            }
            else
            {
                flag = false;
            }
        }
        else
        {
            flag = false;
        }

        return flag;
    }

    bool Date::operator>(const Date &rOp) const
    {
        return (rOp < *this);
    }

    bool Date::operator<=(const Date &rOp) const
    {
        return !(*this > rOp);
    }

    bool Date::operator>=(const Date &rOp) const
    {
        return !(*this < rOp);
    }

    Date::operator bool() const
    {
        return (!err);
    }

    int Date::getYear() const
    {
        return d_year;
    }

    int Date::getMonth() const
    {
        return d_month;
    }

    int Date::getDay() const
    {
        return d_day;
    }

    int Date::getHour() const
    {
        return d_hour;
    }

    int Date::getMinute() const
    {
        return d_minute;
    }

    bool Date::getDateOnly() const
    {
        return date_only;
    }

    void Date::set(bool dateOnly)
    {
        date_only = dateOnly;
        getSystemDate(d_year, d_month, d_day, d_hour, d_minute, date_only);
    }

    void Date::getSystemDate(int &year, int &mon, int &day, int &hour, int &min, bool dateOnly) // Already Implemented
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly)
        {
            hour = min = 0;
        }
        else
        {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int Date::uniqueDateValue(int year, int mon, int day, int hour, int min) // Already Implemented
    {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int Date::daysOfMonth(int year, int month) // Already Implemented
    {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Date::validation()
    {
        if (!err && (d_year < MIN_YEAR || d_year > MAX_YEAR))
        {
            Error temp("Invalid Year");
            err = temp;
        }
        else if (!err && (d_month < 1 || d_month > 12))
        {
            Error temp("Invalid Month");
            err = temp;
        }
        else if (!err && (d_day < 1 || d_day > daysOfMonth(d_year, d_month)))
        {
            Error temp("Invalid Day");
            err = temp;
        }
        else if (!err && (d_hour < 0 || d_hour > 23))
        {
            Error temp("Invalid Hour");
            err = temp;
        }
        else if (!err && (d_minute < 0 || d_minute > 59))
        {
            Error temp("Invlid Minute");
            err = temp;
        }
    }

    Date &Date::dateOnly(bool value)
    {
        if (value)
        {
            date_only = true;
            d_hour = d_minute = 0;
        }
        else
        {
            date_only = value;
        }
        return *this;
    }

    const Error &Date::error() const
    {
        return err;
    }

    ostream &operator<<(ostream &os, const Date &rOp)
    {
        if (rOp.error())
        {
            os << rOp.error()
               << setfill('0')
               << "("
               << rOp.getYear()
               << "/"
               << setw(2)
               << rOp.getMonth()
               << "/"
               << setw(2)
               << rOp.getDay();
            if (!rOp.getDateOnly())
            {
                os << ", "
                   << setw(2)
                   << rOp.getHour()
                   << ":"
                   << setw(2)
                   << rOp.getMinute();
            }
            os << ")";
        }
        else
        {
            os << setfill('0')
               << setw(4)
               << right
               << rOp.getYear()
               << "/"
               << setw(2)
               << rOp.getMonth()
               << "/"
               << setw(2)
               << rOp.getDay();

            if (!rOp.getDateOnly())
            {
                os << ", "
                   << setw(2)
                   << rOp.getHour()
                   << ":"
                   << setw(2)
                   << rOp.getMinute();
            }
            os << left;
        }
        return os;
    }

    istream &operator>>(istream &is, Date &rOp)
    {
        // flag
        bool flag = true;

        // Clear the Error
        rOp.err.clear();

        // Attributes set to 0
        rOp.d_year = rOp.d_month = rOp.d_day = rOp.d_hour = rOp.d_minute = 0;

        // Reading the Data
        if (flag == true)
        {
            is >> rOp.d_year;
            if (is.fail())
            {
                rOp.d_year = 0;
                Error temp("Cannot read year entry");
                flag = false;
                rOp.err = temp;
                return is;
            }
        }

        if (flag == true)
        {
            is.ignore();
            is >> rOp.d_month;
            if (is.fail())
            {
                rOp.d_month = 0;
                Error temp("Cannot read month entry");
                rOp.err = temp;
                flag = false;
                return is;
            }
        }
        if (flag == true)
        {
            is.ignore();
            is >> rOp.d_day;
            if (is.fail())
            {
                rOp.d_day = 0;
                // is.clear();
                Error temp("Cannot read day entry");
                rOp.err = temp;
                flag = false;
                return is;
            }
        }

        if (rOp.date_only)
        {
            rOp.d_hour = rOp.d_minute = 0;
        }
        else
        {
            if (flag == true)
            {
                is.ignore();
                is >> rOp.d_hour;
                if (is.fail() && flag == true)
                {
                    rOp.d_hour = 0;
                    Error temp("Cannot read hour entry");
                    rOp.err = temp;
                    flag = false;
                    return is;
                }
            }
            is.ignore();

            if (flag == true)
            {
                is >> rOp.d_minute;
                if (is.fail() && flag == true)
                {
                    rOp.d_minute = 0;
                    Error temp("Cannot read minute entry");
                    rOp.err = temp;
                    flag = false;
                    return is;
                }
            }
        }

        rOp.validation();

        return is;
    }

} // namespace sdds