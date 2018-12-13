#include "Debug.hpp"
#include "Communication/Communicator.hpp"


using namespace Test;

void Debug::log(double setpoint, double output, double encoder, long deltatime) {
 if(_position < MAX_LEN){
    _data[_position++] = (int16_t)setpoint*10;
    _data[_position++] = (int16_t)output*10;
    _data[_position++] = (int16_t)encoder*10;
    _data[_position++] = (int16_t)deltatime;
 }
}

void Debug::print(Communication::Communicator * communicator){
    //int16_t list[6] = {1000,2000,3000,-4000, -5000, -6000};
    communicator->write_c(1, 0, 3, _data, _position*2);
    //TODO clear _data when print is done!
}