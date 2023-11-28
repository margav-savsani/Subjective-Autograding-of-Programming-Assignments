#include "journey.h"

Journey::Journey(int c, int p) : JourneyCode {c}, price {p} {}

bool Journey::operator< (const Journey &j) { 
    return JourneyCode < j.JourneyCode;
} // Usage: if (journey1 < journey2) {...}

bool Journey::operator== (const Journey &j) {
    return JourneyCode == j.JourneyCode;
}