//
//  uzytkownik.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include "uzytkownik.h"
#include <string>


void uzytkownik::changehours(){
    std::cout<<"Wprowadź ilość wolnych godzin od poniedziałku do niedzieli. \n";
    for (int i=0;i<7;i++)
        std::cin>>IloscWolnychGodzin[i];
}

void uzytkownik::setinfo(std::string name){
    nazwa=name;
}

void uzytkownik::codzisogladaczeventem(int dzientygodnia, int dzienmiesiaca, int miesiac){
    double zuzyte=0;
    if (!OplaconeEventy.empty()){
        std::vector<std::shared_ptr<event>>::iterator iter;
        for(iter=OplaconeEventy.begin();iter!=OplaconeEventy.end();++iter){
            if ((*iter)->getday()==dzienmiesiaca&&(*iter)->getmonth()==miesiac)
            {std::cout<<"Dzisiaj masz zaplanowane wydarzenie: "<<(*iter)->getname()<<"\n";
                zuzyte=(*iter)->gettime();}
            else if((*iter)->getday()<dzienmiesiaca&&(*iter)->getmonth()<=miesiac){
                iter=OplaconeEventy.erase(iter);
            }
        }
    }
    this->codzisogladac(dzientygodnia,zuzyte);
    
}

void uzytkownik::codzisogladac(int dzien, double zuzyty){ //Zapytać Dominika
    try {
        double wolnegodziny=IloscWolnychGodzin[dzien]-zuzyty;
        std::cout<<"Dziś możesz obejrzeć:\n";
        if (DoObejrzenia.empty()){
            blad<std::string> bl;
            bl.setmessage("Nie masz nic w śledzonych!\n");
            throw bl;
        }

        for(std::vector<std::shared_ptr<ogladadlo>>::iterator iter=DoObejrzenia.begin(); iter!=DoObejrzenia.end();++iter) 
        {
        if (((*iter)-> gettype()) == 'F' && ((*iter)->gettime()) >= wolnegodziny)
        {
            std::cout<<"Film: "<<(*iter)->getname()<<", ";
            wolnegodziny-=((*iter)->gettime());
        }
        else if ( ((*iter)->gettime()) >= 0){
            int odcinki=0;
            while(wolnegodziny>=((*iter)->gettime())){
                odcinki++;
                wolnegodziny-=(*iter)->gettime();}
            if (odcinki>0)
            std::cout<<odcinki<<" odcinków serialu "<<(*iter)->getname()<<", ";
        }}
    } catch (blad<std::string> bl) {
        bl.showyourself();
    }
    std::cout<<"\n";
}

void uzytkownik::usunogladadlo(std::string nazwa){
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for(iter=DoObejrzenia.begin();iter!=DoObejrzenia.end();++iter)
        if ((*iter)->getname()==nazwa)
            iter=DoObejrzenia.erase(iter);
}


void uzytkownik::dodajevent(baza &bazadanych, std::string nazwa){
    std::vector<std::shared_ptr<event>>::iterator iter;
    for (iter=bazadanych.Wydarzenia.begin(); iter!=bazadanych.Wydarzenia.end(); ++iter)
    {if ((*iter)->getname()==nazwa)
        OplaconeEventy.push_back(*iter);
    }
}

void uzytkownik::dodajogladane(baza &bazadanych, std::string nazwa){
    std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
    for(iter=bazadanych.PulaStalych.begin();iter!=bazadanych.PulaStalych.end();++iter)
        if ((*iter)->getname()==nazwa)
            DoObejrzenia.push_back(*iter);
}


void uzytkownik::save(){
    try {
        std::fstream plik;
        plik.open(nazwa, std::ios::out); //przez tą linijkę prawdopodobnie nie uruchomi się na Windowsie - plik bez rozszerzenia (a jest to dość wygodne rozwiązanie).
        if (plik.fail()){
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;
        }
        for(int i=0; i<7;i++){
            plik<<IloscWolnychGodzin[i]<<"\n";
        }
        plik<<DoObejrzenia.size()<<"\n";
        std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
        for (iter=DoObejrzenia.begin();iter!=DoObejrzenia.end();++iter){
            plik<<(*iter)->getname()<<"\n";
        }
        plik<<OplaconeEventy.size()<<"\n";
        std::vector<std::shared_ptr<event>>::iterator itek;
        for(itek=OplaconeEventy.begin();itek!=OplaconeEventy.end();++itek){
            plik<<(*itek)->getname()<<"\n";
        }
        plik.close();
    } catch (blad<std::string> bl) {
        bl.showyourself();
    }
}

void uzytkownik::load(baza &bazadanych){
    try {
        std::fstream plik;
        plik.open(nazwa, std::ios::in);
        if (plik.fail()){
            blad<std::string> bl;
            bl.setmessage("Nie udało się otworzyć pliku.\n");
            throw bl;
        }
        for (int i=0;i<7;i++)
            plik>>IloscWolnychGodzin[i];
        int pom;
        plik>>pom;
        std::string tytul;
        bool flaga;
        for (int i=0;i<pom;i++){
            plik>>tytul;
            std::vector<std::shared_ptr<ogladadlo>>::iterator iter;
            flaga=false;
            for (iter=bazadanych.PulaStalych.begin();iter!=bazadanych.PulaStalych.end();++iter){
                if ((*iter)->getname()==tytul){
                    DoObejrzenia.push_back(*iter);
                    flaga=true;
                }
                if (!flaga){
                    blad<std::string> bl;
                    bl.setmessage("Nie udało się znaleść nic o tej nazwie.\n");
                    bl.showyourself(); //Nie zrobi to nic złego, więc tylko poinformuje użyszkodnika o tym, że coś mogło mu zniknąć.
                }
            }
        }
        plik>>pom;
        for (int i=0; i<pom;i++){
            plik>>tytul;
            std::vector<std::shared_ptr<event>>::iterator iter;
            flaga=false;
            for (iter=bazadanych.Wydarzenia.begin(); iter!=bazadanych.Wydarzenia.end();++iter){
                if ((*iter)->getname()==tytul){
                    OplaconeEventy.push_back(*iter);
                    flaga=true;
                }
            }
            if (!flaga){
                blad<std::string> bl;
                bl.setmessage("Nie udało się znaleść nic o tej nazwie.\n");
                bl.showyourself();
            }
        }
        
        plik.close();
        
    } catch (blad<std::string> bl) {
        blad<int> wyzszyblad;
        wyzszyblad.setmessage(-1);
        throw wyzszyblad;
    }
}
