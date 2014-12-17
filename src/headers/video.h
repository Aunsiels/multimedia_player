/*******************************************************************************
*
* \file video.h
* \brief Describe what is a video file
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

#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <multimedia.h>

using namespace std;

/*!
* \class Video
* \brief This class represents a video file.
*
*/

class Video : public Multimedia {

private :
    int length; // The length of a video

public:

    /*!
    * \brief Default Constructor
    *
    * Defaut constructor of a video.
    *
    */

    Video(void);

    /*!
    * \brief Constructor
    *
    * Constructor of a video.
    *
    * \param name : Name of the video.
    * \param date : Date when the file is added.
    * \param pathname : Path to the video.
    * \param length : Length of the video in seconds.
    *
    */

    Video(string name, unsigned long date, string pathname, unsigned int length);

    /*!
    * \brief Destructor
    *
    * Default destructor of this class.
    *
    */

    virtual ~Video(void);

    /*!
    * \brief Length getter.
    *
    * Get the length of the video.
    *
    * \return The length of the video.
    *
    */

    virtual unsigned int getLength (void) const;

    /*
    * \brief Length setter
    *
    * Set the length of the video.
    *
    * \param newLength : the new length of the video
    *
    */

    virtual void setLength (unsigned int newLength);

    /*
    * \brief Print description.
    *
    * Print the description of a video to the standard output.
    *
    */

    virtual void print (void) const;

    /*!
    *
    * \brief Display the multimedia file on screen.
    *
    */

    virtual void play (void) const;
};

#endif
