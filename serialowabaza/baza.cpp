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

void baza::wczytajwszystko(){
    try{
        std::fstream plik;
        char pom;
        int licznosc;
        plik.open("seriale.txt",std::ios::in);
        if (plik.fail()){
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;
        }
        plik>>licznosc;
        for (int i=0;i<licznosc;i++){
            plik>>pom;
            switch (pom) {
                case 'F':{
                    std::shared_ptr<film> ptrf(new(film));
                    ptrf->load(plik);
                    PulaStalych.push_back(ptrf);
                    break;}
                case 'E':{
                    std::shared_ptr<event> ptre(new(event));
                    ptre->load(plik);
                    Wydarzenia.push_back(ptre);
                    break;}
                case 'T':{
                    std::shared_ptr<trwajacy> ptrt(new(trwajacy));
                    ptrt->load(plik);
                    PulaStalych.push_back(ptrt);
                    break;}
                case 'Z':{
                    std::shared_ptr<zakonczony> ptrz (new(zakonczony));
                    ptrz->load(plik);
                    PulaStalych.push_back(ptrz);
                    break;}
                default:{
                    std::cerr<<"Znaleziono niezidntyfikowany typ.\n";
                    break;}
            }
        }
    }
    catch(blad<std::string> bl){
        bl.showyourself();
    }
    catch(...){
        std::cerr<<"Problem wystąpił, jednak nie wpłynął on na pracę programu. \n";
    }
}

void baza::zapiszwszystko(){
    std::fstream plik;
    plik.open("seriale.txt",std::ios::out);
    plik<<(Wydarzenia.size()+PulaStalych.size())<<"\n";
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter)
        (*iter)->save(plik);
    std::vector<std::shared_ptr<event>>::iterator itek;
    for(itek=Wydarzenia.begin();itek!=Wydarzenia.end();++itek)
        (*itek)->save(plik);
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
    std::cout<<"W bazie jest:\n";
    std::cout<<Wydarzenia.size()<<" wydarzeń,\n";
    int filmy=0,trwajace=0,zakonczone=0;
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for (iter=PulaStalych.begin();iter!=PulaStalych.end();++iter){
        if (((*iter)->gettype())=='F')
            filmy++;
        else {
            if (((*iter)->gettype())=='T')
                trwajace++;
            else zakonczone++;
        }
    }
    std::cout<<filmy<<" filmów,\n"<<(trwajace+zakonczone)<<" seriali, w tym: "<<zakonczone<<" zakończonych i "<<trwajace<<" emitowanych.\n";
}

void baza::dodajwydarzenie(){
    std::shared_ptr<event> wskaznik (new (event));
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
        std::shared_ptr<film> wskaznik (new(film));
        wskaznik->setinfo(nazwa, gatunek, Czas, cyfry);
        wskaznik->setnote(ocena);
        PulaStalych.push_back(wskaznik);}
    else {
        std::cout<<"Czy serial się zakończył? [T/N]\n";
        std::cin>>pom;
        if (pom=='T'){
            std::cout<<"Podaj ilość wyemitowanych odcinków.\n";
            std::cin>>cyfry;
            std::shared_ptr<zakonczony> wskaznik (new(zakonczony));
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
            std::shared_ptr<trwajacy> wskaznik (new(trwajacy));
            wskaznik->setinfo(nazwa, gatunek, Czas);
            wskaznik->setemission(cyfry, tab);
            wskaznik->setnote(ocena);
            PulaStalych.push_back(wskaznik);
        }
    }
}
