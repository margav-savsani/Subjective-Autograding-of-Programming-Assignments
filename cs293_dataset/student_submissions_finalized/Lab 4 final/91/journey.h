#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>

class Journey {
    unsigned int JourneyCode, price;

  public:
    // default constructor
    Journey();
    // parametrized Constructor
    Journey(unsigned int c, unsigned int p);

    unsigned int getJourneyCode() const; // returns journey code
    unsigned int getPrice() const; // returns price

    // overloaded comparison operator
    bool operator<(Journey const& j) const;
    bool operator>(Journey const& j) const;
    bool operator==(Journey const& j) const;
    bool operator<=(Journey const& j) const;
    bool operator>=(Journey const& j) const;

    friend std::istream& operator>>(std::istream& in, Journey& j);
    friend std::ostream& operator<<(std::ostream& out, Journey const& j);
};

// overloaded istream input operator
std::istream& operator>>(std::istream& in, Journey& j);
// overloaded ostream output operator
std::ostream& operator<<(std::ostream& out, Journey const& j);

#endif
