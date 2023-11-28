#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>

#define MAXLEN 32

class Journey{
    char start[MAXLEN], dest[MAXLEN];
    float start_time, end_time;
public:
    Journey(){}
    Journey(char *start_, char *dest_, float start_time, float end_time): start_time(start_time), end_time(end_time){
        strcpy(start, start_); strcpy(dest, dest_);
    }
    char *getstart(){ return start; }
    char *getdest(){ return dest; }
    float getstart_time() const{ return start_time; }
    float getend_time() const{ return end_time; }
    void print(){
        std::cout << start << " to " << dest << ". Time: " << start_time << " - " << end_time << std::endl;
    }
};

#endif