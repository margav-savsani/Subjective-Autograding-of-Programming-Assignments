#include "journey.h"

unsigned int Journey::getJourneyCode() const
{
    return JourneyCode;
}
/*
unsigned int Journey::getPrice() const
{
    return price;
}

bool Journey::operator<(Journey const& j) const
{
    return (JourneyCode < j.JourneyCode);
}
*/
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

std::istream& Journey::operator>>(std::istream& in, Journey& j)
{
    in >> j.JourneyCode >> j.price;
    return in;
}

std::ostream& Journey::operator<<(std::ostream& out, Journey const& j)
{
    out << "Journey code: " << j.JourneyCode << "\tJourney price: " << j.price;
}
