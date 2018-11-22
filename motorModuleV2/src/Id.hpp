#ifndef ID_HPP
#define ID_HPP

#include <Arduino.h>


class Id
{
public:
explicit Id();
    void writeId(byte id);
    byte readId();
    byte id;
private:
    const int ID_ADDR = 0;

};


#endif