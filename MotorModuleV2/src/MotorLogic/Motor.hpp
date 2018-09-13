#ifndef MOTOR_HPP
#define MOTOR_HPP

namespace MotorLogic {
    class Motor {
    public:
        Motor();
        void move(int amount, unsigned short speed);

        static unsigned short clockWise;
        static unsigned short counterClockWise;
        static unsigned short pwmPin;
    private:
        void retract(unsigned short speed);
        void feed(unsigned short speed);
        void stop();
    };
}

#endif // MOTOR_HPP