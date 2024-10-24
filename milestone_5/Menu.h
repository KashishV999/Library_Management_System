/*
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author	Kashish Verma
Revision History
-----------------------------------------------------------
Date      19 July 2024
2024/07/06  Actual code completed: Development phase finished, and the main codebase is finalized.
2024/07/08  Fully debugged: All known issues and bugs have been resolved,
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
-----------------------------------------------------------*/


#ifndef MENU_H
#define MENU_H
#include<iostream>
#include <string>
using namespace std;
namespace seneca {

	const unsigned int MAX_MENU_ITEMS = 20;

	class MenuItem {

		char* m_content{};
		MenuItem() = default;
		MenuItem(const char* content);
		MenuItem(const MenuItem& other) = delete;
		MenuItem& operator=(const MenuItem& other) = delete;
		~MenuItem();
		operator bool()const;
		operator char* ()const;
		ostream& display(ostream& ostr)const;
		friend class Menu;
	};


	class Menu {

		MenuItem m_title{};
		MenuItem* menuitems{};

		unsigned num_menuItem{};

	public:
		Menu(const Menu& other) = delete;
		Menu& operator=(const Menu& other) = delete;


		Menu();
		Menu(const char* title);

		~Menu();
		const char* operator[](unsigned index)const;
		ostream& displayTitle(ostream& ostr)const;




		ostream& displayMenu(ostream& ostr)const;

		unsigned int run();

		unsigned int operator~();


		operator int()const;
		operator unsigned int()const;
		operator bool()const;


		Menu& operator<<(const char* menuitemConent);






	};


	ostream& operator<<(ostream& ostr, const Menu& other);



}

#endif // !MENU_H
