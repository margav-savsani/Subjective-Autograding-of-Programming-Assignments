#include "./o-dictionary.h"
#include <cmath>
#include <iostream>
using namespace std;

// Hashing constants
const double M = (sqrt(5)-1)/2;
const int p = 33;

// Special identifiers
char emptyKey = '-';
char tombstoneKey = '?';


int Dictionary::hashValue(char key[]){
    double coeffs[32];
    int size = 0;

    // Get array of all key[i]*M
    for (int i = 0; key[i] != '\0'; i++)
    {   
        coeffs[i] = ((double(key[i]))*M) - floor((double(key[i]))*M);   
        size++;
    }

    double hashc=0;
    // get value of polynomial
    for(int i=size-1; i>=0; i--){
        hashc += coeffs[i];
        hashc = hashc-floor(hashc);
        hashc *= p;
        hashc = hashc-floor(hashc);
    }
    
    // find hashvalue
    int hashval = floor(DICT_SIZE * hashc);
    return hashval;
}


int Dictionary::findFreeIndex(char key[]){
    if(N == DICT_SIZE) return -1;   // check if full
    else{
        int look = Dictionary::hashValue(key);
        while(A[look].station_one[0] != emptyKey){
            look = (look+1) % DICT_SIZE;
        }
        return look;
    }
}


Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];
    N = 0;

    Entry empty;
    empty.station_one[0] = emptyKey;

    for (int i = 0; i < DICT_SIZE; i++)
        A[i] = empty;
}


struct Entry* Dictionary::get(char key[]){
    int look = Dictionary::hashValue(key);

    for (int i = look; i < DICT_SIZE; i++)
    {   
        if(A[i].station_one[0] == emptyKey) return NULL;
        if(A[i].station_one[0] == tombstoneKey) continue;
        if(strcmp(A[i].station_one,key) == 0) return &A[i];
    }
    
    return NULL;
}


bool Dictionary::put(struct Entry e){
    if(N == DICT_SIZE) return false;    // check if full
    else{
        int i = Dictionary::findFreeIndex(e.station_one);
        A[i] = e;
        N++;
        return true;
    }
}


bool Dictionary::remove(char key[]){
    Entry* toRemove = Dictionary::get(key);
    if(toRemove == NULL) return false;
    else{
        Entry tombstone;
        tombstone.station_one[0] = tombstoneKey;

        *toRemove = tombstone;
        N--;
        return true;
    }
}

// Put all entries starting from station_one after start_time into array pointed by Entry* journies
// and return number of such entries
int Dictionary::query_station(char* station_one, float start_time, Entry* journies){
    int look = Dictionary::hashValue(station_one);

    int count = 0;
    for (int i = look; i < DICT_SIZE; i++)
    {   
        if(A[i].station_one[0] == emptyKey) break;
        if(A[i].station_one[0] == tombstoneKey) continue;
        if(strcmp(A[i].station_one,station_one) == 0  && A[i].start_time >= start_time){
            journies[count] = A[i];
            count++;
        }
    }
    
    return count;
}

// Put the journey with soonest start_time going from station_one to station_two in atmost 2 steps
// If it is direct journey in 1 step then put it in path[0]
// else If it is journey with intermediate station then put first train in path[0] and second in path[1]
// and return number of steps required
int Dictionary::query_journey(char* station_one, float start_time, char* station_two, Entry* path){
    int look = Dictionary::hashValue(station_one);
    int steps = 0;

    float min_time = 2500;
    for (int i = look; i < DICT_SIZE; i++)
    {   
        if(A[i].station_one[0] == emptyKey) break;
        if(A[i].station_one[0] == tombstoneKey) continue;
        if(
            strcmp(A[i].station_one,station_one) == 0
         && A[i].start_time >= start_time 
         && A[i].start_time < min_time
         ){
            if(strcmp(A[i].station_two,station_two) == 0){
                // Direct journey
                min_time = A[i].start_time;
                path[0] = A[i];
                steps = 1;
            }
            else{
                // Journey with intermediate step
                Entry possibilities[DICT_SIZE];
                int size = Dictionary::query_station(A[i].station_two, A[i].finish_time, possibilities);
                float min_leave_time = 2500;
                int min_leave_time_journey;

                for (int i = 0; i < size; i++)
                {
                    if(strcmp(possibilities[i].station_two,station_two) == 0){
                        if(possibilities[i].start_time < min_leave_time){
                            min_leave_time = possibilities[i].start_time;
                            min_leave_time_journey = i;
                        }
                    }
                }
                
                if (min_leave_time < 2500)
                {
                    min_time = A[i].start_time;
                    path[0] = A[i];
                    path[1] = possibilities[min_leave_time_journey];
                    steps = 2;
                }
            }
        }
    }

    return steps;
}


Dictionary::~Dictionary(){
    delete[] A;
}