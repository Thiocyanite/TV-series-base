//
//  ogladadlo.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <iostream>
#include "ogladadlo.h"
#include "blad.h"
#include <fstream>

void ogladadlo::save(std::fstream & plik){
    try {
  plik<<nazwa<<"\n"<<gatunek<<"\n"<<CzasTrwania<<"\n"<<ocena<<"\n";
        
    } catch (...) {
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad; //Wyrzuca wyjątek na wyższy poziom
    }
}

void ogladadlo::load(std::fstream & plik){
    try {
        
        plik>>nazwa>>gatunek>>CzasTrwania>>ocena;
    } catch (...) {
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
    
}

void ogladadlo::setinfo(std::string name, std::string gat, double tim){
    nazwa=name;
    gatunek=gat;
    CzasTrwania=tim;
}

void ogladadlo::prezentujsie(){
    std::cout<<nazwa<<" należy do gatunku "<<gatunek<<".";
}
