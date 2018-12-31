#pragma once
#include <inttypes.h>

class Tachometer {
    public:
        Tachometer(uint8_t pin);

        unsigned long measure(unsigned long timeout = 1000000);
        bool calibrate();
    private:
        uint8_t _pin;
        float _pulseCoefficient;
};