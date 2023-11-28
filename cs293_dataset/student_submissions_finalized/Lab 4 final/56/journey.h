#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>

class Journey {
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode(){return JourneyCode;} // returns journey code
  unsigned int getPrice(); // returns price
    
  bool operator < (Journey const &j){if(JourneyCode < j.JourneyCode) return true; else return false;} // Overloaded operator. Usage: if (journey1 < journey2) {...}
  bool operator > (Journey const &j){if(JourneyCode > j.JourneyCode) return true; else return false;} // Overloaded operator. Usage: if (journey1 < journey2) {...}
    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
  //friend std::istream& operator>>(std::istream& in, Journey &j); // Usage: cin >> journey1;
  //friend std::ostream& operator<<(std::ostream& out, const Journey& j);// Usage: cout << journey2
};




#endif