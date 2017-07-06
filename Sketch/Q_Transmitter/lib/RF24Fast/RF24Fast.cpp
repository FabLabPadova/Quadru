#include "RF24Fast.h"

RF24Fast::RF24Fast(const uint8_t p1, const uint8_t p2) : RF24(p1, p2){}

RF24Fast::RF24Fast() : RF24(7, 8){}

void RF24Fast::init(const uint64_t pipe_rx, const uint64_t pipe_tx, Role_RF role, const uint8_t max_size){
    this->begin();
    this->setAutoAck(1);                    // Ensure autoACK is enabled
    this->max_size = constrain(max_size+1, 1, 32);
    this->setPayloadSize(this->max_size);
    this->enableAckPayload();               // Allow optional ack payloads
    this->setRetries(0,15);                 // Smallest time between retries, max no. of retries
    setPipeByRole(pipe_rx, pipe_tx, role);

}//RF24Fast

void RF24Fast::setPipeByRole(const uint64_t pipe_rx, const uint64_t pipe_tx, Role_RF newrole){
    this->role_radio = newrole;
    if (this->role_radio == ROLE_TX){
        this->openWritingPipe(this->pipe_tx = pipe_rx);
        this->openReadingPipe(1,this->pipe_rx = pipe_tx);
        this->stopListening();
    }else {
        this->openWritingPipe(this->pipe_tx = pipe_tx);
        this->openReadingPipe(1,this->pipe_rx = pipe_rx);
        this->startListening();
    }
}

bool RF24Fast::setRole(Role_RF newrole){
    bool res;
    if ((res = this->role_radio != newrole)){
        if (newrole == ROLE_RX)
            setPipeByRole(this->pipe_tx, this->pipe_rx, newrole);
        else
            setPipeByRole(this->pipe_rx, this->pipe_tx, newrole);
    }//if-res
    return res;
}//setRole

bool RF24Fast::was_received(){
    bool prec_received = received_something;
    if (received_something)
        received_something = false;
    return prec_received;
}

Role_RF RF24Fast::getRole(){
    return this->role_radio;
}//getRole

bool RF24Fast::writeString(String s, char term, bool ignore_term ){
    uint8_t buffer[this->max_size];
    memset(buffer, 0, this->max_size);
    uint8_t i=0;
    bool rec_ack = 0;
    while(i<s.length() && i<this->max_size-1){
        buffer[i] = s.charAt(i);
        i++;
    }//while
    if (!ignore_term)
      buffer[i] = term;
    if (!this->write(&buffer, this->max_size))
        return false;
    else{
        while(this->available() && !rec_ack)
          this->read( &rec_ack, 1 );
    }//else
    return rec_ack;
}//writeString

String RF24Fast::readString(char term){
    received_something = false;
    uint8_t buffer[this->max_size];
    memset(buffer, 0, this->max_size);
    byte pipeNo;
    bool received = true;
    String s = "";
    while( this->available(&pipeNo)){
      this->read( &buffer, sizeof(buffer) );
      this->writeAckPayload(pipeNo,&received, 1);
    }//while
    uint8_t i=0;
    while (i<this->max_size && buffer[i] != term){
        s+=String((char)buffer[i]);
        i++;
    }//while
    received_something = s.length() > 0;
    return s;
}//writeString
