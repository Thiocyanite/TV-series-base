//
//  trwajacy.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include "trwajacy.h"
#include <fstream>

void trwajacy::setemission(int n, int T[]){
    IloscOdcinkowTygodniowo=n;
    typ='T';
    DniEmisji=new int[IloscOdcinkowTygodniowo];
    for (int i=0;i<IloscOdcinkowTygodniowo;i++)
        DniEmisji[i]=T[i];
}


void trwajacy::save(std::fstream & plik){
    try {
        plik<<"T\n";
        serial::save(plik);
        plik<<IloscOdcinkowTygodniowo<<"\n";
        for(int i=0;i<IloscOdcinkowTygodniowo;i++)
            plik<<DniEmisji[i]<<"\n";
        
    }
    catch(...){
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
}
void trwajacy::load(std::fstream & plik){
    serial::load(plik);
    typ='T';
    plik>>IloscOdcinkowTygodniowo;
    DniEmisji= new int[IloscOdcinkowTygodniowo];
    for (int i=0; i<IloscOdcinkowTygodniowo;i++)
        plik>>DniEmisji[i];
    plik.close();
}
void trwajacy::prezentujsie(){
    serial::prezentujsie();
    std::cout<<"Jest on emitowany w następujące dni tygodnia: ";
    for (int i=0 ;i<IloscOdcinkowTygodniowo;i++){
        std::cout<<DniEmisji[i]<<", ";
    }
    std::cout<<"\n";
}
