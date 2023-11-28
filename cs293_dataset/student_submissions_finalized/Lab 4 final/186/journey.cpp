#include "journey.h"

Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p)
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

bool Journey :: operator < (Journey const &j) {          // Overloaded Operator
     if(JourneyCode < j.JourneyCode) return true; else return false;
}

bool Journey :: operator <= (Journey const &j) {         // Overloaded Operator
     if(JourneyCode <= j.JourneyCode) return true; else return false;
} 

