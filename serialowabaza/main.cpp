//
//  main.cpp
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#include <iostream>
#include "blad.h"
#include "ogladadlo.h"
#include "event.h"
#include "film.h"

int main(int argc, const char * argv[]) {
    ogladadlo *obejrzyj;
    obejrzyj= new ogladadlo;
    obejrzyj->load();
    std::cout<<obejrzyj->getname();
    std::cout << "Hello, World!\n";
    return 0;
}
