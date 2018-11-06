//
//  film.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include "film.h"
void film::save(){
    try {
        ogladadlo::save();
        std::fstream plik;
        plik.open("seriale.txt",std::ios::out);
        if (plik.fail()){
            {
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;}
        }
        plik<<PEGI;
        plik.close();
    } catch (blad<std::string> bl) {
        bl.showyourself();
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
    catch(...){
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
}

void film::load(){
    try {
        ogladadlo::load();
        std::fstream plik;
        plik.open("seriale.txt",std::ios::in);
        if (plik.fail()){
                blad<std::string> bl;
                bl.setmessage("Nie udało się otworzyć pliku.\n");
                throw bl;}
        plik>>PEGI;
            plik.close();
        } catch (blad<std::string> bl) {
            bl.showyourself();
            blad<int> wyzszyblad;
            wyzszyblad.setmessage(-1);
            throw wyzszyblad;
        }
        catch(...){
            blad<int> wyzszyblad;
            wyzszyblad.setmessage(-1);
            throw wyzszyblad;
        }
    
}

void film::prezentujsie(){
    ogladadlo::prezentujsie();
    std::cout<<"Jest to film o średniej ocen "<<ocena<<". Trwa "<<CzasTrwania<<", a w klasyfikacji PEGI został oznaczony jako "<<PEGI<<"\n";
}

void film::setinfo(std::string name, std::string gat, double EpisodeTime, int wiek){
    ogladadlo::setinfo(name, gat, EpisodeTime);
    PEGI=wiek;
}
