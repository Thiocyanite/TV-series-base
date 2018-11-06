//
//  zakonczony.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include "zakonczony.h"
void zakonczony::setnumberofepisodes(int n){
    IloscWyemitowanychOdcinkow = n;
    typ='Z';
}

void zakonczony::save(){
    try {
        serial::save();
        std::fstream plik;
        plik.open("seriale.txt", std::ios::out);
        if (plik.fail()){
                blad<std::string> bl;
                bl.setmessage("Nie udało się otworzyć pliku.\n");
                throw bl;}
    }
        catch(...){
            blad<int> wyzszyblad;
            wyzszyblad.setmessage(-1);
            throw wyzszyblad;
    }
}
void zakonczony::load(){
    serial::load();
    std::fstream plik;
    plik.open("seriale.txt", std::ios::in);
    plik>>IloscWyemitowanychOdcinkow;
    plik.close();
}

void zakonczony::prezentujsie(){
    serial::prezentujsie();
    std::cout<<"Emisja się zakończyła, ilość odcinków: "<<IloscWyemitowanychOdcinkow<<"\n";
}
