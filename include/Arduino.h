#ifndef ARDUINO_H
#define ARDUINO_H

#include <cstdint>
#include <iostream>
#include <SFML/System/Clock.hpp>

#define A0 0
#define A1 1

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Mock hardware state (Defined here since we use a single-unit build)
static int _sim_mouseX = 0;
static int _sim_mouseY = 0;
static bool _sim_btnSpace = false;
static int _sim_frameRate = 60;
static sf::Clock _sim_clock;

inline int analogRead(uint8_t pin) {
    if (pin == A0) return (_sim_mouseX * 1023) / 256;
    if (pin == A1) return (_sim_mouseY * 1023) / 128;
    return 0;
}

inline int digitalRead(uint8_t pin) {
    if (pin == 2) return _sim_btnSpace ? LOW : HIGH;
    return HIGH;
}

inline void pinMode(uint8_t pin, uint8_t mode) {}
inline void digitalWrite(uint8_t pin, uint8_t val) {}

inline unsigned long millis() {
    return _sim_clock.getElapsedTime().asMilliseconds();
}

class SerialMock {
public:
    void begin(int baud) {}
    void print(const char* s) { std::cout << s; }
    void print(int n) { std::cout << n; }
    void println(const char* s) { std::cout << s << std::endl; }
    void println(int n) { std::cout << n << std::endl; }
};

static SerialMock Serial;

#endif
