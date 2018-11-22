#include <Id.hpp>
#include <EEPROM.h>

Id::Id()
{
    id = 0;
}

void Id::putId(int id)
{
    EEPROM.put(ID_ADDR, id);
}

int Id::getId()
{
    if (id == 0)
    {
        EEPROM.get(ID_ADDR, id);
    }
    return id;
}