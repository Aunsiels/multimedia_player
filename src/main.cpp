/*******************************************************************************
*
* main.cpp by Julien Romero
*
* Main function of the program.
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
#include "headers/multimedia.h"
#include "headers/video.h"
#include "headers/photo.h"
#include <film.h>
#include <string>

Film * createFilm(string name, unsigned int n);

int main () {
    
    Film * film0 = createFilm("0",0);
    Film * film1 = createFilm("1",1);
    Film * film2 = createFilm("2",2);
    film0->print();
    film0->printChapters();
    film1->print();
    film1->printChapters();
    film2->print();
    film2->printChapters();

    unsigned int i;
    unsigned int tab[11];
    for(i =0; i<11;i++){
        tab[i] = 100 + i;
    }

    film0->setChapters(tab,11);
    film0->print();
    film0->printChapters();


    delete film1;
    delete film2;
    delete film0;
    return 0;

}

Film * createFilm(string name, unsigned int n) {

    unsigned int i;
    unsigned int tab[10];
    for(i =0; i<10;i++){
        tab[i] = n + i;
    }
    //tab is erased at the end of the function
    return new Film(name,0,"/",tab,10);
}
