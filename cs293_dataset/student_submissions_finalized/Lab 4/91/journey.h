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

    unsigned int getJourneyCode(); // returns journey code
    unsigned int getPrice(); // returns price

    // overloaded comparison operator
    bool operator<(Journey const& j) const;
    bool operator>(Journey const& j) const;
    bool operator==(Journey const& j) const;
    bool operator<=(Journey const& j) const;
    bool operator>=(Journey const& j) const;

    // overloaded istream input operator
    static std::istream& operator>>(std::istream& in, Journey& j);
    // overloaded ostream output operator
    static std::ostream& operator<<(std::ostream& out, Journey const& j);
};

#endif
