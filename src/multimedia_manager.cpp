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
#include <photo.h>
#include <video.h>
#include <film.h>
#include <group.h>
#include <iostream>
#include <tr1/memory>
#include <fstream>

using namespace std;

//Constructor

MultimediaManager::MultimediaManager(void) {
    read("manager");
}

//Destructor

MultimediaManager::~MultimediaManager(void) {
    write("manager");
}

//Create a new Photo file.

shared_ptr<Photo> MultimediaManager::create_photo
        (const string & name,
	 unsigned long date,
	 const string & pathname,
	 const string & place){
    shared_ptr<Photo> ptr_temp (new Photo(name, date, pathname, place),
        Photo::DeleterPhoto());
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new default Photo file.

shared_ptr<Photo> MultimediaManager::create_photo (void){
    shared_ptr<Photo> ptr_temp (new Photo(), Photo::DeleterPhoto());
    //Remember the name
    string name = ptr_temp->getName();
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    int i = 0;
    //The default file has not specified name
    while(it != multimedia_files.end()){
        ptr_temp->setName(name + to_string(i));
	it = multimedia_files.find(ptr_temp->getName());
	++i;
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Deserializes a photo

shared_ptr<Photo> MultimediaManager::create_photo(istream & is) {
    shared_ptr<Photo> photo (new Photo(), Photo::DeleterPhoto());
    photo->read(is);
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(photo->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[photo->getName()] = photo;
    return photo;
}

//Create a new default Video file.

shared_ptr<Video> MultimediaManager::create_video (void){
    shared_ptr<Video> ptr_temp (new Video(), Video::DeleterVideo());
    //Remember the name
    string name = ptr_temp->getName();
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    int i = 0;
    //The default file has not specified name
    while(it != multimedia_files.end()){
        ptr_temp->setName(name + to_string(i));
	it = multimedia_files.find(ptr_temp->getName());
	++i;
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new Video file.

shared_ptr<Video> MultimediaManager::create_video 
        (const string & name,
	 unsigned long date,
	 const string & pathname,
	 unsigned int length){
    shared_ptr<Video> ptr_temp (new Video(name,date,pathname,length),
        Video::DeleterVideo ());
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Deserializes a video

shared_ptr<Video> MultimediaManager::create_video (istream & is) {
    shared_ptr<Video> ptr_temp (new Video(), Video::DeleterVideo());
    ptr_temp->read(is);
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new default Film file.

shared_ptr<Film> MultimediaManager::create_film (void){
    shared_ptr<Film> ptr_temp (new Film(), Film::DeleterFilm ());
    //Remember the name
    string name = ptr_temp->getName();
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    int i = 0;
    //The default file has not specified name
    while(it != multimedia_files.end()){
        ptr_temp->setName(name + to_string(i));
	it = multimedia_files.find(ptr_temp->getName());
	++i;
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new Film file with no chapter.

shared_ptr<Film> MultimediaManager::create_film
          (const string & name,
           unsigned long date,
	   const string & pathname){
    shared_ptr<Film> ptr_temp (new Film(name,date,pathname), Film::DeleterFilm());
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new Film file.

shared_ptr<Film> MultimediaManager::create_film
          (const string & name,
           unsigned long date,
	   const string & pathname,
	   unsigned int const chapters[],
	   unsigned int number_chapters){
    shared_ptr<Film> ptr_temp (new Film(name,date,pathname, chapters,
        number_chapters), Film::DeleterFilm());
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Deserialize a film

shared_ptr<Film> MultimediaManager::create_film (istream & is) {
    shared_ptr<Film> ptr_temp (new Film(), Film::DeleterFilm ());
    ptr_temp->read(is);
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(ptr_temp->getName()));
    if (it != multimedia_files.end()){
        throw runtime_error("Error : name already taken");
    }
    this->multimedia_files[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a new group

shared_ptr<Group> MultimediaManager::create (const Group& group){
    shared_ptr<Group> ptr_temp (group.clone());
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(ptr_temp->getName()));
    if (it != groups.end()){
        throw runtime_error("Error : name already taken");
    }
    this->groups[group.getName()] = ptr_temp;
    return ptr_temp;
}

//Create a group

shared_ptr<Group> MultimediaManager::create_group (){
    shared_ptr<Group> ptr_temp (new Group());
    //Remember the name
    string name = ptr_temp->getName();
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(ptr_temp->getName()));
    int i = 0;
    //The default file has not specified name
    while(it != groups.end()){
        ptr_temp->setName(name + to_string(i));
	it = groups.find(ptr_temp->getName());
	++i;
    }
    this->groups[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

//Create a group

shared_ptr<Group> MultimediaManager::create_group (const string& name){
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(name));
    if (it != groups.end()){
        throw runtime_error("Error : name already taken");
    }
    shared_ptr<Group> ptr_temp (new Group(name));
    this->groups[name] = ptr_temp;
    return ptr_temp;
}

//Create a group

shared_ptr<Group> MultimediaManager::create_group (istream & is){
    shared_ptr<Group> ptr_temp (new Group());
    ptr_temp->read(is, this);
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(ptr_temp->getName()));
    if (it != groups.end()){
        throw runtime_error("Error : name already taken");
    }
    this->groups[ptr_temp->getName()] = ptr_temp;
    return ptr_temp;
}

// remove a multimedia file

void MultimediaManager::remove_multimedia (const string & name) {
    map<string,shared_ptr<Group> >::const_iterator
        lit(groups.begin()),
	lend(groups.end());
    map<string,shared_ptr<Multimedia> >::const_iterator it;
    //For all the groups...
    for(;lit!=lend;++lit) {
        //I remove the groups with the given name.
        lit->second->remove(name);
    }
    it = multimedia_files.find(name);
    if (it != multimedia_files.end()) {
        multimedia_files.erase(it);
    } else {
        throw runtime_error("File not found");
    }
    write("manager");
}

//Remove a group

void MultimediaManager::remove_group (const string & name) {
    map<string,shared_ptr<Group> >::const_iterator it;
    it = groups.find(name);
    if (it != groups.end()) {
        groups.erase(name);
    } else {
        throw runtime_error("Group not found");
    }
    write("manager");
}

//Search a multimedia file and print it on the standard output.

string MultimediaManager::search_multimedia (const string & name) const {
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(name));
    if (it != multimedia_files.end())
        return it->second->print();
    else
        return "No file found\n";
}

shared_ptr<Multimedia> MultimediaManager::search_multimedia_ptr (
        const string & name) const {
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(name));
    if (it != multimedia_files.end())
        return it->second;
    else
        return NULL;
}

string MultimediaManager::search_group (const string & name) const {
    map<string,shared_ptr<Group> >::const_iterator it
        (groups.find(name));
    if (it != groups.end())
        return it->second->print();
    else
        return "No group found\n";
}

void MultimediaManager::play (const string & name) const {
    map<string,shared_ptr<Multimedia> >::const_iterator it
        (multimedia_files.find(name));
    if (it != multimedia_files.end())
        it->second->play();
    else
        throw runtime_error("File not found");
}

void MultimediaManager::write (const string & name) const {
    ofstream file(name.c_str(), ios::out | ios::trunc); //Open file
    if (file) {
        map<string,shared_ptr<Multimedia> >::const_iterator it;
        for (it = multimedia_files.begin(); it != multimedia_files.end(); ++it) {
            it->second->write(file);
        }
	map<string,shared_ptr<Group> >::const_iterator itg;
        for (itg = groups.begin(); itg != groups.end(); ++itg) {
            itg->second->write(file);
        }
	file.close();
    } else {
        cout << "Problem when writing the manager" << endl;
    }
}

void MultimediaManager::read (const string & name) {
    ifstream file(name.c_str(), ios::in); //Open file
    if (file) {
        string s;
	while(getline(file, s)) {
           if (s == "PHOTO") {
	       create_photo(file);
	   } else if (s == "VIDEO") {
	       create_video(file);
	   } else if (s == "FILM") {
	       create_film(file);
	   } else if (s == "GROUP") {
	       create_group(file);
	   } else {
	       break;
	   }
	}
    } else {
        cout << "No save found." << endl;
    }
}
