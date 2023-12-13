// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/*
*****************************************************************************
                        Mile-Stone - 5 P-5
Full Name  : Farhan Hussain Sarang
Student ID#: 172963217
Email      : fsarang2@myseneca.ca
*****************************************************************************
*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
    class Item : public PosIO
    {
        char i_sku[MAX_SKU_LEN]; // SKU code length
        char *i_name{};          // Dynamically stored item name
        double i_price;          // Item price
        bool i_taxed;            // taxed or not?
        int i_quantity;          // No of items present

    protected:
        int i_displayType;
        Error err; // Will store error mssg

        void empty(); // Sets the object into an invalid state

    public:
        // Constructor and Destructor
        Item();
        Item(const Item &copy);
        virtual ~Item();

        // Operators
        Item &operator=(const Item &copy);
        bool operator==(const char *rOp) const;
        bool operator>(const Item &rOp) const;
        int operator+=(const int rOp);
        int operator-=(const int rOp);

        operator bool();

        double cost() const;
        int quantity() const;
        Item &clear();

        ostream &bprint(ostream &os) const;

        virtual char itemType() const = 0;

        Item &displayType(const int displayType);

        // Base Class Virtual Func
        ostream &write(ostream &os) const;
        istream &read(istream &is);
        ofstream &save(ofstream &ofs);
        ifstream &load(ifstream &ifs);
    };

    double &operator+=(double &lOp, const Item &rOp);

} // namespace sdds

#endif