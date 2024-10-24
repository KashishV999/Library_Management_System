#pragma once
#ifndef STREAMABLE_H
#define STREAMABLE_H
#include<iostream>
using namespace std;
namespace seneca {
	class Streamable {
	public:
		//Both istream and ostream inherit from ios
		virtual ostream& write(ostream& os)const = 0; //Functions overriding this function will write into an ostream object.
		virtual istream& read(istream& is) = 0;  //Functions overriding this function will read from an istream object.
		virtual bool conIO(ios& stream)const = 0; //Functions overriding this function will determine if the incoming ios object is a console IO object or not.
		virtual operator bool()const = 0; // return if the Streamable object is in a valid state or not.
		virtual ~Streamable() = default;

	};
	ostream& operator<<(ostream& os, const Streamable& st);
	istream& operator>>(istream& is, Streamable& st);
}




#endif

