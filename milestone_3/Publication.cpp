#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Publication.h"
#include <iomanip>
using namespace std;
namespace seneca {


	void Publication::setRef(int value) {
		m_libRef = value;
	}

	void Publication::resetDate() {
		Date date; //goes to  Date(); 
		m_date = date;
	}

	bool Publication::onLoan()const {
		bool check = false;
		if (m_membership != 0) {
			check = true;
		}
		return check;
	}

	Date Publication::checkoutDate()const {
		return m_date;
	}

	bool Publication:: operator==(const char* title)const {
		if (strstr(m_title, title)) {
			return true;
		}
		return false;
	}

	Publication:: operator const char* ()const {
		return m_title;
	}

	int Publication::getRef()const {
		return m_libRef;
	}

	Publication:: operator bool() const {
		if (m_title && m_shelfId) {
			return true;
		}
		return false;
	}

	Publication::~Publication() {
		delete[] m_title;
		m_title = nullptr;
	}

	//Functions overriding this function will determine if the incoming ios object is a console IO object or not.
	bool Publication::conIO(ios& io)const {
		if (&io == &cin || &io == &cout) {
			return true;
		}
		return false;
	}


	ostream& Publication::write(ostream& os) const {
		
		if (conIO(os)) {
			os << "| " << setw(SENECA_SHELF_ID_LEN) << m_shelfId << " | ";
			os << setw(SENECA_TITLE_WIDTH) << left << setfill('.') << m_title;
			
			if (m_membership == 0) {
			
				os << " |  " << "N/A"<<"  | ";
			}
			else {
				os << " | " << setw(5) << m_membership<<" | ";
			}

			os << checkoutDate() << " |";

		}

		else {
			os << type() << "\t" << getRef() << "\t" << m_shelfId << "\t" << setw(SENECA_TITLE_WIDTH) << left << setfill('.') << m_title << "\t" << m_membership << "\t" << checkoutDate();
		}
		return os;
	}

	istream& Publication::read(istream& istr) {
		
		delete[] m_title;
		m_title = nullptr;
		m_libRef = -1;
		m_membership = 0;
		m_shelfId[0] = '\0';

		
		string shelfId{};
		string title{};
		Date date_local;
		int membership{};
		int libRef{};
		
	




		if (conIO(istr)) {
			cout << "Shelf No: ";
			
			istr >> shelfId;
			if (shelfId.length() > SENECA_SHELF_ID_LEN) {
				
				istr.setstate(ios::failbit);
			}
			istr.ignore(1000, '\n');

			cout << "Title: ";
			
			getline(istr, title);

			

			cout << "Date: ";
			istr >> date_local; // does not go to read
			if (date_local == false) { //check if it is in valid state goes to  Date::operator bool() const
				
				istr.setstate(ios::failbit);
			}

			m_libRef = -1; //libRef value is left with its default value.
		}

		else {

			istr >> libRef;
			istr.ignore();

			getline(istr, shelfId, '\t');
			
			getline(istr, title, '\t');
			
			istr >> membership;
			istr.ignore();
			istr >> date_local;
			if (date_local == false) { //check if it is in valid state goes to  Date::operator bool() const
				istr.setstate(ios::failbit);
			}

		}

		if (!istr.fail()) {
			m_title = nullptr;
			m_title = new char[title.length() + 1];
			strcpy(m_title, title.c_str());

			strcpy(m_shelfId, shelfId.c_str());

			m_membership = membership;

			m_libRef = libRef;
			
			m_date = date_local;

		}


		return istr;
	}


	Publication::Publication(const Publication& other) {
		if (this != &other) {
			if (other) {
				m_title = new char[strlen(other.m_title) + 1];
				strcpy(m_title, other.m_title);

				strcpy(m_shelfId, other.m_shelfId);

				m_membership = other.m_membership;
				m_libRef = other.m_libRef;
				
				m_date = other.m_date;
			}
		}


	}

	Publication& Publication:: operator=(const Publication& other) {
		if (this != &other) {
			if (other) {
				delete[] m_title;
				m_title = nullptr;
				m_title = new char[strlen(other.m_title) + 1];
				strcpy(m_title, other.m_title);

				strcpy(m_shelfId, other.m_shelfId);
				m_membership = other.m_membership;
				m_libRef = other.m_libRef;

				
				m_date = other.m_date;
			}
		}
		return *this;
	}

}

