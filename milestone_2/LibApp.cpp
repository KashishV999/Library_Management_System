
/*
Final Project Milestone 2
Module: Milestone 2
Filename: LibApp.cpp
Version 1.0
Author  Kashish Verma
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

#include "LibApp.h"
namespace seneca {
   
	LibApp::LibApp()
		: m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_changed = false;
	

		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
	

		m_exitMenu << "Save changes and exit"<< "Cancel and go back to the main menu" ;
		
		load();
	}

	bool LibApp::confirm(const char* message) {
		Menu m_mainMenu(message);
		m_mainMenu << "Yes";
		if (m_mainMenu.run() == 1) {
			return true;
		}
		return false;
	}


	void LibApp:: load() {
		
		cout << "Loading Data" << endl;
	}
	void LibApp::save() {
		cout << "Saving Data" << endl;
	}
	void LibApp::search() {
		cout << "Searching for publication" << endl;
	}
	void LibApp::returnPub() {
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl << endl;
		m_changed = true;
	}

	void LibApp::newPublication() {
		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?")) {
			m_changed = true;
			cout << "Publication added" << endl;
		}
		cout << endl;
	}

	void LibApp::removePublication() {
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?")) {
			m_changed = true;
			cout << "Publication removed" << endl;
		}
		cout << endl;
	}

	void LibApp::checkOutPub() {
		search();
		if(confirm("Check out publication?")) {
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
		cout << endl;
	}


	void LibApp::run() {
		unsigned int s;
		//s = m_mainMenu.run();
		int flag = 1;
		do {
			//m_mainMenu.displayMenu(cout) << endl;
			s = m_mainMenu.run();
			if (s == 1) {
				newPublication();
			}

			else if (s == 2) {
				removePublication();
			}

			else if (s == 3) {
				checkOutPub();
			}

			else if (s == 4) {
				returnPub();
			
			}

			else if (s == 0) {
				if (m_changed) {
				int w = m_exitMenu.run();
					if (w == 1) {
						save();
						flag = 0;
					}
					else if (w == 2) {
						flag = 1;
						cout << endl;
					}
					else {
						if (confirm("This will discard all the changes are you sure?")) {
							flag = 0;
						}
						else {
							flag = 1;
						}

					}
				}


				else {
					flag = 0;
				}
			}


		} while (flag==1);


		cout << endl<< "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;

	}
}

/*

Class2()
	: m_name("bfng") {  //class1 constructor call
	// Other initialization code if needed
}

*/
