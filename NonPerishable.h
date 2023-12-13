// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 5 P-3
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H

#include "Item.h"

namespace sdds
{
    class NonPerishable : public Item
    {
    public:
        // defining base class virtual function
        char itemType() const;

        // Overwriting base class input function
        ostream &write(ostream &os) const;
        ofstream &save(ofstream &ofs);
    };
} // namespace sdds

#endif