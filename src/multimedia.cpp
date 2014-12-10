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

    this->name     = "default";
    // Get the time in seconds since 1970, January 1st
    this->date     = (unsigned long) time(NULL);
    // The default file is at the root of the computer.
    this->pathname = "/";

}

// Constructor with all parameters

Multimedia::Multimedia(
        string name,
	unsigned long date,
	string pathname) {

    this->name     = name;
    this->date     = date;
    this->pathname = pathname;

}

// Default destructor

Multimedia::~Multimedia (void) {
    //Nothing now
}

// Name getter


string Multimedia::getName (void) const {
    
    return this->name;

}

// Date getter

unsigned long Multimedia::getDate (void) const {

    return this->date;

}

// Pathname getter

string Multimedia::getPathname (void) const {

    return this->pathname;

}

// Name setter

void Multimedia::setName (string newName) {

    this->name = newName;

}

//Date setter

void Multimedia::setDate (unsigned long newDate){

    this->date = newDate;

}

//Pathname setter

void Multimedia::setPathname (string newPathname){

    this->pathname = newPathname;

}

//Print description

void Multimedia::print (void) const {

    cout << "Name     : " << this->name     << endl
         << "Date     : " << this->date     << endl
	 << "Pathname : " << this->pathname << endl;

}

