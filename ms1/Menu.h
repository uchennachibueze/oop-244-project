/* Citation and Sources...
Final Project Milestone ?: MS1
Module: Menu
Filename: Menu.h
Version 1.0
Author: Uchenna Emmanuel Chibueze, StNo: 174952234, Email: uechibueze@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#ifndef _SENECA_MENU_H
#define _SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {
    class MenuItem {
    private:
        char* m_content{};
        unsigned m_indent{};
        unsigned m_indentSize{};
        int m_row{};

        bool isContentValid(const char* c) const;
        void safeEmptyState();

    public:
        MenuItem(const char* content, unsigned indent, unsigned indentSize, int row);

        // Desgin rule of three which include destructor, copy constructor and copy assignment operator

        // Prohibited Copy Constructor
        MenuItem(const MenuItem&) = delete;

        // Probited Copy Assignment Operator
        MenuItem& operator=(const MenuItem&) = delete;

        // Destructor
        ~MenuItem();

        // bool type conversion operator
        operator bool() const;

        // Display member function
        std::ostream& display(std::ostream& ostr = std::cout) const;
    };
} 
#endif // !_SENECA_MENU_H