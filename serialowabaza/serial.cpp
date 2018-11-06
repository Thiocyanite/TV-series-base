//
//  serial.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <stdio.h>
#include "serial.h"
void serial::prezentujsie(){
    ogladadlo::prezentujsie();
    std::cout<<"Jest to serial o średniej ocen "<<ocena<<". Czas trwania pojedynczego odcinka wynosi "<<CzasTrwania<<"h.";
}
