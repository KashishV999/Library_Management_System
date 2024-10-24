/*
Final Project Milestone 1
Module: Date
Filename: Date.cpp
Version 1.0
Author	Kashish Verma
Revision History
-----------------------------------------------------------
Date      9 July 2024
2024/07/06  Actual code completed: Development phase finished, and the main codebase is finalized.
2024/07/08  Fully debugged: All known issues and bugs have been resolved,
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"




namespace seneca {
    bool seneca_test = false;
    int seneca_year = 2024;
    int seneca_mon = 12;
    int seneca_day = 25;

    bool Date::validate() {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12) {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays()) {
            errCode(DAY_ERROR);
        }
        return !bad();
    }
    int Date::mdays()const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }
    int Date::systemYear()const {
        int theYear = seneca_year;
        if (!seneca_test) {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            theYear = lt.tm_year + 1900;
        }
        return theYear;
    }
    void Date::setToToday() {
        if (seneca_test) {
            m_day = seneca_day;
            m_mon = seneca_mon;
            m_year = seneca_year;
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            m_day = lt.tm_mday;
            m_mon = lt.tm_mon + 1;
            m_year = lt.tm_year + 1900;
        }
        errCode(NO_ERROR);
    }
    int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3) {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }
    Date::Date() :m_CUR_YEAR(systemYear()) {
        setToToday();
    }
    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }
    const char* Date::dateStatus()const {
        return DATE_ERROR[errCode()];
    }
    int Date::currentYear()const {
        return m_CUR_YEAR;
    }


    void Date::errCode(int readErrorCode) {
        m_ErrorCode = readErrorCode;
    }
    int Date::errCode()const {
        return m_ErrorCode;
    }
    bool Date::bad()const {
        return m_ErrorCode != 0;
    }

    ostream& operator<<(ostream& os, const Date& RO) {
        return RO.write(os);
    }
    istream& operator>>(istream& is, Date& RO) {
        return RO.read(is);
    }



    istream& Date::read(istream& is)
    {

        char temp1{};
        char temp2{};
        errCode(NO_ERROR);
        is >> m_year;
        is >> temp1;
        //is.ignore();
        is >> m_mon;
        is >> temp2;
        //is.ignore();
        is >> m_day;
        //is.ignore(1000,'\n');
        if (is.fail()) {
            errCode(CIN_FAILED);
            //is.clear();
        }
        else {
            validate();
        }
        //is.clear();
       // is.ignore(1000, '\n');

        return is;
    }

    ostream& Date::write(ostream& os)const
    {
        if (bad()) { //bool bad return true if bad state
            os << dateStatus();
        }

        else {
            os << m_year;
            os << "/";

            os.width(2);
            os.fill('0');
            os << m_mon;

            os << "/";

            os.width(2);
            os.fill('0');
            os << m_day;

            os.fill(' '); //Makes sure the padding is set back to spaces from zero


        }
        return os;
    }



    bool Date::operator==(const Date& Right)const
    {
        return daysSince0001_1_1() == Right.daysSince0001_1_1();
    }

    bool Date::operator!=(const Date& Right)const
    {
        return daysSince0001_1_1() != Right.daysSince0001_1_1();
    }

    bool Date::operator>=(const Date& Right)const
    {
        return daysSince0001_1_1() >= Right.daysSince0001_1_1();
    }

    bool Date::operator<=(const Date& Right)const
    {
        return daysSince0001_1_1() <= Right.daysSince0001_1_1();
    }

    bool Date::operator<(const Date& Right)const
    {
        return daysSince0001_1_1() < Right.daysSince0001_1_1();
    }

    bool Date::operator>(const Date& Right)const
    {
        return daysSince0001_1_1() > Right.daysSince0001_1_1();
    }

    int Date::operator-(const Date& Right)const
    {
        return daysSince0001_1_1() - Right.daysSince0001_1_1();
    }

    Date::operator bool() const
    {
        // return !bad();
        return errCode() == 0;
    }




}