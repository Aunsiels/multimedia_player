/*******************************************************************************
*
* \file multimedia.h
* \brief Describe what is a multimedia file
* \author Julien Romero
* \version 0.1
* \date  10/12/2014
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

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>

using namespace std;

/*!
* \class Multimedia
* \brief This class represents a multimedia file.
*
* All multimedia files inherit from this class.
*/

class Multimedia {

private:
    string name; //Name of the multimedia file
    unsigned long   date; //Date of getting of the object
    string pathname; //Path to the file

public:

    /*!
    * \brief Default Constructor
    *
    * Creates a default multimedia object.
    *
    */

    Multimedia(void);

    /*!
    * \brief Constructor
    * 
    * Constructor of the Multimedia class.
    *
    * \param name : Name of the multimedia file
    * \param date : Date when the file is added in seconds
    * \param pathname : Path to the file
    *
    */

    Multimedia(string name,unsigned long date, string pathname);

    /*!
    * \brief Destructor
    *
    * Default destructor of this class.
    *
    */

    ~Multimedia(void);
    
    /*!
    * \brief Name getter
    *
    * Get the name of the file.
    *
    * \return The name of file
    *
    */

    virtual string getName (void) const;

    /*!
    * \brief Date getter
    *
    * Get the date the file was added.
    *
    * \return The date the file was imported in seconds.
    *
    */

    virtual unsigned long getDate (void) const;

    /*!
    * \brief Pathname getter
    *
    * Get the path to the file.
    *
    * \return The path to the file
    *
    */

    virtual string getPathname (void) const;

    /*!
    * \brief Name setter
    *
    * Set the name of the file.
    *
    * \param newName : the new name of the file
    *
    */

    virtual void setName (string newName);

    /*!
    * \brief Date setter
    *
    * Set the date associated to the file.
    *
    * \param newDate : the new value of the date in seconds.
    *
    */

    virtual void setDate (unsigned long newDate);

    /*!
    * \brief Path setter
    *
    * \param newPathname : the new path to the file.
    *
    */

    virtual void setPathname (string newPathname);

    /*!
    * \brief Print description
    *
    * Print the description of the file to the standard output
    *
    */

    virtual void print (void) const;

};

#endif
