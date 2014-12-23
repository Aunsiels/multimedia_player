/*******************************************************************************
*
* \file film.h
* \brief Describe what is a film
* \author Julien Romero
* \version 0.1
* \date  15/12/2014
*
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

#ifndef FILM_H
#define FILM_H

#include <video.h>

using namespace std;

/*!
* \class Film
* \brief This class represents a film file.
*
* It inherits from Movie and contains the chapters of the movie.
*/

class Film : public Video {

private :
    unsigned int * chapters;
    unsigned int number_chapters;

protected :

    Film(const Film&);

public :

    /*!
    * \brief Default Constructor
    *
    * Creates a default film with no chapter.
    *
    */

    Film (void);

    /*!
    * \brief Constructor with no chapter.
    *
    * Creates a film with no chapter.
    *
    * \param name : The name of the film.
    * \param date : The date the film was imported.
    * \param pathname : The path to the film.
    *
    */
    
    Film (string name, unsigned long date, string pathname); 

    /*!
    * \brief Complete constructor.
    *
    * The complete constructor of a film (with chapters).
    *
    * \param name : The name of the film.
    * \param date : The date the film was imported.
    * \param pathname : The path to the film.
    * \param chapter : The vector of the length of each chapter in seconds.
    * \param number_chapters : The number of chapter there are.
    *
    */

    Film (string name,
          unsigned long date,
	  string pathname,
	  unsigned int const chapters[],
	  unsigned int number_chapters);

    /*!
    * \brief Destructor
    *
    *  Destructor of the class.
    *
    */

    ~Film (void);

    /*!
    * \brief Chapters getter.
    *
    * Get the tab of the chapters.
    *
    * \return A vector with two elements. The first one is a reference to the
    * vector of the chapters and the second one is a reference to the number of
    * chapters.
    *
    */

    virtual unsigned int const * * getChapters (void) const;

    /*!
    * \brief Chapters setter.
    *
    * Set the tab of the chapters.
    *
    * \param chapters : The vector of the length of the chapters. 
    * \param number_chapters : The number of chapters in the film.
    *
    */

    virtual void setChapters(unsigned int const chapters[], unsigned int number_chapters);

    /*!
    * \brief Print chapters.
    *
    * Print the chapters of a film.
    *
    */

    virtual void printChapters (void) const; 

    /*!
    *
    * \brief Clone the film.
    *
    * \return Return a copy of the given film.
    */

    virtual Film * clone (void) const;

};

#endif
