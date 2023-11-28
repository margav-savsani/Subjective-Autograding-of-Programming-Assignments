#include "journey.h"

Journey::Journey(int c=-1, int p=-1) : JourneyCode {c}, price {p} {}

int Journey::getJourneyCode(){ return JourneyCode; }
// int Journey::getPrice(){ return price; }

bool Journey::operator!=(const Journey &j) {
    return JourneyCode != j.JourneyCode;
}
// bool Journey::operator< (Journey const &j) { 
//     if(JourneyCode < j.JourneyCode) return true; else return false;
// } // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2