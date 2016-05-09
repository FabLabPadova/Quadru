#include <Servo.h>    //  includo la libreria servo

#define BUTTON_1    2  // pulsante rotazione antioraria con gradi 
#define BUTTON_2    3  // pulsante rotazione oraria gradi 
#define BUTTON_3    4  // pulsante rotazione antioraria con microsecondi
#define BUTTON_4    5  // pulsante rotazione oraria con microsecondi
#define GRADI_0 90
#define GRADI_1 0
#define GRADI_2 180
#define MICROSEC1 700
#define MICROSEC2 2300

Servo Servo1;
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
  Servo1.write (GRADI_0);           // posizione iniziale del servo
}
void loop () {  
  if (digitalRead(BUTTON_1) == HIGH){
    Servo1.write (GRADI_1);
    angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle);
  }else if (digitalRead(BUTTON_2) == HIGH){
    Servo1.write (GRADI_2);
    angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle);
  }else if (digitalRead(BUTTON_3) == HIGH)
    Servo1.writeMicroseconds (MICROSEC1);
  else if (digitalRead(BUTTON_4) == HIGH)
    Servo1.writeMicroseconds (MICROSEC2);


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

