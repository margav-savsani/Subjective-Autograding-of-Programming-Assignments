#include "journey.h"

Journey :: Journey(){ JourneyCode = -1; price = -1; }
 int Journey:: comparisons=0;
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

bool Journey :: operator < (Journey const &j) { 
    comparisons++;
    if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

istream& operator >> (istream& in, Journey &j) {
     in>>j.JourneyCode>>j.price;
    return in; 
} // Usage: cin >> journey1;
ostream& operator << (ostream& out, const Journey& j) {
    out<<j.JourneyCode<<" "<<j.price<<endl;
    return out;
} // Usage: cout << journey2

