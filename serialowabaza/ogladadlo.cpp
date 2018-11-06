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

void ogladadlo::save(){
    try {
        std::fstream plik;
        plik.open("seriale.txt", std::ios::out);
        if (plik.fail()){
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;}
    plik<<typ<<"\n"<<nazwa<<"\n"<<gatunek<<"\n"<<CzasTrwania<<"\n"<<ocena<<"\n";
        plik.close();
        
    } catch (blad<std::string> bl) {
        bl.showyourself();
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad; //wyrzuca wyjątek na wyższy poziom
    }
}

void ogladadlo::load(){
    try {
        std::fstream plik;
        plik.open("seriale.txt",std::ios::in);
        if (plik.fail()){
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;
        }
        plik>>nazwa>>gatunek>>CzasTrwania>>ocena;
        plik.close();
    } catch (blad<std::string> bl) {
        bl.showyourself();
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
