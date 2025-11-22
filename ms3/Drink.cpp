/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Drink
// File: Drink.cpp
// Version: 1.0
// Description:
//   Drink implementation derived from Billable.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Drink.h"
#include "Utils.h"
using namespace std;

namespace seneca {

    Drink::Drink() : m_size(0) {}
    ifstream& Drink::read(ifstream& file) {
        char line[256]{};

        if (file.getline(line, 255)) {
            char* comma = strchr(line, ',');
            if (comma) {
                *comma = '\0';
                name(line);

                double priceVal = atof(comma + 1);
                Billable::price(priceVal);
                m_size = 0;

                return file;
            }
        }
        return file;
    }

    bool Drink::ordered() const {
        return m_size != 0;
    }

    bool Drink::order() {
        cout << "   Drink Size Selection\n"
            << "      1- Small\n"
            << "      2- Medium\n"
            << "      3- Larg\n"
            << "      4- Extra Large\n"
            << "      0- Back\n"
            << "   > ";

        int choice = ut.getInt(0, 4);

        switch (choice) {
            case 1: m_size = 'S'; break;
            case 2: m_size = 'M'; break;
            case 3: m_size = 'L'; break;
            case 4: m_size = 'X'; break;
            default: m_size = 0; return false;
        }

        return true;
    }

    const char* Drink::sizeCode() const {
        switch (m_size) {
            case 'S': return "SML..";
            case 'M': return "MID..";
            case 'L': return "LRG..";
            case 'X': return "XLR..";
            default:  return ".....";
        }
    }

    ostream& Drink::print(ostream& ostr) const {
        char padded[34]{};
        memset(padded, '.', 33);
        padded[33] = '\0';

        const char* nm = operator const char* ();
        if (nm) {
            size_t len = ut.strlen(nm);
            size_t copyLen = len > 28 ? 28 : len;

            for (size_t i = 0; i < copyLen; i++)
                padded[i] = nm[i];
        }

        ostr << padded
            << "   "
            << setw(7) << fixed << setprecision(2)
            << Billable::price();

        return ostr;
    }


    double Drink::price() const {
        if (!ordered()) return Billable::price();

        switch (m_size) {
        case 'S': return Billable::price() * 0.5;
        case 'M': return Billable::price() * 0.75;
        case 'X': return Billable::price() * 1.5;
        default:  return Billable::price();
        }
    }

}