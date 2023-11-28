#include "journey.h"

unsigned int Journey::getJourneyCode() const
{
    return JourneyCode;
}
unsigned int Journey::getPrice() const
{
    return price;
}

bool Journey::operator<(Journey const& j) const
{
    return (JourneyCode < j.JourneyCode);
}
bool Journey::operator>(Journey const& j) const
{
    return (JourneyCode > j.JourneyCode);
}
bool Journey::operator==(Journey const& j) const
{
    return (JourneyCode == j.JourneyCode);
}

bool Journey::operator<=(Journey const& j) const
{
    return (JourneyCode <= j.JourneyCode);
}

bool Journey::operator>=(Journey const& j) const
{
    return (JourneyCode >= j.JourneyCode);
}

std::istream& operator>>(std::istream& in, Journey& j)
{
    in >> j.JourneyCode >> j.price;
//    in >> j.JourneyCode;
    return in;
}

std::ostream& operator<<(std::ostream& out, Journey const& j)
{
//    out << "Journey code: " << j.JourneyCode << "\tJourney price: " << j.price;
    out << j.JourneyCode;
    return out;
}
