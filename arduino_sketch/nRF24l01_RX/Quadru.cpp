#include "Quadru.h"
#include "Arduino.h"

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
