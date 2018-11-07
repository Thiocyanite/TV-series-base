//
//  uzytkownik.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef uzytkownik_h
#define uzytkownik_h

#include <memory>
#include "ogladadlo.h"
#include "event.h"
#include <vector>
#include "baza.h"
class uzytkownik{ //działa poza load
private:
    std::string nazwa;
    std::vector<std::shared_ptr<ogladadlo>> DoObejrzenia;
    std::vector<std::shared_ptr<event>> OplaconeEventy;
    double IloscWolnychGodzin[7];
public:
    void setinfo(std::string name){nazwa=name;};
    void changehours(double *T);
    void load();
    void save();
    void usunogladane(std::string nazwa);
    void dodajogladane(baza bazadanych, std::string nazwa);
    void dodajevent(baza bazadanych, std::string nazwa);
    void codzisogladaczeventem(int dzientygodnia, int dzienmiesiaca, int miesiac);
    void codzisogladac(int dzien, double zuzyty = 0);
    void usunogladadlo(std::string nazwa);
    void operator+=(std::string nazwa){this->dodajogladane(nazwa);};
    void operator-=(std::string nazwa){this->usunogladadlo(nazwa);};
};

#endif /* uzytkownik_h */
