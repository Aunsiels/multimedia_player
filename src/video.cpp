/*******************************************************************************
*
* video.cpp by Julien Romero
*
* Describe a video
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
#include <video.h>
#include <stdlib.h>
#include <string>

using namespace std;

//Default constructor

Video::Video(void) :
        Multimedia(),
	length(0) {}

//Constructor with all parameters

Video::Video(
        string _name,
	unsigned long _date,
	string _pathname,
	unsigned int _length) :
	Multimedia( _name, _date, _pathname),
	length(_length) {}

//Copy constructor

Video::Video(const Video& video) :
        Multimedia(video),
	length(video.getLength()){}

//Default destructor

Video::~Video (void) {
    //Nothing
}

//Length getter

unsigned int Video::getLength (void) const {

    return this->length;

}

//Length setter

void Video::setLength (unsigned int newLength) {

    this->length = newLength;

}

//Print the video description

string Video::print (void) const {

    Multimedia::print ();
    return "Length   : " + this->length + '\r';

}

void Video::play (void) const {
    // I use mplayer to print a video/film on screen
    system(("mplayer " + this->getPathname() + " &").string::c_str());
}

//Clone the video

Video * Video::clone (void) const {
    return new Video(*this);
}

