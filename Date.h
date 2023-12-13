// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 4
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

// In-built
#include <iostream>

// User-defined
#include "Error.h"

using namespace std;
namespace sdds
{
    class Date
    {
        int d_year;
        int d_month;
        int d_day;
        int d_hour;
        int d_minute;
        bool date_only;

    protected:
        Error err;

    public:
        // Constructors and Destructors
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int minute = 0);

        // Operator Functions
        bool operator==(const Date &rOp) const;
        bool operator!=(const Date &rOp) const;
        bool operator<(const Date &rOp) const;
        bool operator>(const Date &rOp) const;
        bool operator<=(const Date &rOp) const;
        bool operator>=(const Date &rOp) const;
        operator bool() const;

        // Getting Data
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        int getHour() const;
        int getMinute() const;
        bool getDateOnly() const;

        // Other Functions
        void set(bool dateOnly);
        void getSystemDate(int &year, int &mon, int &day, int &hour, int &min, bool dateOnly); // Already Implemented
        int uniqueDateValue(int year, int mon, int day, int hour, int min);                    // Already Implemented
        int daysOfMonth(int year, int month);                                                  // Already Implemented
        void validation();
        Date &dateOnly(bool value);
        const Error &error() const;

        friend istream &operator>>(istream &is, Date &rOp);
    };
    ostream &operator<<(ostream &os, const Date &rOp);
} // namespace sdds

#endif