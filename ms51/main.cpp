/***********************************************************************
// OOP244 Project - Milestone 5
// File: main.cpp
// Description:
//   Final application using Menu, Ordering, Food, Drink, Billable,
//   and Utils modules to run the Dine-In Digital system.
//
// Author: Uchenna Emmanuel Chibueze
// Student ID: 174952234
// Email: uechibueze@myseneca.ca
//
// I have done all the coding by myself.
//
// -----------------------------------------------------------
***********************************************************************/

#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

int main() {
    Ordering order("drinks.csv", "foods.csv");

    
    if (!order) { 
        cout << "Failed to open data files or the data files are corrupted!" << endl;
        return 1;
    }

    
    Menu mainMenu("Seneca Restaurant ", "End Program");
    mainMenu << "Order"
        << "Print Bill"
        << "Start a New Bill"
        << "List Foods"
        << "List Drinks";

    Menu orderMenu("Order Menu", "Back to main menu", 1, 3);
    orderMenu << "Food"
        << "Drink";

    Menu confirmExit(
        "You have bills that are not saved. Are you sure you want to exit?",
        "No"
    );
    confirmExit << "Yes";


    bool isRun = true;

    while (isRun) {

        int selection = mainMenu.select();

        switch (selection) {

        case 1: {
            bool orderCase = true;
            while (orderCase) {
                int subMenuSelection = orderMenu.select();

                if (subMenuSelection == 1) {
                    order.orderFood();
                }
                else if (subMenuSelection == 2) {
                    order.orderDrink();
                } else if (subMenuSelection == 0) {
                    orderCase = false;
                }
            }
            break;
        }

        case 2:
            order.printBill(cout);
            break;

        case 3: 
            order.resetBill();
            break;

        case 4: 
            order.listFoods();
            break;

        case 5: 
            order.listDrinks();
            break;

        case 0:  
            if (order.hasUnsavedBill()) {
                int response = confirmExit.select();
                if (response == 1) {
                    isRun = false;
                }
            }
            else {
                isRun = false;
            }
            break;
        }
    }

    return 0;
}
