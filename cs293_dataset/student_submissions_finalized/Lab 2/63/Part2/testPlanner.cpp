#include <iostream>
#include <string.h>
using namespace std;
#include "planner.cpp"
#include <fstream>

class Interface1{
    Planner P;
public:
    void add(){
        string a,b;
        float c,d;
        cin >> a >> c >> b >> d;
        P.add(a,c,b,d);
        cout << "Successfuly ADDED " << a << " " << c << " " << b << " " << d << endl;
    }
    void query_station(){
        string a;
        float b;
        cin >> a >> b;
        P.query_station(a,b);
    }
    void query_journey(){
        string a,b;
        float c;
        cin >> a >> c >> b;
        P.query_journey(a, c, b);
    }
    bool call(){
        cout << "Please select one of the commands :\n";
        cout << "ADD <start> <time> <end> <time>\n";
        cout << "QUERY_STATION <start> <time>\n";
        cout << "QUERY_JOURNEY <start> <time> <end> <time>\n";
        cout << "EXIT : to exit\n";
        string a;
        cin >> a;
        if (a == "ADD"){
            add();
        }
        else if(a == "QUERY_STATION"){
            query_station();
        }
        else if(a == "QUERY_JOURNEY"){
            query_journey();
        }
        else if(a == "EXIT"){
            return 0;
        }
        else{
            cout << "Command not found! Try again";
        }
        return 1;
    }
};


class Interface2{
    Planner P;
    ifstream f;
public:
    Interface2(char* s){
        f.open(s);
    }
    void add(){
        string a,b;
        float c,d;
        f >> a >> c >> b >> d;
        P.add(a,c,b,d);
        cout << "Successfuly ADDED " << a << " " << c << " " << b << " " << d << endl;
    }
    void query_station(){
        string a;
        float b;
        f >> a >> b;
        P.query_station(a,b);
    }
    void query_journey(){
        string a,b;
        float c;
        f >> a >> c >> b;
        P.query_journey(a, c, b);
    }
    bool call(){
       
        string a;
        while(f >> a){
            if (a == "ADD"){
                add();
            }
            else if(a == "QUERY_STATION"){
                query_station();
            }
            else if(a == "QUERY_JOURNEY"){
                query_journey();
            }
            else if(a == "EXIT"){
                f.close();
                return 0;
            }
            else{
                cout << "Command not found! Try again";
            }
            return 1;
        }
    }
};



int main(int argc, char* argv[]){
    Interface2 I(argv[1]);
    while (I.call()){
    }
    return 0;
}
