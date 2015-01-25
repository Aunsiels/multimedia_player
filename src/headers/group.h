/*******************************************************************************
*
* \file group.h
* \brief Creates a group of multimedia objects
* \author Julien Romero
* \version 0.1
* \date  18/12/2014
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

#ifndef GROUP_H
#define GROUP_H

#include <list>
#include "multimedia.h"
#include <string>
#include <tr1/memory>

using namespace std;

/*!
* \class Group
* \brief This class represents a group of multimedia objects.
*
* The group is represented by a list of multimedia objects, so the methods will
* be the same.
*
*/

class Group : public list<shared_ptr<Multimedia>> {

private :

    string name; //The name of the group
    Group (const Group&);

public :

    /*!
    * \brief Default Constructor.
    *
    * Creates an empty group.
    */

    Group (void);

    /*!
    * \brief Constructor.
    *
    * Creates an empty group.
    *
    * \param name : Name of the group
    */

    Group (string name);

    /*!
    * \brief Default destructor.
    *
    * Clean everything before deleting the object.
    *
    */

    virtual ~Group (void);

    /*!
    * \brief Name getter.
    *
    * Give the name of the group.
    *
    * \return The name of the group.
    *
    */

    virtual string getName (void) const;

    /*!
    * \brief Name setter.
    *
    * Set the name of the group.
    *
    * \param newName : the new name of the group.
    *
    */

    virtual void setName (string newName);

    /*!
    * \brief Print all the members.
    *
    * Print the members of the group on the standard output.
    *
    */

    virtual string print (void) const;

    /*!
    * \brief Clone the group.
    *
    * \return A copy of the group.
    *
    */

    virtual Group * clone (void) const;

    /*!
    * \brief Remove a multimedia file by name.
    *
    * Remove all the multimedia files in the group with the given name.
    *
    * \param name : the name of the multimedia file to remove.
    *
    */

    virtual void remove (string name);

};

#endif
