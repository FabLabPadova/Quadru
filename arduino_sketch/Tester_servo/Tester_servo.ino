#include <Servo.h>    //  includo la libreria servo

#define BUTTON_1    2  // pulsante rotazione antioraria con gradi 
#define BUTTON_2    3  // pulsante rotazione oraria gradi 
#define BUTTON_3    4  // pulsante rotazione antioraria con microsecondi
#define BUTTON_4    5  // pulsante rotazione oraria con microsecondi

Servo Servo1;
int gradi0 =  90, gradi1 = 0, gradi2 = 180 ;   
int microsec1  = 700, microsec2  = 2300;
int angle;

void setup () {
  Serial.begin(9600);               // apro la seriale e imposto vla velocita' a 9600
  pinMode(BUTTON_1 , INPUT);        // i pin impostati come input
  pinMode(BUTTON_2 , INPUT);
  pinMode(BUTTON_3 , INPUT);
  pinMode(BUTTON_4 , INPUT);
  Servo1.attach(6, 700, 2350);      // Servo1 e' collegato al pin 6 , limiti minimi e massimi della durata degli impulsi ,
                                    // questo per non forzare il servo nelle due posizioni di finecorsa, si riduce il movimento
                                    // angolare
  Servo1.write (gradi0);            // posizione iniziale del servo
}
void loop () {
  int puls1 = digitalRead(BUTTON_1);
  int puls2 = digitalRead(BUTTON_2);
  int puls3 = digitalRead(BUTTON_3);
  int puls4 = digitalRead(BUTTON_4);
  
  if (digitalRead(BUTTON_1) == HIGH){
    Servo1.write (gradi1);
    angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle);
  }else if (digitalRead(BUTTON_2) == HIGH){
    Servo1.write (gradi2);
    angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle);
  }else if (digitalRead(BUTTON_3) == HIGH)
    Servo1.writeMicroseconds (microsec1);
  else if (digitalRead(BUTTON_4) == HIGH)
    Servo1.writeMicroseconds (microsec2);


  /*  Serial.print("BUTTON_1");
    Serial.println(puls1);
    Serial.print("BUTTON_2");
    Serial.println(puls2);
    Serial.print("BUTTON_3");
    Serial.println(puls3);
    Serial.print("BUTTON_4");
    Serial.println(puls4);
  */
  delay (1000);

}

