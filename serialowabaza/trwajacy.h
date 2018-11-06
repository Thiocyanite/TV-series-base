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
public:
    void setemission(int n, int T[]);
    void save();
    void load();
    trwajacy(){};
    ~trwajacy(){delete DniEmisji;};
    void prezentujsie();
};

#endif /* trwajacy_h */
