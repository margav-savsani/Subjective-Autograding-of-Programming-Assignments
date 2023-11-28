#include <iostream>
#include "journey.h"

using namespace std;

Journey::Journey(){ JourneyCode = -1; price = -1; }
    
Journey::Journey(unsigned int c, unsigned int p) 
{
    JourneyCode = c;
    price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }
void Journey::replaceCode(unsigned code)
{
    unsigned int *temp;
    temp = &JourneyCode;
    *temp = code;
    if (JourneyCode == getJourneyCode())cout<<code<<" "<<getJourneyCode()<<endl; return;
}
void Journey::replacePrice(unsigned pr)
{
    unsigned int *temp;
    temp = &price;
    *temp = pr;
    if (price == getPrice())cout<<pr<<" "<<getPrice()<<endl; return;}
bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
