//
//  event.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "event.h"
#include "blad.h"
void event::setinfo(std::string name, std::string type, double time, int dzien, int miesiac, double cen){
    nazwa=name;
    typ=type;
    cena= cen;
    if (time>0)
        CzasTrwania=time;
    if (dzien>0&&dzien<32)
        data[0]=dzien;
    else data[0]=1;
    if (miesiac>0 &&miesiac<13)
        data[1]=miesiac;
    else data[1]=1;
}

void event::load(std::fstream & plik){
    try {

        plik>>nazwa>>typ>>CzasTrwania>>data[0]>>data[1]>>cena;
        if (nazwa==""||typ==""||CzasTrwania==0||data[0]==0||data[1]==0){
            blad<std::string> bl;
            bl.setmessage("Nie zaladowano poprawnie wydarzenia.\n");
            throw bl;}

    } catch (blad<std::string> bl) {
        bl.showyourself();
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
    
}

void event::save(std::fstream & plik){
    try {
plik<<"E\n"<<nazwa<<"\n"<<typ<<"\n"<<CzasTrwania<<"\n"<<data[0]<<"\n"<<data[1]<<"\n"<<cena<<"\n";
    } catch (...) {
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
}

void event::prezentujsie(){
    std::cout<<nazwa<<" to wydarzenie typu "<<typ<<". Można je obejrzeć "<<data[0]<<"."<<data[1]<<" za "<<cena<<"zł.\n";
}
