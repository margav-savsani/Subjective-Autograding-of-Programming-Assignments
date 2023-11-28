#include<iostream>
#include<string>

#ifndef DICTIONARY_H
#define DICTIONARY_H
using namespace std;


// Can change this value for debugging
int DICT_SIZE = 64;
int TRAINS_SIZE = 500;   // Maximum number of trains starting from a station

struct Train {            // struct Train contains information about a train
    float start_time;     // start time of a Train
    float end_time;       // end time of a train at the destination
    string destination;   // Destination of the train

    Train(){
        start_time = -10; //initializing start and end times to some
        end_time = -10;   //arbitary unusable value, say -10 here
    }
};

struct Entry {            // struct Entry is a entry for Dictionary
    string station;       // I am using name of stations as keys in Dictionary
    struct Train *trains = new Train[TRAINS_SIZE];         // And an array of struct Train as its value
    int size;             // current number of trains stating from this station
    bool isTombStone;     // bool variable, which is set to true when the entry in the array is a tombstone

    Entry(){              // Constructor
        size = 0;
        isTombStone = false;
        station = "$_$";         //I am using "$_$" character as an initializing unusable key
        for(int i = 0; i < TRAINS_SIZE; i++){
            trains[i].destination = "$_$";
        }
    }

    int get_size(){         // function to return current number of trains
      return size;
    }

    void insertTrain(Train newTrain){   //insert a new train through ADD
        if(size == 0){
            trains[0] = newTrain;
        }
        else if(size > 0){              // inserting in a sorted order
            int i;                      // on the basis of start_time
            for (i = size - 1; (i >= 0 && trains[i].start_time >= newTrain.start_time); i--){
                trains[i+1].end_time = trains[i].end_time;
                trains[i+1].destination = trains[i].destination;
                trains[i+1].start_time = trains[i].start_time;
            }
            trains[i+1].end_time = newTrain.end_time;
            trains[i+1].destination = newTrain.destination;
            trains[i+1].start_time = newTrain.start_time; 
        }
        size++;     // incrementing size
    }
};

class Planner {     // This class is used as Dictionary
 private:
  int N;            // size of array A
  struct Entry *A;  // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Planner(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool ADD(struct Entry e);

  // Displays all trains starting from station1 after or equal to startTime
  void QUERY_STATION(string station1, float startTime);

  // Displays the soonest train from station1 to Destination after or equal to startTime (with atmost 1 intermediate stop) 
  void QUERY_JOURNEY(string station1, float startTime, string destination);

};

#endif
