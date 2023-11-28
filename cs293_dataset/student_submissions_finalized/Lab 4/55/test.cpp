#include<iostream>
using namespace std;
class A{
    int x,y;
    public:
    istream& operator >> (istream& in,const A &a) { in>>a.x>>a.y; return stream;} // Usage: cin >> journey1;
    ostream& operator << (const A& a) {  } // Usage: cout << journey2
    int getx(){return x;}
    int gety(){return y;}
};
int main(){
    A a;
    cin>>a;
    cout<<a.getx()<<" "<<a.gety();
}