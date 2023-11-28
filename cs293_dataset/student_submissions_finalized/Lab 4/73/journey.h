#ifndef JOURNEY_H
#define JOURNEY_H
#endif
#include <iostream>
class Journey 
{
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p)
  {
    JourneyCode=c;
    price=p;
  } // Parametrized Constructor
  
  unsigned int getJourneyCode()
  {
    return JourneyCode;
  } // returns journey code
  unsigned int getPrice()
  {
    return price;
  } // returns price
    
  bool operator < (Journey const &j)
  {
    if (JourneyCode<j.JourneyCode)
      return true;
    else
      return false;
  } // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    //friend ostream& operator<<(ostream& os, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};
