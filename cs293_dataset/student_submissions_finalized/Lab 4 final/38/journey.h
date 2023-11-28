#ifndef JOURNEY_H
#define JOURNEY_H


class Journey {
    unsigned int JourneyCode, price;

public:
    Journey(){ JourneyCode = -1; price = -1; }

    Journey(unsigned int c, unsigned int p)
    {
        JourneyCode = c;
        price = p;
    }
    
    unsigned int getJourneyCode(){ return JourneyCode; }
    unsigned int getPrice(){ return price; }

    void setJourneyCode(unsigned int JourneyCode)
    {
        this->JourneyCode = JourneyCode;
    }

    void setPrice(unsigned int price)
    {
        this->price = price;
    }

    bool operator < (Journey const &j) { if(JourneyCode < j.JourneyCode) return true; else return false;} // Usage: if (journey1 < journey2) {...}

    // Following code can be used for ease of I/O
    // Only for those enthusiastic about operator overloading
    // istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
    // ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2
};



#endif


