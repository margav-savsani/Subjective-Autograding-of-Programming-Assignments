#ifndef JOURNEY_CPP
#define JOURNEY_CPP

#include <iostream>
#include "journey.h"

Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { 
//     in >> j.JourneyCode;
//     in >> j.price;
// } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) {  
//     out << j.JourneyCode << " ";
//     out << j.price << std::endl;
// } // Usage: cout << journey2


// int main(){
//     std::cout<<"HEllo"<<std::endl;
// }

#endif