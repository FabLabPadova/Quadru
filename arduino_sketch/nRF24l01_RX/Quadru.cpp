#include "Quadru.h"
#include "Arduino.h"

<<<<<<< HEAD
void print_quadru_details(Quadru *qp) {
  for (unsigned int i = 0; i < NUMBER_LEG; i++) {
    Serial.print("Gamba : ");
    Serial.println(i);
    print_single_leg_part(qp->leg[i]);
    Serial.println("***");
  }//for
}//printQuadruDetails

void print_single_leg_part(Quadru_Leg lp){
  for (unsigned int i = 0; i < NUMBER_PART_LEG; i++){
    Serial.print("Part : ");
    String spart;
    switch (lp.leg_parts[i].type) {
      case (FEMORE):
        spart = "f: ";
        break;
      case (TIBIA):
        spart = "t: ";
        break;
      case (ROTAZIONE):
        spart = "r: ";
        break;
      case (FOO):
        spart = "foo: ";
        break;
    }//switch
    Serial.println(spart);
    Serial.print("Microseconds Angle : ");
    Serial.println(lp.leg_parts[i].micro_s_angle);
  }
}//printSingleLegPart
=======
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
      }//switch
      Serial.print(s);
      Serial.print("ms_angle:");
      Serial.print(ql->leg_parts[i].micro_s_angle);
      Serial.print("|");
    }//for-j
}//printQuadruLeg
>>>>>>> dd320f9cb94fa59592450f4454cb9d9d4f5b4115
