#include <iostream>
#include "dictionary.h"

Planner::Planner(){                //Constructor
    N = DICT_SIZE;                  
    A = new struct Entry[N];                
    for(int i = 0; i < N; i++){             
        A[i].trains[i].end_time = -10;     //I am using -10 as an unusable initializing value
        A[i].trains[i].start_time = -10;
    }
}

int Planner::hashValue(string key){     // hashValue function
    const int x = 37, M = 1e7 + 7;      // I evaluated the polynomial at x = 37
    const double fibb = 0.6180339887;   // fibb is (sqrt(5)-1)/2
    int i = 0, term = 1, hashvalue = 0; 
    char character = key[0];

    while(character!='\0'){             // Polynomial Accumulation
        character = key[i];
        hashvalue = (hashvalue + (character - '\0')*term) % M;
        term = (term*x) % M;            // Used % M inorder to prevent overflow
        i++;
    }

    double hashv = hashvalue*fibb;      // Compression using Fibonacci Hashing scheme
    hashvalue = hashvalue*fibb;
    hashvalue = int((hashv - hashvalue)*64);

    return hashvalue;
}

int Planner::findFreeIndex(string key){    // finding place where insertion can be done
    int probe = hashValue(key);
    int initprob = probe;
    do {
        if((A[probe].station == "$_$") || A[probe].station == key)return probe;    //return the index of empty location
        probe = (probe + 1) % N;                                   // Or if the key is exactly same, then also return the same location
    }
    while(probe != initprob);   // exit the loop if you have checked the whole array
    return -1;                  // return -1 if any empty index not found
}

struct Entry *Planner::get(string key){     // finding the entry corresponding to given key
    int probe = hashValue(key);
    int initprob = probe;
    do {                                 //search until you get an empty location or you searched the whole array
        if(A[probe].isTombStone == true){       //if tombstone is found, then ignore it and continue
            probe = (probe + 1) % N;
            continue;
        }
        if(A[probe].station == key){      //if key found, then return that entry
            return &A[probe];
        }
        probe = (probe + 1) % N;
    }
    while((A[probe].station != "$_$") || (initprob != probe));
    return NULL;                                //return NULL, if key not found
}

bool Planner::ADD(struct Entry e){         // ADD the given entry into the correct place
    int index = hashValue(e.station);
    int initindex = index;
    do {
        if(findFreeIndex(e.station) >= 0 || A[index].isTombStone){     //insert Train details if the location is empty or it is same station/key
            A[index].station = e.station;                              //or it is a tombstone
            A[index].insertTrain(e.trains[0]);                         
            return true;
        }
        index = (index + 1) % N;
    }
    while(index != initindex);              //loop through until you have searched the whole array
    return false;                           //return false if failure (array is full)
}

void Planner::QUERY_STATION(string station1, float startTime){      //QUERY_STATION
    Entry *entry = new struct Entry;
    entry = get(station1);
    bool trainsAreThere = false;
    if(entry != NULL){
        for(int i = 0; i < entry->get_size(); i++){
            if(entry->trains[i].start_time >= startTime){
                trainsAreThere = true;
                cout << entry->trains[i].start_time << " " << entry->trains[i].destination << endl;
            }
        }
        if(!trainsAreThere){
            cout << "No Trains found leaving " << station1 << " after " << startTime << endl;
        }
    }
    else{
        cout << "ERROR : Given source station does not exist" << endl;
    }
}

void Planner::QUERY_JOURNEY(string station1, float startTime, string Destination){      //QUERY_JOURNEY
    Entry *entry = new struct Entry;
    entry = get(station1);
    if(entry == NULL){
        cout << "ERROR : Given source station does not exist" << endl;
    }
    int n = entry->get_size();
    bool pathFound = false;
    for(int i = 0; i < n; i++){           //check for direct train
        if(entry->trains[i].destination == Destination && entry->trains[i].start_time >= startTime){   
            pathFound = true;
            cout << entry->trains[i].start_time << endl;
            break;
        }
        Entry *intermediate = new struct Entry;
        intermediate = get(entry->trains[i].destination);
        if(intermediate == NULL){
            break;
        }
        int n1 = intermediate->get_size();
        for(int j = 0; j < n1; j++){        // check for train wth atmost one intermediate stop
            if(intermediate->trains[j].destination == Destination && entry->trains[i].start_time >= startTime){
                if(intermediate->trains[j].start_time >= entry->trains[i].end_time){
                pathFound = true;
                cout << entry->trains[i].start_time << " " << intermediate->station << " " << intermediate->trains[j].start_time << endl;
                break;
                }
            }
        }
        if(pathFound) break;
    }
    if(!pathFound){
        cout << "ERROR : No train found which goes from " << station1 << " to " << Destination << " after " << startTime<< endl; 
    }
}
