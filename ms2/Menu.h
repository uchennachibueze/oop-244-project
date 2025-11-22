/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author: Uchenna Emmanuel Chibueze, StNo: 174952234, Email: uechibueze@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself
-----------------------------------------------------------
*/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {

	class Menu; // Forward declaration

	class MenuItem {
		friend class Menu;

	private:
		char* m_content{};
		unsigned m_indent{};
		unsigned m_indentSize{};
		int m_row{};

		// Constructor made private only for menu
		MenuItem(const char* content, unsigned indent, unsigned indentSize, int row);

		// Prohibited copy constructor
		MenuItem(const MenuItem&) = delete;
		
		// Prohibited copy assingment operator
		MenuItem& operator=(const MenuItem&) = delete;

		bool isContentValid(const char* c) const;
		void safeEmptyState();

		// Destructor
		~MenuItem();

		// bool type conversion operator
		operator bool() const;

		// Display member function
		std::ostream& display(std::ostream& ostr = std::cout) const;

	};

	class Menu {
	private:
		unsigned m_indent{};
		unsigned m_indentSize{};
		unsigned m_numItems{};

		MenuItem m_title;
		MenuItem m_exit;
		MenuItem m_prompt;

		MenuItem* m_items[MaximumNumberOfMenuItems]{};

	public:
		// Menu Constructor
		Menu(const char* title,
			const char* exitContent = "Exit",
			unsigned indent = 0,
			unsigned indentSize = 3);

		// Prohibted copy constructor
		Menu(const Menu&) = delete;

		// Prohibited assignment operator
		Menu& operator=(const Menu&) = delete;

		// Destructor
		~Menu();

		// Operator<< overload to ADD a new MenuItem
		Menu& operator<<(const char* menuItemContent);

		// Displays menu & returns user selection
		size_t select() const;
	};

	size_t operator<<(std::ostream& ostr, const Menu& m);

}

#endif // !_SENECA_MENU_H
