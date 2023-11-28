#ifndef JOURNEY_H
#define JOURNEY_H

class Journey{
public:
  unsigned int JourneyCode, price, length=0; 
  Journey *left;
  Journey *right;
  Journey *parent;
 
  Journey(){
    JourneyCode = -1; price = -1; left=nullptr; right=nullptr;
  }
  Journey(unsigned int c, unsigned int p){
    JourneyCode = c;
    price = p;
    left=nullptr;
    right=nullptr;
}
  unsigned int getJourneyCode(){
    return JourneyCode;
  } // returns journey code
  unsigned int getPrice(){
    return price;
  } // returns price
    
  bool operator < (Journey const &j){
    if(JourneyCode < j.JourneyCode) return true; else return false;
  } // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};
#endif