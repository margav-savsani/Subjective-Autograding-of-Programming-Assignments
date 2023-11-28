#include "journey.h"

Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

//added equality too in definition
bool Journey :: operator < (Journey const &j) { if(JourneyCode <= j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

//defining function to exchange the values 
void Journey :: operator | (Journey &j){
    unsigned int x = JourneyCode;
    unsigned int y = price;
    JourneyCode = j.JourneyCode;
    price = j.price;
    j.JourneyCode = x;
    j.price = y;
}

void Journey::setJourneyCode(int j){
    JourneyCode = j;
}

void Journey::setprice(int p){
    price = p;
}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
