#include "Debug.hpp"
#include "Communication/Communicator.hpp"


using namespace Test;

Debug::Debug(Communication::Communicator * communicator) : _communicator(communicator) {}

void Debug::log(double setpoint, double output, double encoder, long deltatime) {
 if(_position < MAX_LEN){
    _data[_position++] = (int16_t)setpoint*10;
    _data[_position++] = (int16_t)output*10;
    _data[_position++] = (int16_t)encoder*10;
    _data[_position++] = (int16_t)deltatime;
 }
}

void Debug::print(){
  // Send data
  _communicator->write_c(1, 0, 3, _data, _position*2);
  // Reset position, so new data can be recorded.
  _position = 0;
}
