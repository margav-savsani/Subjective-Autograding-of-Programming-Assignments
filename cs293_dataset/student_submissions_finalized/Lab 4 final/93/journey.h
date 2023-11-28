#ifndef JOURNEY_H
#define JOURNEY_H
class Journey {
public:
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  Journey(const Journey&);//copy constructor
  Journey& operator =(const Journey&);
  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice(); // returns price
    
  bool operator < (Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}
  bool operator > (Journey const& j);
    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};

Journey::Journey(const Journey& j){
    price = j.price;
    JourneyCode = j.JourneyCode;
}
Journey&  Journey::operator =(const Journey& j){
    price = j.price;
    JourneyCode = j.JourneyCode;
    return *this;
}
// Journey::Journey(unsigned int c, unsigned int p) 
// {
//     JourneyCode = c;
//     price = p;
// }
bool Journey :: operator > (Journey const &j) { if(JourneyCode > j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}
unsigned int Journey::getJourneyCode(){ return JourneyCode; }
#endif
