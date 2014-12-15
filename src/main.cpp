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

int main () {

    int i; //for the for

    Multimedia * tab[4];
    tab[0] = new Video();
    tab[1] = new Video("test",11, "/home",100);
    tab[2] = new Photo();
    tab[3] = new Photo("test",11, "/home","Paris");

    /*
    * Le polymorphisme permet d'appeler la fonction print sans connaître
    * le type de l'objet utilisé.
    * En C++, on a le choix entre créer des objets dynamiques (pointeurs,
    * évalués à l'exécution) et statique (sans pointeur, évalués à la
    * compilation).
    * J'ai choisi de faire un tableau contenant des pointeurs de Multimedia.
    * Il faut donc faire des deletes.
    * En Java, la question ne se pose pas : tout passe par des références.
    */

    for (i = 0; i < 4; i++) {
        tab[i]->print();
    }
    for (i = 0; i < 4; i++) {
        delete tab[i];
    }
    return 0;

}
