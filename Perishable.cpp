// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 5 P-5
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#include <iostream>
#include <string>
#include <fstream>

#include "Perishable.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    // Defining base class virtual functions
    char Perishable::itemType() const
    {
        return 'P';
    }

    // Overwriting base class Input and output functions
    ostream &Perishable::write(ostream &os) const
    {
        Item::write(os);
        if (!Item::err)
        {
            if (i_displayType == POS_LIST)
            {
                os << "  " << p_expiry << " |";
            }
            else if (i_displayType == POS_FORM)
            {
                os << "Expiry date: " << p_expiry << endl
                   << "=============^" << endl;
            }
        }
        return os;
    }

    istream &Perishable::read(istream &is)
    {
        Item::read(is);
        if (is.good() && !Item::err)
        {
            Date temp;
            temp.set(true);

            cout << "Expiry date (YYYY/MM/DD)" << endl
                 << "> ";

            is >> temp;
            if (temp)
            {
                p_expiry.set(true);
                p_expiry = temp;
            }
            else
            {
                err = temp.error();
            }
        }
        return is;
    }

    ofstream &Perishable::save(ofstream &ofs)
    {
        Item::save(ofs);

        if (ofs.good())
        {
            ofs << "," << p_expiry << endl;
        }
        return ofs;
    }

    ifstream &Perishable::load(ifstream &ifs)
    {
        Item::load(ifs);

        if (ifs.good() && !Item::err)
        {
            Date temp;
            temp.set(true);

            ifs.ignore();

            ifs >> temp;

            if (temp)
            {
                p_expiry = temp;
            }
            else
            {
                err = temp.error();
            }
        }
        return ifs;
    }
} // namespace sdds
