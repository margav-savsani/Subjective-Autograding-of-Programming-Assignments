#include "journey.h"

//constructors for journey
Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

//member functions for accessing private variables
unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

//defining the comparison operator
bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2

// to change code of journey
void Journey:: change_code(unsigned int JourneyCode){
    this->JourneyCode=JourneyCode;
}

//to change price of journey
void Journey::change_price(unsigned int price){
    this->price=price;
}