#include "journey.h"

// Default Constructor
Journey :: Journey(){
	JourneyCode = -1;
	price = -1;
}

// Constructor with arguements  
Journey :: Journey(unsigned int c, unsigned int p){
	JourneyCode = c;
	price = p;
}

// function to return journey code
unsigned int Journey :: getJourneyCode(){
	return JourneyCode;
}

// function to return journey price
unsigned int Journey :: getPrice(){
	return price;
}

// '<' operator overloaded
bool Journey :: operator < (Journey const &j){
	if(JourneyCode < j.JourneyCode)
		return true;
	else
		return false;
}
// Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
