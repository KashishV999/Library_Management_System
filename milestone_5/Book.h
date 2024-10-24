#ifndef BOOK_H
#define BOOK_H
#include "Publication.h"
namespace seneca {
	class Book : public Publication {
		char* m_author{};
	public:
		Book() = default;
		Book(const Book& other);
		Book& operator=(const Book& other);
		~Book();
		ostream& write(ostream& os) const;
		istream& read(istream& istr);
		char type()const;
		operator bool() const;
		void set(int member_id);
	};

}
#endif


