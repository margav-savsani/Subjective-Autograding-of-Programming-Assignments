#ifndef JOURNEY_H
#define JOURNEY_H


class Journey {
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode();   // returns journey code
  unsigned int getPrice();         // returns price
    
  bool operator < (Journey const &j);     // Overloaded operator. Usage: if (journey1 < journey2)
  bool operator <= (Journey const &j);    // Overloaded operator for using journey1 <= journey2

};

#endif

