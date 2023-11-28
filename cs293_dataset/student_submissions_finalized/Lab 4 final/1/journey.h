#include <iostream>
using namespace std;
class Journey{
    unsigned int code; //unique for each journey
    unsigned int price;
public:
    Journey();
    Journey(int code, int price);
    Journey(const Journey& j);
    unsigned int getPrice();
    unsigned int getCode();
    bool operator< (Journey const& j); //to compare wrt the codes
    bool operator== (Journey const& j);
    bool operator> (Journey const& j);
    friend istream& operator >> (istream& i, Journey& j); //to write into a journey
    friend ostream& operator << (ostream& o, const Journey& j); //to read a journey's content
};