// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 5 P-5
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{
    class Perishable : public Item
    {
        Date p_expiry;

    public:
        // Defining base class virtual functions
        char itemType() const;

        // Overwriting base class Input and output functions
        ostream &write(ostream &os) const;
        istream &read(istream &is);
        ofstream &save(ofstream &ofs);
        ifstream &load(ifstream &ifs);
    };
} // namespace sdds

#endif