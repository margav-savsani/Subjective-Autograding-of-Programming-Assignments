#include <iostream>
#include "planner.h"
#include <string>
using namespace std ;


int main () { 
    Planner planner  ;
    string word ;  
    cin>>word ;
    while (word != "EXIT") { 
            char start[32] , end[32]  ; 
            float start_time , end_time ;

           if (word == "ADD" ) {  
               cin>>start>>start_time>>end>>end_time ; 
               planner.add(start,start_time,end,end_time) ; 
           }
           else if ( word == "QUERY_STATION" ) { 
               cin>>start>>start_time ; 
               planner.query_station(start,start_time) ; 
           }
           else if ( word == "QUERY_JOURNEY" ) { 
               cin>>start>>start_time>>end ; 
               planner.query_journey(start,end,start_time) ; 
           }
           else {  
               cout<<"Command not found"<<endl ; 
           }
           cin>>word ;
    }     
}