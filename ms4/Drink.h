/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Drink
// File: Drink.h
// Version: 1.0
// Description:
//   Drink item derived from Billable.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"

namespace seneca {

    class Drink : public Billable {
        char m_size{};  // 'S', 'M', 'L', 'X', or unset

        const char* sizeCode() const;

    public:
        Drink();

        std::ostream& print(std::ostream& ostr = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& file) override;
        double price() const override;
    };

}

#endif // !SENECA_DRINK_H
