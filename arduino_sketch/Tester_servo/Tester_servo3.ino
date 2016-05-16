#include <Servo.h>    //  includo la libreria servo

#define BUTTON_1    2  // pulsante rotazione step incrementa manuale  
#define BUTTON_2    3  // pulsante rotazione step decrementa manuale
#define BUTTON_3    4  // pulsante rotazione antioraria con microsecondi
#define BUTTON_4    5  // pulsante rotazione oraria con microsecondi
#define BUTTON_5    7  // pulsante rotazione a step automatica
#define GRADI_0     0
#define MICROSEC1 700
#define MICROSEC2 2300

Servo Servo1;
int angle;
int stepmicro = 10 ;    // il valore di microsecondi da incrementare o decrementare ad ogni pressione dei pulsanti 1 e 2
int val_button1, old_val_button1,val_button2, old_val_button2,steptime  ; //memorizzo lo stato del pulsante in due momenti diversi con le variabile val_button
                                           // steptime memorizzo il valore che incrementero' ad ogni pressione del pulsante

void setup () {
  Serial.begin(9600);               // apro la seriale e imposto la velocita' a 9600
  pinMode(BUTTON_1 , INPUT);        // i pin impostati come input
  pinMode(BUTTON_2 , INPUT);
  pinMode(BUTTON_3 , INPUT);
  pinMode(BUTTON_4 , INPUT);
  pinMode(BUTTON_5 , INPUT);
  Servo1.attach(6, 700, 2350);      // Servo1 e' collegato al pin 6 , limiti minimi e massimi della durata degli impulsi ,
                                    // questo per non forzare il servo nelle due posizioni di finecorsa, si riduce il movimento
                                    // angolare
  Servo1.write (GRADI_0);           // posizione iniziale del servo
steptime= 700 ;
}
void loop ()  {
  val_button1 = digitalRead(BUTTON_1); // leggo il valore del pulsante 1 e lo conservo
  val_button2 = digitalRead(BUTTON_2); // // leggo il valore del pulsante 2 e lo conservo
  if ((val_button1 == HIGH)&&(old_val_button1 == LOW))    // controllo se il pulsante e' stato premuto, controllo il fronte di salita
  {                                                       // del pulsante, se e' vero incremento di 10 la variabile steptime
    steptime += stepmicro;                                       // invio al servo il valore
    Servo1.writeMicroseconds(steptime);
     Serial.print("steptime");
    Serial.println(steptime);
 delay(20);
  }
  old_val_button1 = val_button1;                           // memorizzo il nuovo stato del pulsante
  
  if ((val_button2 == HIGH)&&(old_val_button2 == LOW))    // controllo se il pulsante e' stato premuto, controllo il fronte di salita
    {                                                      // del pulsante, se e' vero decremento di 10 la variabile steptime
    steptime -= stepmicro;                                       // invio al servo il valore
    Servo1.writeMicroseconds(steptime);
     Serial.print("steptime");
    Serial.println(steptime);
 delay(20);
  }
  old_val_button2 = val_button2;                             // memorizzo il nuovo stato del pulsante
 if (digitalRead(BUTTON_3) == HIGH)
    Servo1.writeMicroseconds (MICROSEC1);
  else if (digitalRead(BUTTON_4) == HIGH)
    Servo1.writeMicroseconds (MICROSEC2);
  else if (digitalRead(BUTTON_5) == HIGH){          // il servo si muove a step di un grado con la variabile passo
    for(int passo = 0;passo < 180; passo += 1)      // da 0 a 180 , il valore verra' visualizzato sulla seriale
    {
      Servo1.write(passo);
    delay(20);
    angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle); 
    }
    delay(500);
    for(int passo = 180; passo >= 1; passo -= 1)
    {
      Servo1.write(passo);
      angle = Servo1.read();
    Serial.print("Angle position");
    Serial.println(angle);
      delay(20);
    }
  
  }


  delay (1000);

}

