#ifndef JOURNEY_H
#define JOURNEY_H
#endif

struct Journey
{
  unsigned int JourneyCode, price;
  bool isPrinted;

public:
  Journey(); // Default constructor if required

  Journey(unsigned int c, unsigned int p); // Parametrized Constructor

  unsigned int getJourneyCode(); // returns journey code
  unsigned int getPrice();       // returns price

  bool operator<(Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}

  // Following code can be used for ease of I/O
  // Only for those enthusiastic about operator overloading
  // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
  // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};

Journey::Journey()
{
  JourneyCode = -1;
  price = -1;
  isPrinted = false;
}

Journey::Journey(unsigned int c, unsigned int p)
{
  JourneyCode = c;
  price = p;
  isPrinted = false;
}

unsigned int Journey::getJourneyCode() { return JourneyCode; }
unsigned int Journey::getPrice() { return price; }

bool Journey ::operator<(Journey const &j)
{
  if (JourneyCode < j.JourneyCode)
    return true;
  else
    return false;
} // Usage: if (journey1 < journey2) {...}
