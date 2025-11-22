/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Billable
// File: Billable.h
// Version: 1.0
// Description:
//   Abstract base class for billable items.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {

    class Billable {
        char* m_name{};
        double m_price{};

    protected:
        void price(double value);
        void name(const char* value);

    public:
        Billable();
        Billable(const Billable& other);
        Billable& operator=(const Billable& other);
        virtual ~Billable();

        virtual double price() const;
        virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream& read(std::ifstream& file) = 0;

        operator const char* () const;
    };

    double operator+(double money, const Billable& B);
    double& operator+=(double& money, const Billable& B);

}

#endif // !SENECA_BILLABLE_H
