#ifndef ID_HPP
#define ID_HPP

#include <Arduino.h>


class Id
{
public:
explicit Id();
    void putId(int id);
    int getId();
private:
    const int ID_ADDR = 0;
    int id;
};


#endif