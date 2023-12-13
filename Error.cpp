// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
						Mile-Stone - 5 P-5
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#define _CRT_SECURE_NO_WARNINGS

// Header File
#include <iostream>
#include <cstring>

// User-defined Header File
#include "Error.h"

// Namespaces
using namespace std;
using namespace sdds;

namespace sdds
{
	// Constructor and Destructor
	Error::Error()
	{
		error_mssg = nullptr;
	}
	Error::Error(const char *errorMssg)
	{
		if (errorMssg != nullptr && errorMssg[0] != '\0')
		{
			size_t size = strlen(errorMssg);
			error_mssg = new char[size + 1];
			strncpy(error_mssg, errorMssg, size + 1);
			error_mssg[size] = '\0';
		}
		else
		{
			error_mssg = nullptr;
		}
	}
	Error::Error(const Error &copy)
	{
		if (copy)
		{
			error_mssg = nullptr;
			*this = copy;
		}
		else
		{
			error_mssg = nullptr;
		}
	}
	Error::~Error()
	{
		clear();
	}

	// Operator Functions
	Error &Error::operator=(const Error &copy)
	{
		if (this != &copy)
		{
			if (*this)
			{
				delete[] error_mssg;
				error_mssg = nullptr;
			}
			if (copy)
			{
				size_t size = strlen(copy.error_mssg);
				error_mssg = new char[size + 1];
				strncpy(error_mssg, copy.error_mssg, size + 1);
				error_mssg[size] = '\0';
			}
		}
		return *this;
	}

	Error::operator bool() const
	{
		return (error_mssg != nullptr);
	}

	Error &Error::clear()
	{
		if (*this)
		{
			delete[] error_mssg;
			error_mssg = nullptr;
		}
		return *this;
	}

	char *Error::getErrorMssg() const
	{
		return error_mssg;
	}

	// Outside Functions
	ostream &operator<<(ostream &os, const Error &rOp)
	{
		if (rOp)
		{
			os << rOp.getErrorMssg();
		}
		return os;
	}

} // namespace sdds
