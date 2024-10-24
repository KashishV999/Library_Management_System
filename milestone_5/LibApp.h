
/*
Final Project Milestone 2
Module: LibApp
Filename: LibApp.h
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



#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"
namespace seneca {
   class LibApp {
	   //Changes
	   char pub_filename[256]{};
	   Publication* total_publication[SENECA_LIBRARY_CAPACITY]{};
	   int num_loaded_publ{};
	   int lastRefLib{};
	   Menu m_bookOrPub{};
	   

	   //

	   bool m_changed;
	   Menu m_mainMenu{};
	   Menu m_exitMenu{};

	   bool confirm(const char* message);
	   void load();
	   void save();
	   int search(int method);
	   void returnPub();
	   void newPublication();
	   void removePublication();
	   void checkOutPub();

   public:
	   LibApp(const char *filename);
	   void setLibRef(int value);
	   void run();
	   Publication* getPub(int libRef);
	   ~LibApp();
   };
}
#endif // !SENECA_LIBAPP_H



