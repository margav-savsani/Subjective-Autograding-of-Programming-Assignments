#include "journey.h"

Journey::Journey(){ JourneyCode = -1; price = -1;}
    
Journey::Journey(unsigned int c, unsigned int p) {
    JourneyCode = c;
    price = p;
}
unsigned int Journey::comparisonCount=0;
unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }
unsigned int Journey::getComparisonCount(){ return comparisonCount; }

bool Journey :: operator < (Journey const &j) { comparisonCount++; if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

istream& operator >> (istream& in, Journey &j) {
	in>>j.JourneyCode>>j.price;
	return in;
}// Usage: cin >> journey1;
ostream& operator << (ostream& out, const Journey& j){
	out<<"Journey Code: "<<j.JourneyCode<<"\tPrice: "<<j.price<<endl;
	return out;
}
