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
class zakonczony: public serial { 
private:
    int IloscWyemitowanychOdcinkow;
    char typ;
public:
    void setepisodes(int k){IloscWyemitowanychOdcinkow=k; typ='Z';};
    void save(std::fstream & plik);
    void load(std::fstream & plik);
    void prezentujsie();
    char gettype(){return 'Z';}
};

#endif /* zakonczony_h */
