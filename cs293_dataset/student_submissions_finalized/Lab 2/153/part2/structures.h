#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <math.h>
#include <stdlib.h>

const int MAX_STATION_NAME_LEN = 128;

const int KEY_MAX_LENGTH = 32;

struct Station {
  // define suitable fields here
  // char* name = (char*) malloc(sizeof(char) * MAX_STATION_NAME_LEN);
  char* name = new char[MAX_STATION_NAME_LEN];
};
struct Journey {
  // define suitable fields here
  Station origin;
  Station destination;
  float start_time, end_time;
};

#endif