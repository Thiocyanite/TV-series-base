//
//  blad.h
//  serialowabaza
//
//  Created by Julia on 06.11.2018.
//  Copyright © 2018 Julia. All rights reserved.
//

#ifndef blad_h
#define blad_h


template <class T>
class blad{
private:
    T wiadomosc;
public:
    void setmessage(T message){wiadomosc=message;};
    void showyourself(){std::cerr<< wiadomosc;};
};


#endif /* blad_h */
