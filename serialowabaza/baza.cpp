//
//  baza.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "baza.h"
#include "film.h"
#include "zakonczony.h"
#include "trwajacy.h"
#include "memory"
#include "event.h"
#include <vector>

void baza::wczytajuzytkownika(std::string nazwa){
    aktualny=new uzytkownik;
    aktualny->setinfo(nazwa);
    aktualny->load();
}

void baza::stworzuzytkownika(std::string nazwa){
    if (aktualny!=nullptr)
        delete aktualny;
    aktualny=new uzytkownik;
    aktualny->setinfo(nazwa);
    std::cout<<"Podaj ilość wolnych godzin, od poniedziałku do piątku\n";
    double T[7];
    for (int i=0; i<7; i++) {
        std::cin>>T[i];
    }
    aktualny->changehours(T);
}


void baza::zapiszwszystko(){
    std::fstream plik;
    plik.open("seriale.txt",std::ios::out);
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter)
        (*iter)->save(plik);
    std::vector<std::shared_ptr<event>>::iterator itek;
    for(itek=Wydarzenia.begin();itek!=Wydarzenia.end();++itek)
        (*itek)->save(plik);
    aktualny->save();
}

void baza::gatunek(std::string gat){
        std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
        for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter)
            if ((*iter)->getspiese()==gat)
            (*iter)->prezentujsie();
}

void baza::powyzej(double ocena){
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter)
        if ((*iter)->getnote()>=ocena)
        (*iter)->prezentujsie();
}

void baza::wszystkieogladadla(){
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter)
        (*iter)->prezentujsie();
}

void baza::wszystkieeventy(){
    std::cout<<"W bazie znajdują się następujące wydarzenia:\n";
    std::vector<std::shared_ptr<event>>::iterator iter;
    for (iter=Wydarzenia.begin();iter!=Wydarzenia.end();++iter)
        (*iter)->prezentujsie();
}


void baza::statystyki(){
    int seriale=0, filmy=0, trwajace=0, zakonczone=0;
    std::cout<<"W bazie jest:\n";
    std::cout<<Wydarzenia.size()<<" wydarzeń \n";
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for(iter=PulaStalych.begin();iter!=PulaStalych.end();++iter){
        if ((*iter)->gettype()=='F') filmy++;
        else{
            seriale++;
            if ((*iter)->gettype()=='Z') zakonczone++;
            else trwajace++;
        }
    }
    std::cout<<filmy<<"filmów \n"<<seriale<<" seriali, w tym: \n"<<zakonczone<<" zakończone i "<<trwajace<<" trwających.\n";
}

void baza::dodajwydarzenie(){
    std::shared_ptr<event> wskaznik;
    std::string nazwa,typ;
    int data[2];
    double cena, czas;
    std::cout<<"Podaj nazwę oraz rodzaj wydarzenia. Następnie wprowadź datę [dzień i miesiąc],szacowany czas trwania a także cenę biletu normalnego.\n";
    std::cin>>nazwa>>typ>>data[0]>>data[1]>>czas>>cena;
    wskaznik->setinfo(nazwa, typ, czas, data[0], data[1], cena);
    Wydarzenia.push_back(wskaznik);
}

void baza::dodajogladadlo(){
    char pom;
    std::cout<<"Czy chcesz dodać film, czy serial? [F/S]\n";
    std::cin>>pom;
    std::string nazwa,gatunek;
    double Czas, ocena;
    int cyfry;
    std::cout<<"Wprowadź nazwę, gatunek, czas trwania oraz ocenę [0-10]\n";
    std::cin>>nazwa>>gatunek>>Czas>>ocena;
    if (pom=='F'){
        std::cout<<"Wprowadź ograniczenie wiekowe [minimalny wiek]\n";
        std::cin>>cyfry;
        std::shared_ptr<film> wskaznik;
        wskaznik->setinfo(nazwa, gatunek, Czas, cyfry);
        wskaznik->setnote(ocena);
        PulaStalych.push_back(wskaznik);}
    else {
        std::cout<<"Czy serial się zakończył? [T/N]\n";
        std::cin>>pom;
        if (pom=='T'){
            std::cout<<"Podaj ilość wyemitowanych odcinków.\n";
            std::cin>>cyfry;
            std::shared_ptr<zakonczony> wskaznik;
            wskaznik->setinfo(nazwa, gatunek, Czas);
            wskaznik->setepisodes(cyfry);
            wskaznik->setnote(ocena);
            PulaStalych.push_back(wskaznik);
        }
        else {
            std::cout<<"Ile razy tygodniowo jest emitowany?\n";
            std::cin>>cyfry;
            int *tab= new int[cyfry];
            std::cout<<"Wprowadź dni emisji. [0-poniedziałek]\n";
            for (int i=0;i<cyfry;i++)
                std::cin>>tab[i];
            std::shared_ptr<trwajacy> wskaznik;
            wskaznik->setinfo(nazwa, gatunek, Czas);
            wskaznik->setemission(cyfry, tab);
            wskaznik->setnote(ocena);
            PulaStalych.push_back(wskaznik);
        }
    }
}
