#ifndef ENCODER_MANUAL_HPP
#define ENCODER_MANUAL_HPP

#include "Arduino.h"
#include "RotaryEncoder.h"

namespace MotorLogic {
    class EncoderManual {
        public:
            EncoderManual();
            long read();
            
            static RotaryEncoder _encoder;
        private:

    };

}

#endif // ENCODER_MANUAL_HPP