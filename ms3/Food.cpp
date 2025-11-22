/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Food
// File: Food.cpp
// Version: 1.0
// Description:
//   Food implementation derived from Billable.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Food.h"
#include "Utils.h"
using namespace std;

namespace seneca {

    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {}

    Food::Food(const Food& other) : Billable(other),
        m_ordered(other.m_ordered),
        m_child(other.m_child),
        m_customize(nullptr)
    {
        if (other.m_customize)
            ut.alocpy(m_customize, other.m_customize);
    }

    Food& Food::operator=(const Food& other) {
        if (this != &other) {
            Billable::operator=(other);
            m_ordered = other.m_ordered;
            m_child = other.m_child;

            ut.alocpy(m_customize, other.m_customize);
        }
        return *this;
    }

    Food::~Food() {
        delete[] m_customize;
        m_customize = nullptr;
    }

    bool Food::ordered() const {
        return m_ordered;
    }

    bool Food::order() {
        cout << "         Food Size Selection\n"
            << "          1- Adult\n"
            << "          2- Child\n"
            << "          0- Back\n"
            << "         > ";

        int choice = ut.getInt(0, 2);

        if (choice == 0) {
            m_ordered = false;
            m_child = false;
            delete[] m_customize;
            m_customize = nullptr;
            return false;
        }

        m_ordered = true;
        m_child = (choice == 2);

        cout << "Special instructions\n"
            << "> ";

        char buffer[256]{};
        cin.getline(buffer, 255);

        if (buffer[0] == '\0') {
            delete[] m_customize;
            m_customize = nullptr;
        }
        else {
            ut.alocpy(m_customize, buffer);
        }

        return true;
    }

    ifstream& Food::read(ifstream& file) {
        char line[256]{};

        if (file.getline(line, 255)) {
            char* comma = strchr(line, ',');
            if (comma) {
                *comma = '\0';
                name(line);

                double priceVal = atof(comma + 1);
                Billable::price(priceVal);

                m_ordered = false;
                m_child = false;

                delete[] m_customize;
                m_customize = nullptr;
            }
        }
        return file;
    }

    double Food::price() const {
        if (m_ordered && m_child)
            return Billable::price() * 0.5;

        return Billable::price();
    }

    ostream& Food::print(ostream& ostr) const {
        char padded[29]{};
        memset(padded, '.', 28);
        padded[28] = '\0';

        if (operator const char* ()) {
            size_t len = ut.strlen(operator const char* ());
            size_t copyLen = len > 25 ? 25 : len;

            for (size_t i = 0; i < copyLen; i++)
                padded[i] = operator const char* ()[i];
        }


        const char* portion =
            m_ordered ? (m_child ? "Child" : "Adult") : ".....";

        ostr << padded << portion;

        int portionLen = ut.strlen(portion);
        int paddedLen = 28;
        int totalLen = paddedLen + portionLen;
        int spacesNeeded;
        if (!m_ordered) {
            spacesNeeded = 35 - totalLen;
        }
        else if (m_customize) {
            spacesNeeded = 36 - totalLen;
        }
        else {
            spacesNeeded = 37 - totalLen;
        }

        for (int i = 0; i < spacesNeeded; i++)
            ostr << ' ';
        ostr << fixed << setprecision(2) << price();

        if (ostr.rdbuf() == cout.rdbuf() && m_customize) {
            ostr << " >> ";
            for (int i = 0; m_customize[i] && i < 30; i++)
                ostr << m_customize[i];
        }

        return ostr;
    }

}