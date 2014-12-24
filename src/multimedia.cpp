/*******************************************************************************
*
* multimedia.cpp by Julien Romero
*
* Describe what is a multimedia file
*
*Copyright (c) 2014 JulienRomero
*
*Permission is hereby granted, free of charge, to any person obtaining
*a copy of this software and associated documentation files (the
*"Software"), to deal in the Software without restriction, including
*without limitation the rights to use, copy, modify, merge, publish,
*distribute, sublicense, and/or sell copies of the Software, and to
*permit persons to whom the Software is furnished to do so, subject to
*the following conditions:
*
*The above copyright notice and this permission notice shall be
*included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
*LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
*OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
*WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*******************************************************************************/

#include <iostream>
#include <ctime>

#include <multimedia.h>

// Default constructor

Multimedia::Multimedia(void) :
        name("default"),
	date((unsigned long) time(NULL)),
	pathname("/") {}

// Constructor with all parameters

Multimedia::Multimedia(
        string _name,
	unsigned long _date,
	string _pathname) :
	name(_name),
	date(_date),
	pathname(_pathname){}

//Copy constructor

Multimedia::Multimedia(const Multimedia& multimedia) :
        name(multimedia.getName()),
	date(multimedia.getDate()),
	pathname(multimedia.getPathname()){}

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


//A class to access to the delete method.

class Multimedia::DeleterMultimedia
{
    public :
        void operator() (Multimedia * multimedia){
	    delete multimedia;
        }
};

