#ifndef SoftwareServo_h
#define SoftwareServo_h

#include <Arduino.h>
#include <inttypes.h>

class SoftwareServo
{
  private:
    uint8_t pin;
    uint8_t angle;       // in degrees
    uint16_t angle_ms;
    uint16_t angle_max;
    uint16_t angle_min;
    uint16_t pulse0;     // pulse width in TCNT0 counts
    uint16_t min_us;       // minimum pulse, 16uS units  (default is 34)
    uint16_t max_us;       // maximum pulse, 16uS units, 0-4ms range (default is 150)
    class SoftwareServo *next;
    static SoftwareServo* first;
    void calculatePulse(int);
  public:
    SoftwareServo();
    uint8_t attach(int);     // attach to a pin, sets pinMode, returns 0 on failure, won't
                             // position the servo until a subsequent write() happens
    void detach();
    void write(int);         // specify the angle in degrees, 0 to 180
    void writeMicroseconds(int);         // specify the angle in microseconds.
    uint8_t read();
    uint16_t read_ms();
    uint8_t attached();
    void setMinimumUs(uint16_t);  // pulse length for 0 degrees in microseconds
    void setMaximumUs(uint16_t);  // pulse length for 180 degrees in microseconds
    void setMinimumDegrees(uint16_t);  // pulse length for 0 degrees in microseconds
    void setMaximumDegrees(uint16_t);  // pulse length for 180 degrees in microseconds
    static void refresh();    // must be called at least every 50ms or so to keep servo alive
    uint16_t getAngleMax();
    uint16_t getAngleMin();
    String info();
                              // you can call more often, it won't happen more than once every 20ms
};

#endif
