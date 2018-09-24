#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "RotaryEncoder.hpp"

namespace MotorLogic {

    class Counter {
    public:
        Counter();
        long getCount();
        static RotaryEncoder * encoder;
    private:
    };
}

#endif // ENCODER_HPP
