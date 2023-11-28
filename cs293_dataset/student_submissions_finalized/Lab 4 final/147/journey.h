#ifndef JOURNEY_H
#define JOURNEY_H

class Journey {
  static int comparisons;
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice(); // returns price
    
  bool operator<(Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}
  // aside: notice here we have Journey const and in .cpp const Journey. Since these are equivalent here, C++ allows us to interchange these and still call the declaration identical - it converts both to const Journey &.
  
    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2

  static int howManyComparisons(){ return comparisons; }
  static void resetComparisons(){ comparisons = 0; }
};

#endif