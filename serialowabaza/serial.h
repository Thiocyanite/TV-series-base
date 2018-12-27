//
//  serial.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef serial_h
#define serial_h
#include"ogladadlo.h"
#include <fstream>
class serial:public ogladadlo{
public:
    virtual void prezentujsie();
    virtual void save(std::fstream &plik);
    
};
#endif /* serial_h */
