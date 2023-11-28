#ifndef JOURNEY_H
#define JOURNEY_H
#include<stdio.h>
using namespace std;

class Journey {
public:
  unsigned int JourneyCode, price; 
  
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice(); // returns price
    
  bool operator < (Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
};
#endif
