
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>

using namespace std;

const int DICT_SIZE = 100;


#define DICTIONARY_H


// Can change this value for debugging





struct Entry;


class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key1);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(string my_key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(string key);
};


struct Journey{ //journey struct that saves all the data of a journey
    float st_time, end_time;
    string st_station, end_station;


    Journey(){
        
    } //constructor

    Journey(string st_station_, float st_time_, string end_station_, float end_time_){
        st_time = st_time_;
        end_time = end_time_;
        st_station = st_station_;
        end_station = end_station_;
    }//constructor

    void display(){
        cout << st_station << " " << st_time << " " << end_station << " " << end_time << endl;
    }//to display the journey data



};




class sortedArray{ //array that sorts itself
private:
  Journey *A; // the array used
  int N; // the current size of array A
  int mark; // index where next element will be inserted
public:

    sortedArray() // default constructor
    {
        A = new Journey[DICT_SIZE];
        if (A != nullptr) N = DICT_SIZE;
        else N = 0;
        mark = 0;
    } 

    void QInsert(Journey x){
        A[mark] = x;
        mark += 1;
        sort();
    } // insert given element

    void sort(){ //to sort the queue. This is an insertion sort

        int i, j; 
        Journey key;

        for (i = mark-1; i < mark && mark>0; i++){ 
            key = A[i]; 
            j = i - 1; 

            while (j >= 0 && A[j].st_time > key.st_time){ 
                A[j + 1] = A[j]; 
                j = j - 1; 
            }
            A[j + 1] = key; 
        }
    }


    void display(){ // to display everything in the sorted array
        for(int i = 0; i < mark; i++){
        A[i].display();
        }
        cout << endl;
    }


    int binarySearch(float To_Find){// gives a binary search to the location >= the given floating point number

        int lo = 0, hi = mark - 1;
        int mid;

        if (A[hi].st_time < To_Find){
            return -1;
        }
        while (hi - lo > 0) {
            int mid = (hi + lo) / 2;
            if (A[mid].st_time < To_Find) {
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }
        return lo;
    }

    Journey *give_stations(float st_time, int &number_of_st){ //gives an array of journeys that leaave the station after the given time. Also sets number_of_st as the length of this array
        
        int first = binarySearch(st_time);

        if(first == -1){
            return nullptr;
        }

        number_of_st = mark-first;
        return &A[first];
    }

};








struct Entry { //each entry is a station and the list of all trains leaving it
 public:
  string key; //name of station
  int property; //to handle tombstones
  sortedArray journeys; //journey data in a sorted manner
  
  Entry(){
  	property = 0;//signifies empty entry
  }

  Entry(string key_, Journey first_journey){
  	int pos = 0;
  	key = key_;
    journeys.QInsert(first_journey);
  	property = 1; //signifies full entry
  }
  
  
  string give_key(){
  	return key;
  }
  
  void make_non_empty(){
  	property = 1;
  }
  
  void make_tombstone(){
  	property = 2; //signifies tombstone
  }
  
  int give_property(){
  	return property;
  }

  void add_journey(Journey j){
    journeys.QInsert(j);
  }

  Journey* get_journeys_after(float time, int &number_of_journeys_){//returns set of journeys that leave station after given time.
    int number_of_journeys;
    Journey *j = journeys.give_stations(time, number_of_journeys);

    if (j != nullptr){
        number_of_journeys_ = number_of_journeys;
        return j;
    }
    else{
        return nullptr;
    }

  }

  
  
};
















