#ifndef JOURNEY_H
#define JOURNEY_H
#endif

class Journey {

  public:

  unsigned int JourneyCode, price; 
  
  Journey(){ // Default constructor if required
    JourneyCode = -1; 
    price = -1;
  }
  Journey(unsigned int c, unsigned int p){   // Parametrized Constructor 
    JourneyCode = c;
    price = p;
  } 
  
  unsigned int getJourneyCode(){  // returns journey code
    return JourneyCode;
  } 
  unsigned int getPrice(){ // returns price
    return price;
  }

  bool operator < (Journey const &j){
    if(JourneyCode < j.JourneyCode){
    return true; 
    }
    else return false;
  } // Overloaded operator. Usage: if (journey1 < journey2) {...}


    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};