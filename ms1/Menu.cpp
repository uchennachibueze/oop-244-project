/* Citation and Sources...
Final Project Milestone ?: MS1
Module: Menu
Filename: Menu.cpp
Version 1.0
Author: Uchenna Emmanuel Chibueze, StNo: 174952234, Email: uechibueze@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself
-----------------------------------------------------------
*/
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace seneca {
	// function to validate if content is valid
	bool MenuItem::isContentValid(const char* c) const {
		if (c == nullptr || ut.isspace(c)) {
			return false;
		}
		return true;
	}

	// function to set safe empty state
	void MenuItem::safeEmptyState() {
		m_content = nullptr;
		m_indent = 0;
		m_indentSize = 0;
		m_row = -1;
	}

	MenuItem::MenuItem(const char* content, unsigned indent, unsigned indentSize, int row)
	{
		if (!isContentValid(content) || indent > 4 || indentSize > 4 || row > int(MaximumNumberOfMenuItems)) {
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


	ostream& MenuItem::display(ostream& ostr) const {
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



}