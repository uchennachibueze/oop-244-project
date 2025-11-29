/***********************************************************************
// OOP244 Project - Milestone 4
// Module: Ordering
// File: Ordering.h
// Version: 1.0
// Description:
//   Class for ordering items.
//
// -----------------------------------------------------------
// Name            Date            Reason
// Your Name       2025-11-21     Milestone 4 implementation
//
***********************************************************************/
#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include <iostream>
#include <fstream>
#include "Food.h"
#include "Drink.h"
#include "Menu.h"
#include "Billable.h"
#include "constants.h"
namespace seneca {
	class Ordering {
	private:
		size_t m_foodCounter{};
		size_t m_drinkCounter{};
		size_t m_billableCounter{};
		size_t m_bill_sn{};
		Food* m_food_items{ nullptr };
		Drink* m_drink_items{ nullptr };
		Billable* m_bill_items[MaximumNumberOfBillItems]{};

		void printBillTitle(std::ostream& ostr) const;
		void printTotal(std::ostream& ostr, double total) const;
		size_t countRecords(const char* file) const;
	public:
		Ordering(const char* drinkFileName, const char* FoodFileName);
		~Ordering();
		operator bool() const;
		size_t noOfBillItems() const;
		bool hasUnsavedBill() const;
		void listFoods() const;
		void listDrinks() const;
		void orderFood();
		void orderDrink();
		void printBill(std::ostream& ostr) const;
		void resetBill();
	};
}
#endif // SENECA_ORDERING_H