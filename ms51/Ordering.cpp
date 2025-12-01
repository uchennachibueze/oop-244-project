/***********************************************************************
// OOP244 Project - Milestone 5
// Module: Ordering
// File: Ordering.cpp
// Version: 1.0
// Description:
//   Method definition for ordering items.
//
// -----------------------------------------------------------
// Name            Date            Reason
// v1.0				11/30/2025     Define and implement the functions 
//								  following the specifications in the MS5
//
-----------------------------------------------------------
I have done all the code by myself
-----------------------------------------------------------
***********************************************************************/
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Ordering.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
	// Prints the header title of the bill
	void Ordering::printBillTitle(std::ostream& ostr) const
	{
		ostr << "Bill # " 
			<< setw(3) << std::setfill('0') << m_bill_sn
			<< " =============================" << setfill(' ') << endl;
	}
	//Prints the total of the bill
	void Ordering::printTotal(std::ostream& ostr, double total) const
	{
		ostr << setw(27) << "Total:" << setw(13) << fixed << setprecision(2) << total << endl;
		ostr << setw(25) << "Tax:" << setw(15) << fixed << setprecision(2) << total * Tax << endl;
		ostr << setw(31) << "Total+Tax:" << setw(9) << fixed << setprecision(2) << total + (total * Tax) << endl;
		ostr << "========================================" << endl;
	}
	// Count records in the file
	size_t Ordering::countRecords(const char* file) const
	{
		size_t newlineCounter = 0;
		std::ifstream resFiles(file);
		char ch{};
		while (resFiles.get(ch)) {
			if (ch == '\n') {
				newlineCounter++;
			}
		}
		return newlineCounter;
	}
	// Constructor
	Ordering::Ordering(const char* drinkFileName, const char* FoodFileName) 
	:	m_foodCounter{ 0 },
		m_drinkCounter{ 0 },
		m_billableCounter{ 0 },
		m_bill_sn{ 1 }, 
		m_food_items{ nullptr },
		m_drink_items{ nullptr },
		m_bill_items{nullptr}
	{

		size_t numOfDrinkRec = countRecords(drinkFileName);
		size_t numOfFoodRec = countRecords(FoodFileName);
		ifstream drinkFile(drinkFileName);
		ifstream foodFile(FoodFileName);

		if (!drinkFile || !foodFile) {
			m_drink_items = nullptr;
			m_food_items = nullptr;
			m_drinkCounter = 0;
			m_foodCounter = 0;
			return;
		}
			
		Drink* drinks = new Drink[numOfDrinkRec];
		Food* foods = new Food[numOfFoodRec];

		size_t drinkReadResult = 0;
		size_t foodReadResult = 0;

		for (size_t i = 0; i < numOfDrinkRec; i++) {
			drinks[i].read(drinkFile);
			if (!drinkFile.fail()) {
				drinkReadResult++;
			}
			else {
				break;
			}
		}
			
		for (size_t j = 0; j < numOfFoodRec; j++) {
			foods[j].read(foodFile);
			if (!foodFile.fail()) {
				foodReadResult++;
			} else {
				break;
			}
		}
		
		if (drinkReadResult != numOfDrinkRec || foodReadResult != numOfFoodRec) {
			delete[] drinks;
			delete[] foods;
			m_drink_items = nullptr;
			m_food_items = nullptr;
			m_drinkCounter = 0;
			m_foodCounter = 0;
			return;
		}

		m_drink_items = drinks;
		m_food_items = foods;
		m_drinkCounter = numOfDrinkRec;
		m_foodCounter = numOfFoodRec;
	}
	// Destructor
	Ordering::~Ordering() {
		delete[] m_drink_items;
		delete[] m_food_items;

		for (size_t i = 0; i < m_billableCounter; i++) {
			delete m_bill_items[i];
		}
	}
	// Gets the number of bill items
	size_t Ordering::noOfBillItems() const
	{
		return m_billableCounter;
	}

	Ordering::operator bool() const
	{
		return m_food_items != nullptr && m_drink_items != nullptr;
	}
	bool Ordering::hasUnsavedBill() const
	{
		return m_billableCounter > 0;
	}
	
	void Ordering::listFoods() const
	{
		cout << "List Of Avaiable Meals" << endl;
		cout << "========================================" << endl;
		for (size_t i = 0; i < m_foodCounter; i++) {
			m_food_items[i].print();
			cout << endl;
		}
		cout << "========================================" << endl;
	}
	void Ordering::listDrinks() const
	{
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================" << endl;
		for (size_t i = 0; i < m_drinkCounter; i++) {
			m_drink_items[i].print();
			cout << endl;
		}
		cout << "========================================" << endl;
	}
	void Ordering::orderFood()
	{
		if (m_billableCounter >= MaximumNumberOfBillItems) {
			return;
		}
		Menu foodMenu("Food Menu", "Back to Order", 2);

		for(size_t i = 0; i < m_foodCounter; i++) {
			foodMenu << m_food_items[i];
		}

		int selection = foodMenu.select();
		if (selection != 0) {
			Billable* selectedFoodItem = new Food(m_food_items[selection - 1]);
			
			if (selectedFoodItem->order()) {
				m_bill_items[m_billableCounter] = selectedFoodItem;
				m_billableCounter++;
			} else {
				delete selectedFoodItem;
			}
		}

	}
	void Ordering::orderDrink()
	{
		if (m_billableCounter >= MaximumNumberOfBillItems) {
			return;
		}
		Menu drinkMenu("Drink Menu", "Back to Order", 2);

		for (size_t i = 0; i < m_drinkCounter; i++) {
			drinkMenu << m_drink_items[i];
		}

		int selection = drinkMenu.select();
		if (selection != 0) {
			Billable* selectedDrinkItem = new Drink(m_drink_items[selection - 1]);

			if (selectedDrinkItem->order()) {
				m_bill_items[m_billableCounter] = selectedDrinkItem;
				m_billableCounter++;
			}
			else {
				delete selectedDrinkItem;
			}
		}

	}
	void Ordering::printBill(std::ostream& ostr) const
	{
		double total = 0.0;
		printBillTitle(ostr);
		for (size_t i = 0; i < m_billableCounter; i++) {
			if(m_bill_items[i]) {
				m_bill_items[i]->print(ostr) << endl;
				total += m_bill_items[i]->price();
			}
		}
		printTotal(ostr, total);

	}
	void Ordering::resetBill()
	{
		char billFileName[21]{};
		ut.makeBillFileName(billFileName, m_bill_sn);

		ofstream billFile(billFileName);
		if (billFile) {
			printBill(billFile);
		}

		cout << "Saved bill number " << m_bill_sn << std::endl;
		cout << "Starting bill number " << (m_bill_sn + 1) << std::endl;

		for (size_t i = 0; i < m_billableCounter; i++) {
			delete m_bill_items[i];
			m_bill_items[i] = nullptr;
		}

		m_bill_sn++;
		m_billableCounter = 0;
	}
}
