#include "journey.h"

Journey::Journey(){ 
    this->JourneyCode = 0; 
    this->price = 0; 
}
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    this->JourneyCode = c;
    this->price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
