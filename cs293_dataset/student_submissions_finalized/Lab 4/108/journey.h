#ifndef JOURNEY_H
#define JOURNEY_H

class Journey {
    int JourneyCode;
    int price;
  
public:
    Journey(int c, int p);
  
    int getJourneyCode(); // returns journey code
    int getPrice(); // returns price
      
    bool operator<(Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}
    bool operator!=(const Journey &j);

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};

#endif