#include "planner.h"

bool Planner::add(char st1[],double start, char st2[],double end){
    Info inf;
    strcpy(inf.dest,st2);
    inf.stime = start;
    inf.etime = end;
    bool a = dict.put(st1,inf);
    if (!a){
        std::cerr<<"Cannot be added since the dictionary is full"<<std::endl;
        return false;
    }
    return true;
}

returnDetails Planner::query_station(char st1[], double start){
    return (dict.query_station(st1,start));
}

Info Planner::query_journey(char st1[], double start, char st2[]){
    return (dict.query_journey(st1,start,st2));
}
