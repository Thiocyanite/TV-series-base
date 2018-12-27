//
//  main.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//  Used IDE: XCode 9.4; Used OS: Mac OS 10.13.6
//  This project probably will not work correctly with Windows, becouse of 100th line in uzytkownik.cpp.


#include <iostream>
#include <fstream>
#include "blad.h"
#include "ogladadlo.h"
#include "event.h"
#include "serial.h"
#include "zakonczony.h"
#include "trwajacy.h"
#include "film.h"
#include "uzytkownik.h"



void ladujuzytkownika(std::shared_ptr<uzytkownik> uz, baza &bazadanych){
    char pom;
    std::string nazwa;
    std::cout<<"Czy jesteś zarejestwowanym użytkownikiem? [T/N]\n";
    std::cin>>pom;
    std::cout<<"Wprowadź nazwę użytkowniks.\n";
    std::cin>>nazwa;
    uz->setinfo(nazwa);
    if (pom=='T'){
        try {
            
            uz->load(bazadanych);
        } catch (...) {
            pom='F';
        }
    }
    if (pom=='F'){
        uz->changehours();
    }
}


void help(){
    std::cout<<"Opis programu:\n";
    std::cout<<"Działanie programu:\t h wyświetl pomoc \t q wyjdź \t s zapisz\n";
    std::cout<<"Działanie bazy: \t b wyświetl wydarzenia \n";
    std::cout<<"c wyświetl filmy i seriale \t d wyświetl z oceną powyżej X \t e z gatunku X\n";
    std::cout<<"Edycja bazy: \t f dodaj film lub serial \t g dodaj wydarzenie\n";
    std::cout<<"Użytkownik: \t i zmień wolne godziny\t j dodaj wydarzenie \t k dodaj film lub serial do obejrzenia \n";
    std::cout<<"l usuń serial lub film ze śledzonych\t m co obejrzeć\t n co obejrzeć z wydarzeniami \t o przełącz użytkownika\n";
}

int main(int argc, const char * argv[]) {
    std::shared_ptr<baza> glownabaza(new(baza));
    std::shared_ptr<uzytkownik> uzyszkodnik (new(uzytkownik));
    char sterowny;
    double przecinek;
    glownabaza->wczytajwszystko();
    std::string nazwa;
    int data[3];
    ladujuzytkownika(uzyszkodnik, (*glownabaza));
    sterowny='h';
    while (sterowny!='q') {
        switch (sterowny) {
            case 'a':
                glownabaza->statystyki();
                break;
            case 'b':
                glownabaza->wszystkieeventy();
                break;
            case 'c':
                glownabaza->wszystkieogladadla();
                break;
            case 'd':
                std::cout<<"Wprowadź minimalną ocenę [0-10]\n";
                std::cin>>przecinek;
                glownabaza->powyzej(przecinek);
                break;
            case 'e':
                std::cout<<"Wprowadź nazwę gatunku.\n";
                std::cin>>nazwa;
                glownabaza->gatunek(nazwa);
                break;
            case 'h':
                help();
                break;
            case 'f':
                glownabaza->dodajogladadlo();
                glownabaza->zapiszwszystko();
                break;
            case 'g':
                glownabaza->dodajwydarzenie();
                glownabaza->zapiszwszystko();
                break;
            case 'i':
                uzyszkodnik->changehours();
                uzyszkodnik->save();
                break;
            case 'j':
                std::cout<<"Podaj nazwę wydarzenia \n";
                std::cin>>nazwa;
                uzyszkodnik->dodajevent((*glownabaza),nazwa);
                uzyszkodnik->save();
                break;
            case 'k':
                std::cout<<"Podaj nazwę filmu lub serialu \n";
                std::cin>>nazwa;
                //(*uzyszkodnik)+=nazwa;
                uzyszkodnik->dodajogladane((*glownabaza), nazwa);
                break;
            case 'l':
                std::cout<<"Podaj nazwę filmu lub serialu \n";
                std::cin>>nazwa;
                (*uzyszkodnik)-=nazwa;
                uzyszkodnik->save();
                break;
            case 'm':
                std::cout<<"Podaj dzień tygodnia [0-poniedziałek]\n";
                std::cin>>data[0];
                uzyszkodnik->codzisogladac(data[0],0);
                break;
            case 'n':
                std::cout<<"Podaj dzień tygodnia, dzień miesiąca i miesiąc \n";
                std::cin>>data[0]>>data[1]>>data[2];
                uzyszkodnik->codzisogladaczeventem(data[0], data[1], data[2]);
                break;
            case 's':
                uzyszkodnik->save();
                glownabaza->zapiszwszystko();
                break;
            case 'o':
                uzyszkodnik->save();
                ladujuzytkownika(uzyszkodnik, (*glownabaza));
                break;
            default:
                break;
        }
        std::cout<<"Wprowadź polecenie.\n";
        std::cin>>sterowny;
    }
    uzyszkodnik->save();
    glownabaza->zapiszwszystko();
    return 0;
}
