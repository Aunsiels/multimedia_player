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

#include <tr1/memory>

using std::tr1::shared_ptr;

using namespace std;

//Constructor

MultimediaManager::MultimediaManager(void) {}

//Destructor

MultimediaManager::~MultimediaManager(void) {}

//Create a new Multimedia file.

shared_ptr<Multimedia> MultimediaManager::Create (const Multimedia& multimedia){
    shared_ptr<Multimedia> ptr_temp (multimedia.clone());
    this->multimedia_files[multimedia.getName()] = ptr_temp;
    return ptr_temp;
}

shared_ptr<Group> MultimediaManager::Create (const Group& group){
    shared_ptr<Group> ptr_temp (group.clone());
    this->groups[group.getName()] = ptr_temp;
    return ptr_temp;
}
