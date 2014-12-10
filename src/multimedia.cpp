/*******************************************************************************
*
* multimedia.cpp by Julien Romero
*
* Describe what is a multimedia file
*
*******************************************************************************/

#include <iostream>
#include <ctime>

#include <multimedia.h>

// Default constructor

Multimedia::Multimedia(void) {
    this.name = "default";
    // Get the time in seconds since 1970, January 1st
    this.date = (long) time(NULL);
    this.pathname = "/"
}

// Constructor with all parameters

Multimedia::M
