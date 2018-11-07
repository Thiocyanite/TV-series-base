//
//  zakonczony.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef zakonczony_h
#define zakonczony_h

#include"serial.h"
class zakonczony: public serial { //działa poza load
private:
    int IloscWyemitowanychOdcinkow;
    char typ='Z';
public:
    void setepisodes(int k){IloscWyemitowanychOdcinkow=k;};
    void save(std::fstream & plik);
    void load(std::fstream & plik);
    void prezentujsie();
};

#endif /* zakonczony_h */
