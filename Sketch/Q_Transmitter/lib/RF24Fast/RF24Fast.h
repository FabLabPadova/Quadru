#ifndef RF24FAST_H
#define RF24FAST_H

#include <Arduino.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define MAX_BUFFER_SIZE 32

typedef enum { ROLE_TX = 1, ROLE_RX } Role_RF;

class RF24Fast: public RF24{

    private:
        Role_RF role_radio;
        bool received_something = false;
        uint64_t pipe_rx, pipe_tx;
        uint8_t max_size;
        void setPipeByRole(const uint64_t pipe_rx, const uint64_t pipe_tx, Role_RF newrole);

    public:
        RF24Fast(const uint8_t p1 , const uint8_t p2 );

        RF24Fast();

        void init(const uint64_t pipe_rx, const uint64_t pipe_tx, Role_RF role, const uint8_t max_size = MAX_BUFFER_SIZE);

        bool setRole(Role_RF newrole);

        bool writeString(String s, char term = ';', bool ignore_term = false);

        bool was_received();

        String readString(char term = ';');

        Role_RF getRole();

};//RF24Fast

#endif
