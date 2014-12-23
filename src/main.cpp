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
#include <multimedia_manager.h>
#include <string>
#include <time.h>
#include <group.h>
#include <tr1/memory>

using std::tr1::shared_ptr;

int main () {
    
    MultimediaManager manager = MultimediaManager();
    shared_ptr<Video> video = manager.create(Video("Le chat",
                            time(NULL),
			    "/home/julien/Téléchargements/Le-Chat-et-l39aspirateur----YouTube.mp4",10));

    unsigned int i;
    unsigned int tab[10];
    for(i =0; i<10;i++){
        tab[i] = i;
    }
    shared_ptr<Film> film0 = manager.create(Film("Le chat2",
                            time(NULL),
			    "/home/julien/Téléchargements/Le-Chat-et-l39aspirateur----YouTube.mp4",tab,10));

    shared_ptr<Photo> photo = manager.create(Photo("id",time(NULL),
                            "/home/julien/Téléchargements/id.jpg", "Paris"));
   
    shared_ptr<Group> group = manager.create(Group ("Test"));
    group->push_back(video);
    group->push_back(film0);
    group->push_back(photo);
    shared_ptr<Group> group1 = manager.create(Group ("Test1"));
    group1->push_back(video);
    manager.search_group("Test");
    manager.search_multimedia("Le chat");
    manager.remove_multimedia("Le chat");
    manager.search_multimedia("Le chat");
    manager.search_group("Test");
    manager.remove_group("Test");
    manager.search_group("Test");
    video->getLength();
    return 0;

}
