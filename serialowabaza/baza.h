//
//  baza.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef baza_h
#define baza_h
#include <vector>
#include<memory>

#include "ogladadlo.h"
#include "event.h"
#include "uzytkownik.h"

class baza{
private:
    std::vector<std::shared_ptr<ogladadlo>> PulaStalych;
    std::vector<std::shared_ptr<event>> Wydarzenia;
    uzytkownik *aktualny;
public:
    void wczytajuzytkownika(std::string nazwa);
    void stworzuzytkownika(std::string nazwa);
    void dodajwydarzenie();
    void dodajogladadlo();
    void zapiszwszystko();
    void wczytajwszystko();
    void statystyki();
    void wszystkieogladadla();
    void wszystkieeventy();
    void powyzej(double ocena);
    void gatunek(std::string gat);
    void baza(){aktualny=nullptr};
    void ~baza(){if (aktualny!=nullptr) delete aktualny;};
    friend class uzytkownik;
};
#endif /* baza_h */
