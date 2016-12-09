#include "Quadru.h"
#include "Arduino.h"

void printQuadruInfo(Quadru * qp, LiquidCrystal_I2C &lcd){
  lcd.clear();
  for (unsigned int i = 0; i<NUMBER_LEG; i++){
    Serial.print("leg:");
    Serial.print(i);
    Serial.print("|");
    lcd.setCursor(0, i);
    printQuadruLeg(&qp->leg[i], lcd);
    Serial.println();
  }//for-i
  Serial.println("***");
}//printQuadruInfo

void printQuadruLeg(Quadru_leg *ql, LiquidCrystal_I2C &lcd){
    String s = "";
    for (unsigned int i = 0; i<NUMBER_PART_LEG; i++){
      switch (ql->leg_parts[i].type) {
        case (FEMORE):
          s = "f:";
          break;
        case (TIBIA):
          s = "t:";
          break;
        case (ROTAZIONE):
          s = "r:";
          break;
        case (FOO):
          s = "foo:";
          break;
      }//switch
      Serial.print(s);
      Serial.print("ms_angle:");
      Serial.print(ql->leg_parts[i].micro_s_angle);
      lcd.print(s);
      lcd.print(ql->leg_parts[i].micro_s_angle);
      if (i != NUMBER_PART_LEG-1)
        lcd.print(" ");
      Serial.print("|");
    }//for-j
}//printQuadruLeg
