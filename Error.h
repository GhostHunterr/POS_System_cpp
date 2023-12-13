// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 5 P-5
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H

#include <iostream>

// Namespaces
using namespace std;

namespace sdds
{
    class Error
    {
        char *error_mssg;

    public:
        // Constructor and Destructor
        Error();
        Error(const char *errorMssg);
        Error(const Error &copy);
        ~Error();

        // Operator Functions
        Error &operator=(const Error &copy);
        operator bool() const;

        // Other Functions
        Error &clear();
        char *getErrorMssg() const;
    };

    ostream &operator<<(ostream &os, const Error &rOp);

} // namespace sdds

#endif