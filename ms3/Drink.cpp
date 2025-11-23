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
// v1.0       2025-11-21     Implemented the constructor and destructor for Drink and also
//							 implemented the read, price, print, order, and ordered methods     
// v1.1       2025-11-22     Clean up code and citation
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
            char* extractComma = strchr(line, ',');
            if (extractComma) {
                *extractComma = '\0';
                name(line);

                double drinkPrice = atof(extractComma + 1);
                Billable::price(drinkPrice);
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
        cout << "         Drink Size Selection\n"
            << "          1- Small\n"
            << "          2- Medium\n"
            << "          3- Larg\n"
            << "          4- Extra Large\n"
            << "          0- Back\n"
            << "         > ";

        int drinkChoice = ut.getInt(0, 4);

        switch (drinkChoice) {
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
        char displayDot[29]{};
        memset(displayDot, '.', 28);
        displayDot[28] = '\0';

        const char* drinkName = operator const char* ();
        if (drinkName) {
            size_t len = ut.strlen(drinkName);
            size_t copyLen = len > 25 ? 25 : len;

            for (size_t i = 0; i < copyLen; i++)
                displayDot[i] = drinkName[i];
        }

        ostr << displayDot;
        ostr << sizeCode();
        ostr << "   ";
        ostr << fixed << setprecision(2) << price();

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