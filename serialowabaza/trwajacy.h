//
//  trwajacy.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef trwajacy_h
#define trwajacy_h
#include"serial.h"
class trwajacy: public serial { //działa poza load
private:
    int IloscOdcinkowTygodniowo;
    int* DniEmisji;
    char typ = 'T';
public:
    void setemission(int n, int T[]);
    void save(std::fstream & plik);
    void load(std::fstream & plik);
    trwajacy(){};
    ~trwajacy(){delete DniEmisji;};
    void prezentujsie();
};

#endif /* trwajacy_h */
