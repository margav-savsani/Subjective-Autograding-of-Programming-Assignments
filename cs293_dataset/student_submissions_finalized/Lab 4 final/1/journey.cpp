#include "journey.h"
Journey::Journey(){
    code = 0;
    price = 0;
}
Journey::Journey(int a, int b){
    code = a;
    price = b;
}
Journey::Journey(Journey const& j){
    code = j.code;
    price = j.price;
}

unsigned int Journey::getCode(){return code;}
unsigned int Journey::getPrice(){return price;}

bool Journey::operator<(Journey const& j){
    if(code < j.code) return true;
    else return false;
}


bool Journey::operator>(Journey const& j){
    if(code > j.code) return true;
    else return false;
}

bool Journey::operator==(Journey const& j){
    return j.code == code;
}

istream& operator>>(istream& i, Journey& j){
    i >> j.code >> j.price;
    return i;
}

ostream& operator<<(ostream& o, const Journey& j){
    o << j.code << " " << j.price << endl;
    return o;
}