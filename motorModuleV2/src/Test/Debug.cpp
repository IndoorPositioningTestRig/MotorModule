#include "Debug.hpp"
#include "Communication/Communicator.hpp"


using namespace Test;

void Debug::log(double setpoint, double output, double encoder) {
 if(_position < MAX_LEN){
    _data[_position++] = setpoint;
    _data[_position++] = output;
    _data[_position++] = encoder;
 }
}

void Debug::print(Communication::Communicator communicator){
    for(int i = 0; i < _position; i++){
        communicator.write_c(1, 0, 3, "hoi Stefan", 10);
    }
}
