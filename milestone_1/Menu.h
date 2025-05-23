

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
