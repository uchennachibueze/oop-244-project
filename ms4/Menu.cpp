/* Citation and Sources...
Final Project Milestone 3
Module: Menu
Filename: Menu.cpp
Version 1.0
Author: Uchenna Emmanuel Chibueze, StudentNo: 174952234, Email: uechibueze@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself
-----------------------------------------------------------
*/

#include <iostream>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
	bool MenuItem::isContentValid(const char* c) const {
		if (c == nullptr || ut.isspace(c)) return false;
		return true;
	}

	void MenuItem::safeEmptyState() {
		m_content = nullptr;
		m_indent = 0;
		m_indentSize = 0;
		m_row = -1;
	}

	MenuItem::MenuItem(const char* content, unsigned indent, unsigned indentSize, int row)
	{
		if (!isContentValid(content) || indent > 4 || indentSize > 4 || row > (int)MaximumNumberOfMenuItems) {
			safeEmptyState();
		}
		else {
			while (*content && ut.isspace(*content)) {
				content++;
			}
			ut.alocpy(m_content, content);
			m_indent = indent;
			m_indentSize = indentSize;
			m_row = row;
		}
	}

	MenuItem::operator bool() const {
		return m_content != nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& ostr) const {
		if (!*this) {
			ostr << "??????????";
			return ostr;
		}

		for (unsigned i = 0; i < m_indent * m_indentSize; i++) {
			ostr << ' ';
		}

		if (m_row >= 0) {
			ostr.width(2);
			ostr << right << m_row << "- ";
		}

		ostr << m_content;

		return ostr;
	}

	MenuItem::~MenuItem() {
		delete[] m_content;
		m_content = nullptr;
	}


	Menu::Menu(const char* title, const char* exitContent, unsigned indent, unsigned indentSize)
		:
		m_indent(indent),
		m_indentSize(indentSize),
		m_numItems(0),
		m_title(title, indent, indentSize, -1),
		m_exit(exitContent, indent, indentSize, 0),
		m_prompt("> ", indent, indentSize, -1)
	{
		for (unsigned i = 0; i < MaximumNumberOfMenuItems; i++) {
			m_items[i] = nullptr;
		}
	}

	Menu::~Menu() {
		for (unsigned i = 0; i < m_numItems; i++) {
			delete m_items[i];
			m_items[i] = nullptr;
		}
	}

	Menu& Menu::operator<<(const char* menuItemContent) {
		if (m_numItems < MaximumNumberOfMenuItems) {
			m_items[m_numItems] = new MenuItem(menuItemContent, m_indent, m_indentSize, m_numItems + 1);
			m_numItems++;
		}
		return *this;
	}

	size_t Menu::select() const {
		if (m_title) {
			m_title.display() << endl;
		}

		for (unsigned i = 0; i < m_numItems; i++) {
			m_items[i]->display() << endl;
		}

		m_exit.display() << endl;

		m_prompt.display();

		int choice = ut.getInt(0, (int)m_numItems);

		return choice;
	}

	size_t operator<<(std::ostream& ostr, const Menu& m) {
		if (&ostr == &cout) {
			return m.select();
		}
		return 0;
	}

}
