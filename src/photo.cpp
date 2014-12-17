/*******************************************************************************
*
* photo.cpp by Julien Romero
*
* Describe a photo
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

#include <multimedia.h>
#include <photo.h>
#include <stdlib.h>

using namespace std;

//Default constructor

Photo::Photo(void) :
        Multimedia(),
	place("") {}

//Constructor with all parameters

Photo::Photo(
        string _name,
	unsigned long _date,
	string _pathname,
	string _place) :
	Multimedia( _name, _date, _pathname),
	place(_place) {}

//Default destructor

Photo::~Photo (void) {
    //Nothing
}

//Place getter

string Photo::getPlace (void) const {

    return this->place;

}

//Length setter

void Photo::setPlace (string newPlace) {

    this->place = newPlace;

}

//Print the video description

void Photo::print (void) const {

    Multimedia::print ();
    cout << "Place    : " << this->place <<endl;

}

void Photo::play (void) const {
    // I use display to print a photo on screen
    system(("display " + this->getPathname() + " &").string::c_str());
}
