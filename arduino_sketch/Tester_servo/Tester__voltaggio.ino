#define BATTERY_0   0      // il positivo della batteria e' collegato al pin analogico 0
#define LED_10   10        // led rosso batteria scarica
#define LED_11   11       // led verde batteria carica
void setup() {
 pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  
 Serial.begin(9600);

}

void loop() {
 
float valbattery = analogRead(BATTERY_0);  // leggo il valore dal pin analogico 0 
Serial.println("Volts");
Serial.println(valbattery/100 );
delay(200);
digitalWrite(LED_10,(valbattery<840));
digitalWrite(LED_11,(valbattery>850)); 
}
