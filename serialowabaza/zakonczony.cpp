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


void zakonczony::save(std::fstream & plik){
    try {
        serial::save(plik);
        plik<<IloscWyemitowanychOdcinkow<<"\n";
    }
        catch(...){
            blad<int> wyzszyblad;
            wyzszyblad.setmessage(-1);
            throw wyzszyblad;
    }
}
void zakonczony::load(std::fstream & plik){
    serial::load(plik);
    plik>>IloscWyemitowanychOdcinkow;
}

void zakonczony::prezentujsie(){
    serial::prezentujsie();
    std::cout<<"Emisja się zakończyła, ilość odcinków: "<<IloscWyemitowanychOdcinkow<<"\n";
}
