#ifndef JOURNEY_H
#define JOURNEY_H
// #include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Journey {
	unsigned int JourneyCode, price;
	static unsigned int comparisonCount;
public:
	Journey(); // Default constructor if required
	
	Journey(unsigned int c, unsigned int p); // Parametrized Constructor
	
	unsigned int getPrice(); // returns price
	unsigned int getJourneyCode();
	static unsigned int getComparisonCount();
	bool operator < (Journey const &j); // Overloaded operator. Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    friend istream& operator >> (istream& in, Journey &j);
    friend ostream& operator << (ostream& out, const Journey& j);
};

#endif
