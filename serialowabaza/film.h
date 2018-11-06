//
//  film.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef film_h
#define film_h
#include"ogladadlo.h"

class film:public ogladadlo{
private:
    int PEGI;
public:
    void save();
    void load();
    void prezentujsie();
    void setinfo(std::string name, std::string gat, double EpisodeTime, int wiek);
};

#endif /* film_h */
