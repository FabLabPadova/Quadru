#include "Quadru.h"
#include "Arduino.h"

void printQuadruInfo(Quadru * qp){
  for (unsigned int i = 0; i<NUMBER_LEG; i++){
    Serial.print("leg:");
    Serial.print(i);
    Serial.print("|");
    printQuadruLeg(&qp->leg[i]);
    Serial.println();
  }//for-i
  Serial.println("***");
}//printQuadruInfo

void printQuadruLeg(Quadru_leg *ql){
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
      Serial.print("|");
    }//for-j
}//printQuadruLeg
