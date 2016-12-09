#include <SoftwareServo.h>

SoftwareServo *SoftwareServo::first;

#define NO_ANGLE (0xff)
#define MIN_REF_ANGLE 1000
#define MAX_REF_ANGLE 2000
#define MAX_REF_DEGREES 180
#define PRESCALER_VALUE 64L
#define CLOCK_MHZ 16L

SoftwareServo::SoftwareServo() : pin(0),angle(NO_ANGLE),angle_ms(MIN_REF_ANGLE),angle_max(MAX_REF_DEGREES),pulse0(0),min_us(MIN_REF_ANGLE),max_us(MAX_REF_ANGLE),next(0){}

  void SoftwareServo::setMinimumDegrees(uint16_t deg){
    setMinimumUs(map(deg, 0, angle_max, MIN_REF_ANGLE, MAX_REF_ANGLE));
  }

  void SoftwareServo::setMinimumUs(uint16_t t){
    //TODO: if min > max
    min_us = constrain(t, MIN_REF_ANGLE, MAX_REF_ANGLE);
  }

  void SoftwareServo::setMaximumDegrees(uint16_t deg){
    setMaximumUs(map(deg, 0, constrain(deg, 0, MAX_REF_DEGREES), MIN_REF_ANGLE, MAX_REF_ANGLE));
  }

  void SoftwareServo::setMaximumUs(uint16_t t){
    max_us = constrain(t, MIN_REF_ANGLE, MAX_REF_ANGLE);
    angle_max = map(max_us, MIN_REF_ANGLE, MAX_REF_ANGLE, 0, MAX_REF_DEGREES);
  }

  uint8_t SoftwareServo::attach(int pinArg){
    pin = pinArg;
    angle = NO_ANGLE;
    pulse0 = 0;
    next = first;
    first = this;
    digitalWrite(pin,LOW);
    pinMode(pin,OUTPUT);
    return 1;
  }

  void SoftwareServo::detach(){
    for ( SoftwareServo **p = &first; *p != 0; p = &((*p)->next) ) {
      if ( *p == this) {
        *p = this->next;
        this->next = 0;
        return;
      }
    }
  }

  void SoftwareServo::write(int angleArg){
    // bleh, have to use longs to prevent overflow, could be tricky if always a 16MHz clock, but not true
    // That 64L on the end is the TCNT0 prescaler, it will need to change if the clock's prescaler changes,
    // but then there will likely be an overflow problem, so it will have to be handled by a human.
    angle = constrain(angleArg, 0, angle_max);
    angle_ms = map(angle, 0, angle_max, min_us, max_us);
    calculatePulse(angle_ms);
  }

  void SoftwareServo::writeMicroseconds(int ms){
    // bleh, have to use longs to prevent overflow, could be tricky if always a 16MHz clock, but not true
    // That 64L on the end is the TCNT0 prescaler, it will need to change if the clock's prescaler changes,
    // but then there will likely be an overflow problem, so it will have to be handled by a human.
    angle = map(constrain(ms, min_us, max_us), min_us, max_us, 0, angle_max);
    angle_ms = ms;
    calculatePulse(angle_ms);

  }

  void SoftwareServo::calculatePulse(int ms){
    pulse0 = (((CLOCK_MHZ*clockCyclesPerMicrosecond()))*
    ((long)(min_us/CLOCK_MHZ)+( (map(ms, min_us, max_us, 0, max_us-min_us))
    *((max_us-min_us)/CLOCK_MHZ)/(max_us-min_us) ) ))
    /PRESCALER_VALUE;
  }

  uint8_t SoftwareServo::read(){
    return angle;
  }

  uint16_t SoftwareServo::read_ms(){
    return angle_ms;
  }

  uint16_t SoftwareServo::getAngleMax(){
    return angle_max;
  }

  uint8_t SoftwareServo::attached(){
    for ( SoftwareServo *p = first; p != 0; p = p->next ) {
      if ( p == this) return 1;
    }
    return 0;
  }

  void SoftwareServo::refresh(){
    uint8_t count = 0, i = 0;
    uint16_t base = 0;
    SoftwareServo *p;
    static unsigned long lastRefresh = 0;
    unsigned long m = millis();

    // if we haven't wrapped millis, and 20ms have not passed, then don't do anything
    if ( m >= lastRefresh && m < lastRefresh + 20) return;
    lastRefresh = m;

    for ( p = first; p != 0; p = p->next ) if ( p->pulse0) count++;
    if ( count == 0) return;

    // gather all the SoftwareServos in an array
    SoftwareServo *s[count];
    for ( p = first; p != 0; p = p->next ) if ( p->pulse0) s[i++] = p;

    // bubblesort the SoftwareServos by pulse time, ascending order
    for(;;) {
      uint8_t moved = 0;
      for ( i = 1; i < count; i++) {
        if ( s[i]->pulse0 < s[i-1]->pulse0) {
          SoftwareServo *t = s[i];
          s[i] = s[i-1];
          s[i-1] = t;
          moved = 1;
        }
      }
      if ( !moved) break;
    }

    // turn on all the pins
    // Note the timing error here... when you have many SoftwareServos going, the
    // ones at the front will get a pulse that is a few microseconds too long.
    // Figure about 4uS/SoftwareServo after them. This could be compensated, but I feel
    // it is within the margin of error of software SoftwareServos that could catch
    // an extra interrupt handler at any time.
    for ( i = 0; i < count; i++) digitalWrite( s[i]->pin, 1);

    uint8_t start = TCNT0;
    uint8_t now = start;
    uint8_t last = now;

    // Now wait for each pin's time in turn..
    for ( i = 0; i < count; i++) {
      uint16_t go = start + s[i]->pulse0;

      // loop until we reach or pass 'go' time
      for (;;) {
        now = TCNT0;
        if ( now < last) base += 256;
        last = now;

        if ( base+now > go) {
          digitalWrite( s[i]->pin,0);
          break;
        }
      }
    }
  }
