#include <Arduino.h>
#include "Tachometer.h"

Tachometer::Tachometer(uint8_t pin){
    this->_pin = pin;
}

unsigned long Tachometer::measure(unsigned long timeout = 1000000) {
    unsigned long pulse = pulseIn(this->_pin, HIGH, timeout);
    if(pulse > 0) {
        return 60000000 / (pulse * this->_pulseCoefficient);
    } else {
        return 0;
    }
}

bool Tachometer::calibrate() {
    unsigned long pulseHigh = pulseIn(this->_pin, HIGH);
    unsigned long pulseLow = pulseIn(this->_pin, LOW);
    if(pulseHigh > 0 && pulseLow > 0) {
        this->_pulseCoefficient = (pulseHigh / (pulseHigh + pulseLow)) + 1;
        return true;
    } else {
        this->_pulseCoefficient = 1; 
        return false;
    }
}