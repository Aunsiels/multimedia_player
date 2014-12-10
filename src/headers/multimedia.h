/*******************************************************************************
//
// \file multimedia.h
// \brief Describe what is a multimedia file
// \author Julien Romero
// \version 0.1
// \date  10/12/2014
//
*******************************************************************************/

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>

/*
* \class Multimedia
* \brief This class represents a multimedia file
*
* All multimedia files inherit from this class.
*/

using namespace std;

class Multimedia {

private:
    string name; //Name of the multimedia file
    long   date; //Date of getting of the object
    string pathname; //Path to the file

public:

    /*
    * \brief Default Constructor
    *
    * Creates a default multimedia object.
    *
    */

    Multimedia(void);

    /*
    * \brief Constructor
    * 
    * Constructor of the Multimedia class.
    *
    * \param name : Name of the multimedia file
    * \param date : Date when the file is added in millis
    * \param pathname : Path to the file
    *
    */

    Multimedia(string name, long date, string pathname);

    /*
    * \brief Destructor
    *
    * Default destructor of this class.
    *
    */

    ~Multimedia(void);
    
    /*
    * \brief Name getter
    *
    * Get the name of the file.
    *
    * \return The name of file/
    *
    */

    virtual string getName (void) const;


};

#endif
