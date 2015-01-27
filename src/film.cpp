/*******************************************************************************
*
* film.cpp by Julien Romero
*
* Implentation of a film.
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

#include <string>
#include <film.h>
#include <iostream>
#include <video.h>
#include <stdlib.h>
#include <sstream>

// Default constructor

Film::Film(void) : Video(), chapters(NULL), number_chapters(0) {}

// Constructor with no chapter

Film::Film(string _name,
           unsigned long _date,
	   string _pathname) :
	   Video (_name, _date, _pathname, 0),
	   chapters(NULL),
	   number_chapters(0) {}

// Full constructor

Film::Film (string _name,
            unsigned long _date,
	    string _pathname,
	    unsigned int const _chapters[],
	    unsigned int _number_chapters) :
	    Video (_name, _date, _pathname,0) {

    //I copy the vector to avoid someone erase it from outside
    unsigned int i = 0;
    //I choose the allocate manually the memory to be able to change easily the
    //parameters.
    int total_length = 0;
    this->chapters = new unsigned int[_number_chapters];
    this->number_chapters = _number_chapters;
    for (i = 0; i < _number_chapters; i++) {
        chapters[i] = _chapters[i];
	total_length += _chapters[i];
    }
    this->setLength(total_length);
}

//Copy constructor

Film::Film(const Film& film) :
        Video(film){
    unsigned int const * * chapters = film.getChapters();
    this->number_chapters = *chapters[1];
    this->chapters = new unsigned int[this->number_chapters];
    unsigned int i = 0;
    for(i = 0; i < this->number_chapters ; i++){
        this->chapters[i] = chapters[0][i];
    }
}

//Destructor

Film::~Film (void) {
    // As I allocated manually the vector, I free the memory.
    delete[] this->chapters;
}

// Get the chapters of the movie.

unsigned int const * * Film::getChapters (void) const {
    unsigned int const * * tab = new unsigned int const * [2];
    tab[0] = this->chapters;
    tab[1] = &this->number_chapters;
    return tab;
}

// Set the chapters of the movie.

void Film::setChapters (unsigned int const _chapters[], unsigned int _number_chapters) {
    //I free the former vector
    delete[] this->chapters;
    //The same as in the constructor.
    unsigned int i = 0;
    unsigned int total_length = 0;
    this->chapters = new unsigned int[_number_chapters];
    this->number_chapters = _number_chapters;
    for (i = 0; i < _number_chapters; i++) {
        chapters[i] = _chapters[i];
	total_length += _chapters[i];
    }
    this->setLength( total_length );
}

//Print chapters

string Film::printChapters (void) const {
    unsigned int i = 0;
    stringstream ss;
    for (i = 0; i < this->number_chapters; i++) {
        ss << "Chapter " << i << " : " << chapters[i] << " seconds.\r";
    }
    return ss.str();
}

//Clone the film

Film * Film::clone (void) const {
    return new Film(*this);
}

void Film::write (ostream & stream) {
    stream << "FILM" << endl
           << this->getName() << endl
	   << this->getDate() << endl
	   << this->getPathname() << endl
	   << this->number_chapters << endl;
    unsigned int i;
    for (i = 0; i < this->number_chapters; ++i) {
        stream << chapters[i] << endl;
    }
}

void Film::read (istream & stream) {
    string name, pathname;
    unsigned int date;
    getline(stream, name);
    stream >> date;
    stream.ignore();
    getline(stream,pathname);
    stream >> this->number_chapters;
    unsigned int i;
    this->chapters = new unsigned int [this->number_chapters];
    for (i = 0; i < this->number_chapters; ++i) {
        stream >> chapters[i];
    }
    //Reload the video length
    this->setChapters(this->chapters, this->number_chapters);
    setName(name);
    setPathname(pathname);
    setDate(date);
}
