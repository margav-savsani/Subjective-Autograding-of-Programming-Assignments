#include "journey.h"

//Implementations of member functions of class Journey
Journey::Journey(){ JourneyCode = -1; price = -1; }   //Default Constructor

Journey::Journey(unsigned int c, unsigned int p)      //Detailed Constructor
{
  JourneyCode = c;
  price = p;
}

unsigned int Journey::getJourneyCode(){ return JourneyCode; } //To get back journey price
unsigned int Journey::getPrice(){ return price; }   //To get back price

//Overloaded operator -----NOT USED IN THE SCRIPTS--------
bool Journey :: operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;}

