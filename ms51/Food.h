/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Food
// File: Food.h
// Version: 1.0
// Description:
//   Food item derived from Billable.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#ifndef _SENECA_FOOD_H
#define _SENECA_FOOD_H

#include "Billable.h"

namespace seneca {

    class Food : public Billable {
        bool m_ordered{ false };
        bool m_child{ false };
        char* m_customize{ nullptr };

    public:
        Food();
        Food(const Food& other);
        Food& operator=(const Food& other);
        ~Food();

        std::ostream& print(std::ostream& ostr = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& file) override;
        double price() const override;
    };

}

#endif // !_SENECA_FOOD_H
