#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"

namespace MotorLogic {
    class Logic {
    public:
        Logic();
        explicit Logic(unsigned short speed);
        void move(int len);
        void setSpeed(unsigned short speed);
    private:
        unsigned short _speed;
        Motor _motor;
    };
}

#endif // LOGIC_HPP