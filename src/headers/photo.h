/*******************************************************************************
*
* \file photo.h
* \brief Describe what is a photo file
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

#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include "multimedia.h"

using namespace std;

/*!
* \class Photo
* \brief This class represents a photo file.
*
*/

class Photo : public Multimedia {

    friend class MultimediaManager;

private :
    string place; // The place where the photo was taken

protected :

    class DeleterPhoto;
    friend class DeleterPhoto;

    //A class to access to the delete method.
    
    class DeleterPhoto
    {
    public :
        void operator() (Photo * photo){
            delete photo;
        }
    };

    Photo(const Photo&);

    /*!
    * \brief Default Constructor
    *
    * Defaut constructor of a photo.
    *
    */

    Photo(void);

    /*!
    * \brief Constructor
    *
    * Constructor of a photo.
    *
    * \param name : Name of the photo.
    * \param date : Date when the file is added.
    * \param pathname : Path to the photo.
    * \param place : Place where the photo was taken.
    *
    */

    Photo(string name, unsigned long date, string pathname, string place);

    /*!
    * \brief Destructor
    *
    * Default destructor of this class.
    *
    */

    virtual ~Photo(void);

    /*!
    *
    * \brief Clone the photo.
    *
    * \return Return a copy of the given photo.
    */

    virtual Photo * clone (void) const;

public:

    /*!
    * \brief Place getter.
    *
    * Get the place where the photo was taken.
    *
    * \return The place where the photo was taken.
    *
    */

    virtual string getPlace(void) const;

    /*
    * \brief Place setter
    *
    * Set the place where the photo was taken.
    *
    * \param newPlace : the new place.
    *
    */

    virtual void setPlace (string newPlace);

    /*
    * \brief Print description.
    *
    * Print the description of a photo to the standard output.
    * \return Return a string which contains the file description. 
    *
    */

    virtual string print (void) const;

    /*!
    *
    * \brief Display the multimedia file on screen.
    *
    */

    virtual void play (void) const;

    /*!
    *
    * \brief Serialize the multimedia object.
    * \param stream : the output stream where the object will be written.
    *
    */

    virtual void write (ostream & stream) const;

    /*!
    *
    * \brief Read from a serialized object.
    * \param stream : the input stream where the object will be read.
    *
    */

    virtual void read (istream & stream);
};

#endif
