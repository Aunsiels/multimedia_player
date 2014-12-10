/*******************************************************************************
*
* multimedia.cpp by Julien Romero
*
* Describe what is a multimedia file
*
*******************************************************************************/

#include <iostream>
#include <ctime>

#include <multimedia.h>

// Default constructor

Multimedia::Multimedia(void) {

    this.name     = "default";
    // Get the time in seconds since 1970, January 1st
    this.date     = (unsigned long) time(NULL);
    // The default file is at the root of the computer.
    this.pathname = "/"

}

// Constructor with all parameters

Multimedia::Multimedia(
        string name,
	unsigned long date,
	string pathname) {

    this.name     = name;
    this.date     = date;
    this.pathname = pathname;

}

// Default destructor

Multimedia::~Multimedia (void) {
    //Nothing now
}

// Name getter


virtual string Multimedia::getName (void) const {
    
    return this.name;

}

// Date getter

virtual unsigned long Multimedia::getDate (void) const {

    return this.date;

}

// Pathname getter

virtual string Multimedia::getPathname (void) const {

    return this.pathname;

}

// Name setter

virtual void Multimedia::setName (string newName) {

    this.name = newName;

}

//Date setter

virtual void Multimedia::setDate (unsigned long newDate){

    this.date = newDate;

}

//Pathname setter

virtual void Multimedia::setPathname (string newPathname){

    this.pathname = newPathname;

}

//Print description

virtual void Multimedia::print (void) const {

    cout << "Name     : " << this.name     << '\n'
         << "Date     : " << this.date     << '\n'
	 << "Pathname : " << this.pathname << '\n'
	 << endl;

}

