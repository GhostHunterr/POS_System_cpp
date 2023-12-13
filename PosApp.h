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
#include "Item.h"

using namespace std;

namespace sdds
{
    class PosApp
    {
        char file_name[128];
        Item *Iptr[MAX_NO_ITEMS]{};
        int nptr;

    protected:
        void action(const char *title) const;
        void empty();
        void deallIptr();

    public:
        // Constructor
        PosApp(const char *fileName);
        PosApp(const PosApp &copy) = delete;
        ~PosApp();

        // Operator Overloading
        PosApp &operator=(const PosApp &copy) = delete;

        // Other Functions
        int menu();

        int selectItem();

        void listItems();
        void addItem();
        void removeItem();
        void stockItem();
        void POS();

        void saveRecs();
        void loadRecs();

        void run();

        // Defined by me
        double printItems();
    };
} // namespace sdds
