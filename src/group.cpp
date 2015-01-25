/*******************************************************************************
*
* group.cpp
* Creates a group of multimedia objects
* Julien Romero
* 0.1
* 19/12/2014
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


#include <group.h>
#include <list>
#include <iostream>
#include <intrusive_ptr.h>
#include <tr1/memory>

using namespace std;

//Default constructor
Group::Group(void) : name("default") {
    //Nothing else
}

//Constructor
Group::Group(string _name) :
        name(_name) {}

//Copy constructor
Group::Group (const Group& group) :
        list::list(group),
        name(group.getName()){}

//Destructor
Group::~Group(void) {
}

//Name getter
string Group::getName(void) const {
    return this->name;
}

//Name setter
void Group::setName(string newName) {
    this->name = newName;
}
 
//Print the elements of the group
string Group::print (void) const {
    string result = "Group " + this->name + " :" + '\r';
    //I just visit all the elements and use their print method.
    list<shared_ptr<Multimedia> >::const_iterator
        lit(this->begin()),
	lend(this->end());
    for(;lit!=lend;++lit) {
        result += (*lit)->print();
    }
    return result;
}

//Clone method
Group * Group::clone (void) const {
    return new Group(*this);
}

void Group::remove (string name) {
    list<shared_ptr<Multimedia> >::iterator
        lit(this->begin()),
	lend(this->end());
    for(;lit!=lend;++lit) {
        if ((*lit)->getName() == name){
            lit = erase(lit);
	    lit--;
	}
    }
}
