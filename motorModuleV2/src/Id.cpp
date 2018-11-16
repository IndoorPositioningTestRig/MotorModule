#include <Id.hpp>
#include <EEPROM.h>


Id::Id(){
    id = readId();
}

void Id::writeId(byte id){
    EEPROM.write(ID_ADDR, id);
}

byte Id::readId(){
    id = EEPROM.read(ID_ADDR);
}