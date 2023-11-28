#ifndef JOURNEY_H
#define JOURNEY_H


class Journey {
  unsigned int JourneyCode, price; 
  
public:
  static int comparisons;//stores the comparisons that have happened 
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  void setJourneyCode(unsigned journey_code);
  void setJourneyPrice(unsigned price);
  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice(); // returns price
  static int getStaticVar(){//returns the static int variable comaprisons 
    return comparisons;
  }
  bool operator<(Journey &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};
#endif