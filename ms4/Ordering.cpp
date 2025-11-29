#include "Ordering.h"
using namespace std;

namespace seneca {
	void Ordering::printBillTitle(std::ostream& ostr) const
	{
		ostr << "Bill # " << m_bill_sn << " ==========================" << endl;
	}
	void Ordering::printTotal(std::ostream& ostr, double total) const
	{
	}
	size_t Ordering::countRecords(const char* file) const
	{
		return size_t();
	}
	Ordering::Ordering(const char* drinkFileName, const char* FoodFileName)
	{
	}
	Ordering::~Ordering()
	{
	}
	size_t Ordering::noOfBillItems() const
	{
		return size_t();
	}
	bool Ordering::hasUnsavedBill() const
	{
		return false;
	}
	void Ordering::listFoods() const
	{
	}
	void Ordering::listDrinks() const
	{
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
