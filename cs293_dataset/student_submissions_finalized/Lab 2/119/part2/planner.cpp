#include <iostream>
#include <string>
#include <math.h>
#include "planner.h"
using namespace std;

int main()
{   
    Planner p;
    string t,x; 

    cout << "Welcome to the Rail Planner\n" << endl;
    
    while(true){
        getline(cin, t);
        if (t.substr(0,3) == "ADD"){
            bool x = p.ADD(t.substr(3+1,t.length()-3-1));
            if(!x) {
                cout << "ERROR in ADD" << endl;
                // break;
            }
        }
        else if (t.substr(0,13) == "QUERY_STATION"){
            bool x = p.QUERY_STATION(t.substr(13+1,t.length()-13-1));
            if(!x) {
                cout << "ERROR in QUERY_STATION" << endl;
                // break;
            }
        }
        else if (t.substr(0,13) == "QUERY_JOURNEY"){
            bool x = p.QUERY_JOURNEY(t.substr(13+1,t.length()-13-1));
            if(!x) {
                cout << "ERROR in QUERY_JOURNEY" << endl;
                // break;
            }
        }
        else if (t == "EXIT") {
            break;
        }
        else {
            cout << "Enter a valid command" << endl;
        }
    }
}
