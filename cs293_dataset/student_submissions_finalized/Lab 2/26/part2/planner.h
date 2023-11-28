#ifndef PLANNER_H
#define PLANNER_H

#include "dictionary.h"
#include"dictionary.cpp"
#include<tuple>
using namespace std;

struct Station {
  // define suitable fields here
};

struct Journey {
  // define suitable fields here
};

struct Query{
  // define suitable fields here
};

class Planner {
private:
    class Dictionary D;

public:
    bool Add( char st1[],char st2[],float st,float ft){
        Entry data;
        strcpy(data.key,st1);
        strcpy(data.s1,st1);
        strcpy(data.s2,st2);
        data.start=st;
        data.end=ft;
        if(D.put(data)){
            return true;
        }
        else{
            return false;
        }
    };

    void QUERY_STATION( char s1[],float st){
        D.gettrain(s1, st);
    };
    void QUERY_JOURNEY(char s1[],float st, char s2[]){
        D.journey(s1,st,s2);

    }
};

#endif