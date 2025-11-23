/***********************************************************************
// OOP244 Project - Milestone 3
// Module: Billable
// File: Billable.cpp
// Author: Uchenna Emmanuel Chibueze, StudentNo: 174952234, Email: uechibueze@myseneca.ca
// Version: 1.0
// Description:
//   Abstract base class implementation for billable items.
//
// -----------------------------------------------------------
// Name            Date            Reason
// v1.0       2025-11-21     Milestone 3 implementation
//
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Billable.h"
#include "Utils.h"
using namespace std;

namespace seneca {

    Billable::Billable() : m_name(nullptr), m_price(0.0) {}

    Billable::Billable(const Billable& other) : m_name(nullptr), m_price(other.m_price) {
        if (other.m_name) {
            ut.alocpy(m_name, other.m_name);
        }
    }

    Billable& Billable::operator=(const Billable& other) {
        if (this != &other) {
            m_price = other.m_price;
            ut.alocpy(m_name, other.m_name);
        }
        return *this;
    }

    Billable::~Billable() {
        delete[] m_name;
        m_name = nullptr;
    }

    void Billable::price(double value) {
        if (value >= 0) m_price = value;
    }

    double Billable::price() const {
        return m_price;
    }

    void Billable::name(const char* value) {
        ut.alocpy(m_name, value);
    }

    Billable::operator const char* () const {
        return m_name;
    }

    double operator+(double money, const Billable& B) {
        return money + B.price();
    }

    double& operator+=(double& money, const Billable& B) {
        money += B.price();
        return money;
    }

} // namespace seneca