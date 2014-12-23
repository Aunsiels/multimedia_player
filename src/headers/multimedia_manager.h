/*******************************************************************************
*
* \file multimedia_manager.h
* \brief Manages the multimedia files and groups.
* \author Julien Romero
* \version 0.1
* \date  19/12/2014
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

#ifndef MULTIMEDIA_MANAGER_H
#define MULTIMEDIA_MANAGER_H

#include <map>
#include <string>
#include <Multimedia.h>
#include <Group.h>
#include <tr1/memory>

using std::tr1::shared_ptr;

using namespace std;

/*!
* \class MultimediaManager
*
* \brief Manages the multimedia files and groups.
*
* This is the main interface to create & delete multimedia files. It also allows
* to create, delete a group.
*/

class MultimediaManager {

private :
    map<string,shared_ptr<Multimedia> > multimedia_files; //The map of the multimedia files
    map<string,shared_ptr<Group> > groups; //The map of all the groups.

public :

    /*
    * \brief Constructor.
    *
    * Initialize the manager.
    */

    MultimediaManager(void);

    /*!
    * \brief Destructor
    *
    * Called before destruction.
    */

    virtual ~Multimedia(void);

    /*!
    * \brief Creates a multimedia file.
    *
    * Add a multimedia file in the manager.
    *
    * \param multimedia : a multimedia object.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Multimedia> Create (const Multimedia& multimedia);

};

#endif
