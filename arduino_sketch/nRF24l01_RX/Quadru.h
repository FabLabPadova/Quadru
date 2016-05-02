#ifndef QUADRU_H   // if x.h hasn't been included yet...
#define QUADRU_H

#define NUMBER_LEG 4
#define NUMBER_PART_LEG 3

enum Quadru_Part_type {FEMORE = 0, TIBIA = 1, ROTAZIONE = 2, FOO = 3};

struct Quadru_Part_Leg{
  Quadru_Part_type type;
  unsigned int micro_s_angle;
  int offset_target = 0;
};

struct Quadru_Leg{
  int n_slave;
  Quadru_Part_Leg leg_parts[NUMBER_PART_LEG];
};

struct Quadru{
  Quadru_Leg leg[NUMBER_LEG];
};

void print_quadru_details(Quadru *qp);

void print_single_leg_part(Quadru_Leg lp);

#endif 