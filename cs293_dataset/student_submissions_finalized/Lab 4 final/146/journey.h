#ifndef JOURNEY_H
#define JOURNEY_H

#include<iostream>

class Journey {
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode(){return JourneyCode;}; // returns journey code
  unsigned int getPrice(){return price;}; // returns price
  void setJourneyCode(){std::cin>>JourneyCode; } //Sets journey code from input
  void setPrice(){std::cin>>price;} //Sets price from input
  bool operator < (Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}
  bool operator == (Journey const &j){if(JourneyCode == j.JourneyCode) return true; else return false;  } //$ Overloaded operator ==
    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};

#endif