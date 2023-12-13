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
// In-Built Modules
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include <iomanip>
#include <fstream>

// User-Defined Header
#include "Item.h"
#include "POS.h"

// Namespaces
using namespace std;
using namespace sdds;

namespace sdds
{
    void Item::empty() // Sets the object into an invalid state
    {
        i_sku[0] = '\0';
        if (i_name != nullptr)
        {
            delete[] i_name;
        }
        i_name = nullptr;
        i_price = -1;
        i_taxed = false;
        i_quantity = -1;
        i_displayType = -1;
    }

    // Constructor and Destructor
    Item::Item()
    {
        empty();
    }

    Item::Item(const Item &copy)
    {
        if (copy.i_name != nullptr && copy.i_name[0] != '\0')
        {
            i_name = nullptr;
            *this = copy;
        }
        else
        {
            empty();
        }
    }

    Item::~Item()
    {
        empty();
    }

    // Operators
    Item &Item::operator=(const Item &copy)
    {
        if ((this != &copy) && (copy.i_name != nullptr) && (copy.i_name[0] != '\0'))
        {
            clear();

            if (i_name != nullptr)
            {
                delete[] i_name;
                i_name = nullptr;
            }

            // static members
            strncpy(i_sku, copy.i_sku, MAX_SKU_LEN);
            i_price = copy.i_price;
            i_taxed = copy.i_taxed;
            i_quantity = copy.i_quantity;
            i_displayType = copy.i_displayType;

            // Dynamic member

            i_name = new char[strlen(copy.i_name) + 1];
            strcpy(i_name, copy.i_name);
            i_name[strlen(copy.i_name)] = '\0';
        }
        else
        {
            empty();
        }
        return *this;
    }

    bool Item::operator==(const char *rOp) const
    {
        bool flag = true;
        for (int i = 0; i_sku[i] != '\0' && flag; i++)
        {
            if (i_sku[i] != rOp[i])
            {
                flag = false;
            }
        }
        return flag;
    }

    bool Item::operator>(const Item &rOp) const
    {
        bool flag = false;
        if (!rOp.err)
        {
            if (strcmp(i_name, rOp.i_name) > 0)
            {
                flag = true;
            }
        }
        return flag;
    }

    int Item::operator+=(const int rOp)
    {
        i_quantity += rOp;
        if (i_quantity > MAX_STOCK_NUMBER)
        {
            i_quantity = MAX_STOCK_NUMBER;

            // Setting Error Message
            Error Temp(ERROR_POS_QTY);
            err = Temp;
        }

        return i_quantity;
    }

    int Item::operator-=(const int rOp)
    {
        i_quantity -= rOp;
        if (i_quantity < 0)
        {
            i_quantity = 0;

            // Setting Error Message
            Error Temp(ERROR_POS_STOCK);
            err = Temp;
        }
        return i_quantity;
    }

    Item::operator bool()
    {
        return !err;
    }

    Item &Item::displayType(const int displayType)
    {
        if (displayType == POS_LIST || displayType == POS_FORM)
        {
            i_displayType = displayType;
        }
        return *this;
    }

    double Item::cost() const
    {
        return i_price * (1 + i_taxed * TAX);
    }

    int Item::quantity() const
    {
        return i_quantity;
    }

    Item &Item::clear()
    {
        err.clear();
        return *this;
    }

    ostream &Item::bprint(ostream &os) const
    {
        if (i_name != nullptr && i_name[0] != '\0')
        {
            os << "| ";
            if (strlen(i_name) > 20)
            {
                for (int i = 0; i < 20; i++)
                {
                    os << i_name[i];
                }
            }
            else
            {
                os << left
                   << setfill(' ')
                   << setw(20)
                   << i_name;
            }
            os << "|  "
               << setw(8)
               << fixed
               << setprecision(2)
               << right
               << (i_taxed ? i_price * (1 + TAX) : i_price)
               << " |  "
               << (i_taxed ? "T" : " ")
               << "  |" << endl;
        }

        return os;
    }

    // Base Class Virtual Func
    ostream &Item::write(ostream &os) const
    {

        if (!err)
        {
            if (i_displayType == POS_LIST)
            {
                if (i_name != nullptr && i_name[0] != '\0')
                {

                    os << setw(7)
                       << setfill(' ')
                       << left
                       << i_sku
                       << "|";
                    if (strlen(i_name) > 20)
                    {
                        for (int i = 0; i < 20; i++)
                        {
                            os << i_name[i];
                        }
                    }
                    else
                    {
                        os << left
                           << setfill(' ')
                           << setw(20)
                           << i_name;
                    }
                    os << "|"
                       << setw(7)
                       << fixed
                       << setprecision(2)
                       << right
                       << i_price
                       << "|"
                       << setprecision(3)
                       << (i_taxed ? " X " : "   ")
                       << "|"
                       << setw(4)
                       << i_quantity
                       << "|"
                       << setw(9)
                       << fixed
                       << setprecision(2)
                       << right
                       << cost() * i_quantity
                       << "|"
                       << left;
                }
            }
            else if (i_displayType == POS_FORM)
            {

                if (i_name != nullptr && i_name[0] != '\0')
                {
                    os << "=============v" << endl
                       << "Name:        " << i_name << endl
                       << "Sku:         " << i_sku << endl
                       << "Price:       " << i_price << endl;
                }
                if (i_taxed)
                {
                    os << "Price + tax: " << fixed << setprecision(2) << (i_price * 1.13) << endl;
                }
                else
                {
                    os << "Price + tax: "
                       << "N/A" << endl;
                }
                os << "Stock Qty:   " << i_quantity << endl;
            }
        }
        else
        {
            os << err.getErrorMssg() << endl;
        }

        return os;
    }

    istream &Item::read(istream &is)
    {
        clear();
        empty();

        char name[100];
        char sku[100];
        char taxed = 'N';
        bool flag;

        // SKU Input
        cout << "Sku" << endl;
        do
        {
            flag = false;
            cout << "> ";
            is >> sku;

            if (is.fail())
            {
                is.clear();
                cout << ", try again...\n"
                     << endl;
            }
            else if (strlen(sku) > MAX_SKU_LEN)
            {
                cout << ERROR_POS_SKU << endl;
            }
            else
            {
                flag = true;
            }
            is.ignore(1000, '\n');
        } while (!flag);

        // NAME Input
        cout << "Name" << endl;
        do
        {
            flag = false;
            cout << "> ";
            is.getline(name, MAX_NAME_LEN);
            if (is.fail())
            {
                is.clear();
                cout << ", try again...\n"
                     << endl;
                is.ignore(1000, '\n');
            }
            else if (strlen(name) > MAX_NAME_LEN)
            {
                name[0] = '\0';
                cout << ERROR_POS_NAME << endl;
                is.ignore(1000, '\n');
            }
            else
            {
                flag = true;
            }
        } while (!flag);

        // PRICE Input
        cout << "Price" << endl;
        do
        {
            flag = false;
            cout << "> ";
            is >> i_price;

            if (is.fail())
            {
                is.clear();
                cout << ", try again...\n"
                     << endl;
                is.ignore(1000, '\n');
            }
            else if (i_price <= 0)
            {
                cout << ERROR_POS_PRICE << endl;
                is.ignore(1000, '\n');
            }
            else
            {
                flag = true;
            }
        } while (!flag);

        // TAXED? Input

        cout << "Taxed?" << endl
             << "(Y)es/(N)o: ";
        do
        {
            flag = false;
            is >> taxed;
            if (is.fail())
            {
                is.clear();
                cout << ", try again...\n";
                is.ignore(1000, '\n');
            }
            else if (toupper(taxed) != 'Y' && toupper(taxed) != 'N')
            {
                cout << "Only 'y' and 'n' are acceptable: ";
                is.ignore(1000, '\n');
            }
            else
            {
                flag = true;
            }
        } while (!flag);

        cout << "Quantity" << endl;
        do
        {
            flag = false;
            cout << "> ";
            is >> i_quantity;
            if (is.fail())
            {
                is.clear();
                cout << ", try again...\n"
                     << endl;
                is.ignore(1000, '\n');
            }
            else if (i_quantity < 1 || i_quantity > MAX_STOCK_NUMBER)
            {
                cout << ERROR_POS_QTY << endl;
                is.ignore(1000, '\n');
            }
            else
            {
                flag = true;
            }
        } while (!flag);

        // Assigning Values
        strncpy(i_sku, sku, MAX_SKU_LEN);

        i_sku[MAX_SKU_LEN - 1] = '\0';

        i_taxed = ((toupper(taxed) == 'Y') ? true : false);

        i_name = new char[strlen(name) + 1];

        strcpy(i_name, name);

        i_name[strlen(name)] = '\0';

        return is;
    }

    ofstream &Item::save(ofstream &ofs)
    {
        if (*this)
        {
            ofs << itemType()
                << ","
                << i_sku
                << ","
                << i_name
                << ","
                << setw(4)
                << fixed
                << setprecision(2)
                << i_price
                << ","
                << (i_taxed ? 1 : 0)
                << ","
                << i_quantity;
        }
        else
        {
            ofs << err.getErrorMssg();
        }

        return ofs;
    }

    ifstream &Item::load(ifstream &ifs)
    {
        if (ifs.is_open())
        {
            empty();
            clear();

            // Local variables for Input
            char sku[MAX_SKU_LEN] = "";
            char name[MAX_NAME_LEN] = "";
            double price = -1;
            int taxed = -1;
            int quantity = -1;

            // flag
            bool flag = true;

            // sku input
            ifs.getline(sku, MAX_SKU_LEN, ',');
            if (ifs.fail())
            {
                ifs.clear();
                flag = false;
                Error temp(ERROR_POS_SKU);
                err = temp;
            }

            // Name
            if (flag)
            {
                ifs.getline(name, MAX_NAME_LEN, ',');
                if (ifs.fail())
                {
                    ifs.clear();
                    flag = false;
                    Error temp(ERROR_POS_NAME);
                    err = temp;
                }
                else if (name[0] == '\0' || name == nullptr)
                {
                    flag = false;
                    Error temp(ERROR_POS_NAME);
                    err = temp;
                }
            }

            // Price
            if (flag)
            {
                ifs >> price;
                if (ifs.fail())
                {
                    ifs.clear();
                    flag = false;
                    Error temp(ERROR_POS_PRICE);
                    err = temp;
                }
                else if (price <= 0)
                {
                    flag = false;
                    Error temp(ERROR_POS_PRICE);
                    err = temp;
                }
                // ifs.ignore(1000, '\n');

                // Taxed?
                if (flag)
                {
                    ifs.ignore();
                    ifs >> taxed;
                    if (ifs.fail())
                    {
                        ifs.clear();
                        flag = false;
                        Error temp(ERROR_POS_TAX);
                        err = temp;
                    }
                    else if (taxed > 1 || taxed < 0)
                    {
                        flag = false;
                        Error temp(ERROR_POS_TAX);
                        err = temp;
                    }
                    // ifs.ignore(1000, '\n');
                }

                // Quantity
                if (flag)
                {
                    ifs.ignore();
                    ifs >> quantity;
                    if (ifs.fail())
                    {
                        ifs.clear();
                        flag = false;
                        Error temp(ERROR_POS_QTY);
                        err = temp;
                    }
                    else if (quantity < 1 || quantity > MAX_STOCK_NUMBER)
                    {
                        flag = false;
                        Error temp(ERROR_POS_QTY);
                        err = temp;
                    }
                }

                if (flag)
                {
                    // Copying values from local variables to member variables
                    strcpy(i_sku, sku);
                    i_sku[MAX_SKU_LEN - 1] = '\0';

                    i_price = price;
                    i_taxed = (taxed == 1);
                    i_quantity = quantity;

                    if (i_name != nullptr)
                    {
                        delete[] i_name;
                        i_name = nullptr;
                    }

                    size_t size = strlen(name) + 1;

                    i_name = new char[size];
                    strcpy(i_name, name);
                    i_name[size - 1] = '\0';
                }
                else
                {
                    empty();
                }
            }

            if (ifs.peek() == EOF)
            {
                ifs.close();
            }
        }
        return ifs;
    }

    // Global Functions
    double &operator+=(double &lOp, const Item &rOp)
    {
        return lOp += (rOp.cost() * rOp.quantity());
    }

} // namespace sdds
