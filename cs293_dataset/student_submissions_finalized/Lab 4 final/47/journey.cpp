#include "journey.h"

Journey::Journey(){ JourneyCode = 0; price = 0; }
    
Journey::Journey(int c,int p) 
{
    JourneyCode = c;
    price = p;
}

int Journey::getJourneyCode(){ return JourneyCode; }
int Journey::getPrice(){ return price; }

bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}
bool Journey :: operator == (Journey const &j) { if( (JourneyCode == j.JourneyCode) && (price == j.price)) return true; else return false;} // created the operator == between two journeys.


// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
