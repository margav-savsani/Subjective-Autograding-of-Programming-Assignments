#ifndef JOURNEY_H
#define JOURNEY_H

class Journey {
public:
    int JourneyCode {-1};
    int price {-1};

    Journey() = default;
    Journey(int c, int p);
      
    bool operator<(const Journey &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}
    bool operator==(const Journey &j);
};

#endif