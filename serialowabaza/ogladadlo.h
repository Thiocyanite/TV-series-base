//
//  ogladadlo.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef ogladadlo_h
#define ogladadlo_h
#include <iostream>

#include "blad.h"
class ogladadlo{
protected:
    std::string nazwa;
    std::string gatunek;
    double CzasTrwania; //W godzinach
    double ocena;
    char typ;
public:
    virtual void setinfo(std::string name, std::string gat, double EpisodeTime);
    virtual void setnote(double note){if (ocena>=0&&ocena<=10) ocena=note;};
    double getnote(){return ocena;};
    double gettime(){return CzasTrwania;};
    std::string getspiese(){return gatunek;};
    std::string getname() {return nazwa;};
    virtual void save(std::fstream & plik);
    virtual void load(std::fstream & plik);
    virtual char gettype(){return typ;};
    bool operator<(ogladadlo const &q)const {return ocena<q.ocena;};
    bool operator<=(ogladadlo const &q)const {return ocena<=q.ocena;};
    bool operator>(ogladadlo const &q)const {return ocena>q.ocena;};
    bool operator>=(ogladadlo const &q)const {return ocena>=q.ocena;};
    bool operator==(ogladadlo const &q)const {return ocena==q.ocena;};
    virtual void prezentujsie();
};


#endif /* ogladadlo_h */
