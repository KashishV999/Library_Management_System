#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"
using namespace std;
namespace seneca {
	
	ostream& operator<<(ostream& os, const Streamable& st) {
		if (st) {
			st.write(os);
		}
		return os;
	}

	istream& operator>>(istream& is, Streamable& st) {
		st.read(is);
		return is;
	}

}