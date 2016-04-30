#ifndef QUADRU_H   // if x.h hasn't been included yet...
#define QUADRU_H

#define NUMBER_LEG 4
#define NUMBER_PART_LEG 3

enum Type_part_leg {FEMORE = 0, TIBIA = 1, ROTAZIONE = 2};

struct Quadru_part{
  Type_part_leg type;
  unsigned int * sel_combo;
  unsigned int micro_s_angle;
};

struct Quadru_leg{
  Quadru_part leg_parts[NUMBER_PART_LEG];
};

struct Quadru{
  Quadru_leg leg[NUMBER_LEG];
};

void printQuadruInfo(Quadru * qp);

void printQuadruLeg(Quadru_leg * qp);

#endif
