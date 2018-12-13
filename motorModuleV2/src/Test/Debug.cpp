#include "Debug.hpp"
#include "Communication/Communicator.hpp"


using namespace Test;

void Debug::log(double setpoint, double output, double encoder) {
 if(_position < MAX_LEN){
    _data[_position++] = (uint16_t)setpoint*10;
    _data[_position++] = (uint16_t)output*10;
    _data[_position++] = (uint16_t)encoder*10;
 }
}

void Debug::print(Communication::Communicator * communicator){
        //communicator.write_c(1, 0, 3, _data, _position*2*3);
    communicator->write_c(1, 0, 2, (uint8_t*)"{\"command\":\"kutrs485\"}", 22);

    // for(int i = 0; i < _position; i++){
    //     communicator.write_c(1, 0, 3, _data, 10);
    // }
}
