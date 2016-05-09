
#include <Servo.h>    //  includo la libreria servo

Servo Servo1;         // creo una variabile che richiama il servo collegato
#define Button1    2  // pulsante rotazione antioraria con gradi 
#define Button2    3  // pulsante rotazione oraria gradi 
#define Button3    4  // pulsante rotazione antioraria con microsecondi
#define Button4    5  // pulsante rotazione oraria con microsecondi
int  puls1 ,puls2 ,puls3 , puls4; // variabile per memorizzare lo stato dei pulsanti
int Gradi0 =  90 ;     //   posizione di default  
int Gradi1 = 0  ;     //   gradi di movimento premendo il pulsante 1
int Gradi2 = 180 ;     //   gradi di movimento premendo il pulsante 2
int Microsec1  = 700;  //   microsecondi durata impulsi posizione minima
int Microsec2  = 2300; //   microsecondi durata impulsi posizione massima
int angle ;            //   il valore restituito dal servo in gradi funziona solamente se e' comandato con un valore in gradi
void setup () {
  pinMode(Button1 , INPUT);   // i pin impostati come input
   pinMode(Button2 , INPUT);
    pinMode(Button3 , INPUT);
     pinMode(Button4 , INPUT);
     Servo1.attach(6,700,2350);        // Servo1 e' collegato al pin 6 , limiti minimi e massimi della durata degli impulsi ,
                                       // questo per non forzare il servo nelle due posizioni di finecorsa, si riduce il movimento
                                       // angolare 
                                        
    
     Serial.begin(9600);      // apro la seriale e imposto vla velocita' a 9600
   Servo1.write (Gradi0);     // posizione iniziale del servo     
}
void loop () {
int puls1 = digitalRead(Button1);  // memorizzo lo stato del pulsante1
if(puls1== HIGH) 
{
  Servo1.write (Gradi1);
angle = Servo1.read();
Serial.print("Angle position");
Serial.println(angle);
}
else
{
   Servo1.write (Gradi0);
}
int puls2 = digitalRead(Button2);// memorizzo lo stato del pulsante2
if(puls2== HIGH) 
{
  Servo1.write (Gradi2);
  angle = Servo1.read();
Serial.print("Angle position");
Serial.println(angle);
}


int puls3 = digitalRead(Button3);
if(puls3== HIGH) 
{
  Servo1.writeMicroseconds (Microsec1 );
}
int puls4 = digitalRead(Button4);
if(puls4== HIGH) 
{
  Servo1.writeMicroseconds (Microsec2 );
}


/*  Serial.print("Button1");
  Serial.println(puls1);
  Serial.print("Button2");
  Serial.println(puls2);
  Serial.print("Button3");
  Serial.println(puls3);
  Serial.print("Button4");
  Serial.println(puls4);
*/
  delay (1000);
  
}

