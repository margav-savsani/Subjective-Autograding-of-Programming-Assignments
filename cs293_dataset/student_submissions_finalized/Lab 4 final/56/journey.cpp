#include "journey.h"

Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

//bool Journey :: operator <= (Journey const &j) { if(JourneyCode <= j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}
//bool Journey :: operator >= (Journey const &j) { if(JourneyCode >= j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

// std::istream& operator>>(std::istream& in, Journey &j){
//   in >> j.JourneyCode >> j.price;
//   return in;
// }

// std::ostream& operator<<(std::ostream& out, const Journey& j){
//   out << j.JourneyCode << " " << j.price << std::endl;
//   return out;
// }