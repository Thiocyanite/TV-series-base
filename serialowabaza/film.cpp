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
void film::save(std::fstream & plik){
    try {
        ogladadlo::save(plik);
        plik<<PEGI<<"\n";
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

void film::load(std::fstream & plik){
    try {
        ogladadlo::load(plik);
        
        plik>>PEGI;

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
