#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<string>
#include "Book.h"
#include<iomanip>
#include "Publication.h"
using namespace std;
namespace seneca {

	Book::Book(const Book& other) {
		if (other) {
			delete[] m_author;
			m_author = nullptr;
			m_author = new char[strlen(other.m_author) + 1];
			strcpy(m_author, other.m_author);
		}
	}


	Book& Book:: operator=(const Book& other) {
		if (this != &other && other) {
			delete[] m_author;
			m_author = nullptr;
			m_author = new char[strlen(other.m_author) + 1];
			strcpy(m_author, other.m_author);

			Publication:: operator=(other);
		}
		return *this;
	}


	Book::~Book() {
		delete[] m_author;
		m_author = nullptr;
	}

	char Book::type()const {
		return 'B';
	}

	Book::operator bool() const {

		return m_author && Publication::operator bool();


	}


	void Book::set(int member_id) {
		Publication::set(member_id);
		resetDate();
	}

	ostream& Book::write(ostream& os) const {

		Publication::write(os);
		if (conIO(os)) {
			os << " ";

			if (strlen(m_author) < SENECA_AUTHOR_WIDTH) {
				os << setw(SENECA_AUTHOR_WIDTH) << m_author;
			}
			else {
				for (int i = 0; i < SENECA_AUTHOR_WIDTH; i++) {
					os << m_author[i];
				}
			}
			os << " |";
		}

		else {
			os << "\t";
			os << m_author;

		}

		return os;
	}

	istream& Book::read(istream& istr) {
		char author[256]{};

		Publication::read(istr);

		delete[] m_author;
		m_author = nullptr;

		if (conIO(istr)) {
			istr.ignore();
			cout << "Author: ";
			istr.getline(author, 256);
		}

		else {
			istr.ignore();
			istr.get(author, 256,'\n');
		}

		if (!istr.fail()) {
			m_author = new char[strlen(author) + 2];

			strcpy(m_author, author);

		}

		return istr;
	}


}

