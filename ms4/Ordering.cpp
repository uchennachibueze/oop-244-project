#include <iomanip>
#include <iostream>
#include <fstream>
#include "Ordering.h"
using namespace std;

namespace seneca {
	void Ordering::printBillTitle(std::ostream& ostr) const
	{
		ostr << "Bill # " << m_bill_sn << " ==========================" << endl;
	}
	void Ordering::printTotal(std::ostream& ostr, double total) const
	{
		ostr << "Total: " << fixed << setprecision(2) << total << endl;
		ostr << "Tax: " << fixed << setprecision(2) << total * Tax << endl;
		ostr << "Total+Tax: " << fixed << setprecision(2) << total + Tax << endl;
		ostr << "===============================" << endl;
	}
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
	Ordering::Ordering(const char* drinkFileName, const char* FoodFileName) 
	:	m_bill_sn{ 1 }, 
		m_billableCounter{ 0 },
		m_drink_items{ nullptr },
		m_food_items{ nullptr },
		m_drinkCounter{ 0 },
		m_foodCounter{ 0 }
	{

		size_t numOfDrinkRec = countRecords(drinkFileName);
		size_t numOfFoodRec = countRecords(FoodFileName);
		//cout << "Number of drink records: " << numOfDrinkRec << endl;
		//cout << "Number of food records: " << numOfFoodRec << endl;
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
	Ordering::~Ordering() {
		delete[] m_drink_items;
		delete[] m_food_items;

		for (size_t i = 0; i < m_billableCounter; i++) {
			delete m_bill_items[i];
		}
	}

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
		cout << "List of Available Meals " << endl;
		cout << "========================" << endl;
		for (size_t i = 0; i < m_foodCounter; i++) {
			m_food_items[i].print();
			cout << endl;
		}
		cout << "========================" << endl;
	}
	void Ordering::listDrinks() const
	{
		cout << "List of Available Drinks " << endl;
		cout << "========================" << endl;
		for (size_t i = 0; i < m_drinkCounter; i++) {
			m_food_items[i].print();
			cout << endl;
		}
		cout << "========================" << endl;
	}
	void Ordering::orderFood()
	{
	}
	void Ordering::orderDrink()
	{
	}
	void Ordering::printBill(std::ostream& ostr) const
	{
	}
	void Ordering::resetBill()
	{
	}
}
