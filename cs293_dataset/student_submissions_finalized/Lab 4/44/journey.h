#ifndef JOURNEY_H
#define JOURNEY_H
#endif

class Journey {
  unsigned int JourneyCode, price; 
  
public:
  Journey(); // Default constructor if required
  
  Journey(unsigned int c, unsigned int p); // Parametrized Constructor
  
  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice(); // returns price
    
  bool operator < (Journey const &j)the pointer to the array, start is the starting index and finish is the last index, 
// Please ensure start <= finish, start >= 0 and finish <= N-1
the pointer to the array, start is the starting index and finish is the last index, 
// Please ensure start <= finish, start >= 0 and finish <= N-1
; // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};
