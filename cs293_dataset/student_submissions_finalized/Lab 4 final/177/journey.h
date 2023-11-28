#ifndef JOURNEY_H
#define JOURNEY_H

class Journey {
  unsigned int JourneyCode, price; 
  
public:
  Journey();
  
  Journey(unsigned int c, unsigned int p);
  
  unsigned int getJourneyCode();
  unsigned int getPrice();
    
  bool operator < (Journey const &j);
};

#endif
