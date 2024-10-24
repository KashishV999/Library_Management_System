#pragma once
#ifndef PUBLICATION_H
#define PUBLICATION_H
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"
namespace seneca {
	class Publication : public Streamable {
	public:
		char* m_title{}; //can not be more than 255 characters long.
		char m_shelfId[SENECA_SHELF_ID_LEN + 1]{};
		int m_membership{};
		int m_libRef = -1;
		Date m_date{};

	//public:
		Publication() = default;

		virtual void set(int member_id) {
			if (member_id == 0 || (member_id > 10000 && member_id < 99999)) {
				m_membership = member_id;
			}
		};

		void setRef(int value);

		void resetDate();


		virtual char type()const {
			return 'P';
		};

		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;

		int getRef()const;


		bool conIO(ios& io)const;

		ostream& write(ostream& os) const;

		istream& read(istream& istr);

		 operator bool() const;

		Publication(const Publication& other);
		Publication& operator=(const Publication& other);

		~Publication();


	};


}

#endif
