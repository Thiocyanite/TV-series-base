//
//  event.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef event_h
#define event_h

class event{ //działa poza load
private:
    std::string nazwa;
    std::string typ;
    double CzasTrwania;
    int data[2];
    double cena;
public:
    void setinfo(std::string name, std::string type, double time, int dzien, int miesiac, double cen);
    std::string getname(){return nazwa;};
    std::string gettype(){return typ;};
    double gettime(){return CzasTrwania;};
    int getday(){return data[0];};
    int getmonth(){return data[1];};
    void save(std::fstream & plik);
    void load(std::fstream & plik);
    void prezentujsie();
};
#endif /* event_h */
