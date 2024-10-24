
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
#define _CRT_SECURE_NO_WARNINGS
#include "LibApp.h"
#include <fstream>
#include <cstring>

namespace seneca {
   //Publication* total_publication{};
	LibApp::LibApp(const char *filename)
		: m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_bookOrPub("Choose the type of publication:")

	{
		//changed
		
		if (filename) {
			strcpy(pub_filename, filename);
		}

		m_bookOrPub << "Book" << "Publication";
		
		//
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

	void LibApp::setLibRef(int value) {
		lastRefLib = value;
	}

	void LibApp:: load() {
		cout << "Loading Data" << endl;
		ifstream inputfile(pub_filename);
		num_loaded_publ = 0;
		if (!inputfile) {
			cout << "Error opening file!!!";
		}
		else {
			char type{};
			
			while(inputfile>>type) {
			
				if (type == 'P') {
					total_publication[num_loaded_publ] = new Publication;
				}
				else if (type == 'B') {
					total_publication[num_loaded_publ] = new Book;
				}

				if (total_publication[num_loaded_publ]) {

					inputfile >> *total_publication[num_loaded_publ];
					
				}
				

				num_loaded_publ++;
				
			}
			
			//CHECK or -1
			setLibRef(total_publication[num_loaded_publ-1]->getRef());
			
		}

	}

	void LibApp::save() {
		cout << "Saving Data" << endl;
		ofstream outputfile(pub_filename);
		if (!outputfile) {
			cout << "Error opening the file";
		}
		else {
		
			for (int i = 0; i < num_loaded_publ; i++) {
				if (total_publication[i]->getRef() != 0) {
					
					outputfile << *total_publication[i] <<endl;

					
				}
		
			}
		}
	}



	void LibApp::newPublication() {

		if (num_loaded_publ == SENECA_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!";
		}

		else {
			cout << "Adding new publication to library" << endl;
			int choice = m_bookOrPub.run();
			Publication* pbl{};
			if (choice == 1) {
				pbl = new Book;
				
			}

			else if (choice == 2) {
				pbl = new Publication;
				
			}
			
			else if (choice == 0) {
				cout << "Aborted!"<<endl;
				return;
			}


			cin >> *pbl;

			if (cin.fail()) {
				cin.clear();
				//add if ignore
				cout << "Aborted";
				//exit
			}

			else {
				if (confirm("Add this publication to library?")) {
					if (pbl) {
						//Add one to the LLRN and set the library reference number to the value
						lastRefLib += 1;
						
						//set the library reference number to the value
						pbl->setRef(lastRefLib);

						//Add the publication object's address to the end of the PPA 
					
						//	Publication& operator=(const Publication& other);

						total_publication[num_loaded_publ] = pbl;



						num_loaded_publ ++;
						
						m_changed = true;
						cout << "Publication added" << endl;
					}

					else {
						cout << "Failed to add publication!";
						delete pbl;
						pbl = nullptr;
					}
				}

				else {
					cout << "Aborted";
					//exit
				}
				cout << endl;
			}


		}
	}

	//method to search 
	//1 - All
	//2 - on loan
	//3 - available
	int LibApp::search(int method) {
		// return the library reference number. 
		cout << "Searching for publication" << endl;
		
		char typeBP{};
	
		int flag = 1;
		
		do {
			
			int choice = m_bookOrPub.run();
			typeBP = (choice == 1) ? 'B' : ((choice == 2) ? 'P' : 'N');

			if (choice > 0) {
				string title{};
				cin.clear();
				cin.ignore(1000,'\n');
				
				cout << "Publication Title: ";
				getline(cin, title);
				PublicationSelector ps("Select one of the following found matches:");
				//PUT HERE -1
				//cout << "NUM OF LOADED : "<< num_loaded_publ <<endl;
				for (int i = 0; i < num_loaded_publ; i++) {
					
					switch (method) {
						case 1:
							
							if ((total_publication[i]->getRef() != 0) && total_publication[i]->type() == typeBP  && strstr(total_publication[i]->operator const char *(), title.c_str())) {
							
								ps << total_publication[i];
							}

							
							break;
						case 2:
							if ((total_publication[i]->getRef() != 0) && strstr(total_publication[i]->operator const char* (), title.c_str()) && total_publication[i]->type() == typeBP && total_publication[i]->onLoan()) {
								
								ps << total_publication[i];
							}
							break;
						case 3:
							if ((total_publication[i]->getRef() != 0) && strstr(total_publication[i]->operator const char* (), title.c_str()) && total_publication[i]->type() == typeBP &&  (!(total_publication[i]->onLoan()))) {
								//total_publication[i]->write(cout)<<endl;

								ps << total_publication[i];
							}
							//else {
								//total_publication[i]->write(cout)<<endl;
							//}
							break;
						default:
							cout << "WHATEVER";
					}

				}
				if (!ps) {
					cout<<"No matches found!"<<endl;
					
				}
				else {
					ps.sort();
					int num_choice = ps.run();
					
					/*
					int PublicationSelector::run() {
					// runs the selection
					return the library reference fo the selection publication.
					//return the library reference number. 
					*/
					
					return num_choice;

				}

			}

			else {
				cout << "Aborted!";
				flag = 0; //out of loop
			}

		} while (flag == 1);

		// return the library reference number

	}


	Publication* LibApp::getPub(int libRef) {
		
		for (int i = 0; i < num_loaded_publ; i++) {
			if (total_publication[i]->getRef() == libRef) {
				return total_publication[i];
			}
		}
		return nullptr;
	}



	void LibApp::removePublication() {
		cout << "Removing publication from library" << endl;
		int num = search(1);
		cout << "CHOICE: " << num << endl;

		if (num > 0) {
			for (int i = 0; i < num_loaded_publ && num != 0; i++) {
				if (num == total_publication[i]->getRef()) {
					cout << *total_publication[i];
					i = num_loaded_publ; //EXIT
				}
			}

			if (confirm("Remove this publication from the library?")) {
				//Set the library reference of the selected publication to 0 (zero)
				for (int i = 0; i < num_loaded_publ; i++) {
					if (total_publication[i]->getRef() == num) {

						total_publication[i]->setRef(0);

					}
				}
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
		else {
			cout << "Aborted!";
			return;
		}
		cout << endl;
	}



	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library"<<endl;
		int num = search(3);

		for (int i = 0; i < num_loaded_publ; i++) {
			if (num == total_publication[i]->getRef()) {
				cout << *total_publication[i];
				i = num_loaded_publ; //EXIT
			}
		}

		if (confirm("Check out publication?")) {
			/*read a 5-digit number from the console, if invalid print:
			"Invalid membership number, try again: " and read again*/
			int membernum{};
			do {
				cin >> membernum;
				if (membernum < 10000 && membernum > 99999) {
					cout << "Invalid membership number, try again: ";
				}
			} while (membernum < 10000 || membernum>99999);

			for (int i = 0; i < num_loaded_publ; i++) {
				if (total_publication[i]->getRef() == num) {
					
					total_publication[i]->set(membernum);
				
					m_changed = true;
					cout << "Publication checked out" << endl;
				}
			}
		}
		cout << endl;
	}



	void LibApp::returnPub() {
		cout << "Return publication to the library";
		int num = search(2);

		for (int i = 0; i < num_loaded_publ; i++) {
			if (num == total_publication[i]->getRef()) {
				cout << *total_publication[i];
				i = num_loaded_publ; //EXIT
			}
		}

		if (confirm("Return Publication?")) {
		//If the publication is more than 15 days on loan,

			for (int i = 0; i < num_loaded_publ; i++) {
				if (total_publication[i]->getRef() == num) {
					
					
					//int days=  total_publication[i]->checkoutDate();
					//cout << days;
					Date date_one{};
					date_one.write(cout) << endl;
					cout << total_publication[i]->checkoutDate()<<endl;

					int days = date_one.operator-(total_publication[i]->checkoutDate());

					cout << "DAYS ARE : " << days<<endl;
					if (days > SENECA_MAX_LOAN_DAYS) {
						double penalty = (days - 15) * 0.50;
						cout << "Please pay $";
						cout.setf(ios::fixed);
						cout.precision(2);
						cout<< penalty << " penalty for being " << (days - 15) << " days late!"<<endl;
						//
						total_publication[i]->set(0);
						
						m_changed = true;


						cout << "Publication returned" << endl << endl;
						
					}
				}
			}
		}

		else {
			cout << "Aborted!";
		}
	
		
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



	LibApp:: ~LibApp() {
		//Publication* total_publication[SENECA_LIBRARY_CAPACITY]{};
		
		for (int i = 0; i < SENECA_LIBRARY_CAPACITY; i++) {
			delete total_publication[i];
			total_publication[i] = nullptr;
		}
	}
}

/*

Class2()
	: m_name("bfng") {  //class1 constructor call
	// Other initialization code if needed
}

*/

