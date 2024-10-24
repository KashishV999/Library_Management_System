/*
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
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
#include<iostream>
#include "Menu.h"
#include <cstring>
#include <string>
using namespace std;
namespace seneca {

	MenuItem::MenuItem(const char* content) {
		delete[]m_content;
		m_content = nullptr;
		m_content = new char[strlen(content) + 1];
		strcpy(m_content, content);
	}


	MenuItem::~MenuItem() {
		delete[] m_content;
		m_content = nullptr;
	}

	MenuItem::operator bool()const {
		return m_content;
	}

	MenuItem::operator char* ()const {
		return m_content;
	}

	ostream& MenuItem::display(ostream& ostr = cout)const {
		if (this) {
			ostr << m_content;
		}
		return ostr;
	}




	Menu::Menu() {
		menuitems = new MenuItem[MAX_MENU_ITEMS];

	}



	Menu::Menu(const char* title) {
		if (title != nullptr) {
			m_title.m_content = nullptr;
			m_title.m_content = new char[strlen(title) + 1];
			strcpy(m_title.m_content, title);

			menuitems = new MenuItem[MAX_MENU_ITEMS];
		}

	}

	Menu::~Menu() {
		for (unsigned i = 0; i < num_menuItem; i++) {
			delete[] menuitems[i].m_content;
			menuitems[i].m_content = nullptr;
		}
		delete[] menuitems;
		menuitems = nullptr;

		delete[]m_title.m_content;
		m_title.m_content = nullptr;
	}




	ostream& Menu::displayTitle(ostream& os)const {
		if (m_title.m_content != nullptr) {
			os << m_title.m_content;
		}
		return os;
	}

	ostream& Menu::displayMenu(ostream& ostr)const {

		if (m_title) {
			displayTitle(ostr) << ":" << endl;
		}

		//ostr << ":" << endl;
		for (unsigned i = 0; i < num_menuItem; i++) {
			ostr.width(2);
			//by default right justify
			ostr << i + 1;
			ostr << "- ";
			ostr << menuitems[i].m_content << endl;
		}
		ostr << " 0- Exit" << endl;
		ostr << "> ";
		return ostr;
	}

	/*DO-WHILE LOOP*/
	unsigned int Menu::run() {
		displayMenu(cout);
		unsigned value{};
		int flag = 0;
		while (flag == 0) {

			cin >> value;
			if (cin.fail()) {
				//cout << "CIN FAILED";
				cout << "Invalid Selection, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
				flag = 0;
			}

			else {

				if (value < 0 || value>num_menuItem) {
					cout << "Invalid Selection, try again: ";
					flag = 0;
				}
				else {
					flag = 1;
				}
			}
		}
		return value;
	}



	unsigned int Menu::operator~()
	{
		return	run();

	}

	Menu::operator int() const
	{
		return num_menuItem;
	}

	Menu::operator unsigned int()const {
		return num_menuItem;
	}

	Menu::operator bool() const
	{
		return (num_menuItem > 1);
	}




	const char* Menu::operator[](unsigned index) const
	{
		if (index <= num_menuItem) {
			return menuitems[index].operator char* ();
		}
		else {

			return menuitems[0].operator char* ();
		}
		return nullptr;
	}


	Menu& Menu::operator<<(const char* menuitemConent) {
		if (num_menuItem < MAX_MENU_ITEMS) {
			menuitems[num_menuItem].m_content = new char[strlen(menuitemConent) + 1];
			strcpy(menuitems[num_menuItem].m_content, menuitemConent);
			num_menuItem += 1;
		}

		return *this;
	}



	ostream& operator<<(ostream& ostr, const Menu& other)
	{
		return other.displayTitle(ostr);
	}


}