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
#include "multimedia.h"
#include "group.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include <tr1/memory>

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

    virtual ~MultimediaManager(void);

    /*!
    * \brief Creates a default photo.
    *
    * Add a default photo to the manager.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Photo> create_photo (void);

    /*!
    * \brief Creates a photo file.
    *
    * Add a photo file in the manager.
    *
    * \param name : The name of the photo.
    * \param date : The date of the creation of the object, in seconds
    * \param pathname : The path to the file.
    * \param place : The place where the photo was taken
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Photo> create_photo
        (const string & name,
	 unsigned long date,
	 const string & pathname,
	 const string & place);

    /*!
    * \brief Creates a default video.
    *
    * Add a video file in the manager.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Video> create_video (void);

    /*!
    * \brief Creates a video.
    *
    * Add a video file in the manager.
    *
    * \param name : The name of the video
    * \param date : The date when the file was created
    * \param pathname : The path to the video.
    * \param length : The length of the video.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Video> create_video
        (const string & name,
	 unsigned long date,
	 const string & pathname,
	 unsigned int length);

    /*!
    * \brief Creates a default film.
    *
    * Add a film file in the manager.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Film> create_film (void);

    /*!
    * \brief Creates a film with no chapter.
    *
    * Add a film file in the manager.
    *
    * \param name : Name of the film.
    * \param date : The date when the file was created.
    * \param pathname : The path to the file.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Film> create_film 
          (const string & name,
           unsigned long date,
	   const string & pathname);

    /*!
    * \brief Creates a film.
    *
    * Add a film file in the manager.
    *
    * \param name : Name of the film.
    * \param date : The date when the file was created.
    * \param pathname : The path to the file.
    * \param chapters : The array the the length of the chapters.
    * \param number_chapters : The number of chapter in the film.
    *
    * \return A shared pointer to the object created.
    */

    virtual shared_ptr<Film> create_film 
          (const string & name,
           unsigned long date,
	   const string & pathname,
	   unsigned int const chapters[],
	   unsigned int number_chapters);

    /*!
    * \brief Creates a group.
    *
    * Create a new group and add it to the manager.
    *
    * \param group : the group to create.
    *
    * \return A shared pointer to the group created.
    */

    virtual shared_ptr<Group> create (const Group& group);

    /*!
    * \brief Creates a default group.
    *
    * Create a new group and add it to the manager.
    *
    * \return A shared pointer to the group created.
    */

    virtual shared_ptr<Group> create_group ();

    /*!
    * \brief Creates a group.
    *
    * Create a new group and add it to the manager.
    *
    * \param group : the name of the group to create.
    *
    * \return A shared pointer to the group created.
    */

    virtual shared_ptr<Group> create_group (const string&);

    /*!
    * \brief Remove a multimedia file.
    *
    * Remove a multimedia file from the manager.
    *
    * \param The name of the multimedia file to remove
    *
    */

    virtual void remove_multimedia (const string & name);

    /*!
    * \brief Remove a group.
    *
    * Remove a group from the manager.
    *
    * \param name : the name of the group to remove
    *
    */

    virtual void remove_group (const string & name);

    /*!
    * \brief Search a multimedia file and print it.
    *
    * Search a multimedia file by its name and print it.
    *
    * \param name : The name of the searched multimedia file.
    *
    */

    virtual string search_multimedia (const string & name) const;

    /*!
    * \brief Search a group and print it.
    *
    * Search a group by its name and print it.
    *
    * \param name : The name of the searched group.
    *
    */

    virtual string search_group (const string & name) const;

    /*!
    * \brief Play a multimedia file.
    *
    * Search by name a multimedia file and play it.
    *
    * \param name : The name of the file to play.
    *
    */

    virtual void play (const string & name) const;
};

#endif
