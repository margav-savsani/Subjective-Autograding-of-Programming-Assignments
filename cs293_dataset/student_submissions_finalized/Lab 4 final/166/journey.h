#ifndef JOURNEY_H 
#define JOURNEY_H


class Journey {
  unsigned int JourneyCode, price; 
  
public:
Journey(){ JourneyCode = -1; price = -1; }
    
Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int getJourneyCode(){ return JourneyCode; }
unsigned int getPrice(){ return price; }

bool  operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} 
};

#endif