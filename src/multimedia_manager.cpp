/*******************************************************************************
*
* multimedia_manager.cpp by Julien Romero
*
* Manage the multimedia files.
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

#include <multimedia_manager.h>
#include <multimedia.h>
#include <group.h>
#include <iostream>
#include <tr1/memory>

using std::tr1::shared_ptr;

using namespace std;

//Constructor

MultimediaManager::MultimediaManager(void) {}

//Destructor

MultimediaManager::~MultimediaManager(void) {}

//Create a new Multimedia file.

shared_ptr<Multimedia> MultimediaManager::create (const Multimedia& multimedia){
    shared_ptr<Multimedia> ptr_temp (multimedia.clone());
    this->multimedia_files[multimedia.getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new group

shared_ptr<Group> MultimediaManager::create (const Group& group){
    shared_ptr<Group> ptr_temp (group.clone());
    this->groups[group.getName()] = ptr_temp;
    return ptr_temp;
}

// remove a multimedia file

void MultimediaManager::remove_multimedia (string name) {
    map<string,shared_ptr<Group> >::const_iterator
        lit(groups.begin()),
	lend(groups.end());
    //For all the groups...
    for(;lit!=lend;++lit) {
        //I remove the groups with the given name.
        lit->second->remove(name);
    }
    multimedia_files.erase(name);
}

//Remove a group

void MultimediaManager::remove_group (string name) {
    groups.erase(name);
}

//Search a multimedia file and print it on the standard output.

void MultimediaManager::search_multimedia (string name) const {
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(name));
    if (it != multimedia_files.end())
        it->second->print();
    else
        cout << "No file found" <<endl;
}

void MultimediaManager::search_group (string name) const {
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(name));
    if (it != groups.end())
        it->second->print();
    else
        cout << "No group found" <<endl;
}
