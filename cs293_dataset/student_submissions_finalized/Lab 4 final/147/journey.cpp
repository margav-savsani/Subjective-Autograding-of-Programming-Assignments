#include "journey.h"

int Journey::comparisons = 0;
Journey::Journey(){ JourneyCode = -1; price = -1; }
Journey::Journey(unsigned int c, unsigned int p): JourneyCode(c), price(p){}

unsigned int Journey::getJourneyCode(){ return JourneyCode; }
unsigned int Journey::getPrice(){ return price; }

bool Journey::operator<(const Journey &other) { comparisons++; return (JourneyCode < other.JourneyCode); }