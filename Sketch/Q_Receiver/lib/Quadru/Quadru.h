#ifndef QUADRU_H   // if x.h hasn't been included yet...
#define QUADRU_H

#include <LiquidCrystal_I2C.h>

#define NUMBER_LEG 4
#define NUMBER_PART_LEG 3

enum Quadru_Part_type {FEMORE = 0, TIBIA = 1, ROTAZIONE = 2, FOO = 3};

struct Quadru_part{
  Quadru_Part_type type;
  unsigned int micro_s_angle;
};

struct Quadru_leg{
  int n_slave;
  Quadru_part leg_parts[NUMBER_PART_LEG];
};

struct Quadru{
  Quadru_leg leg[NUMBER_LEG];
};

void printQuadruInfo(Quadru * qp, LiquidCrystal_I2C &lcd);

void printQuadruLeg(Quadru_leg * qp, LiquidCrystal_I2C &lcd);

#endif

