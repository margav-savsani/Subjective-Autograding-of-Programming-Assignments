#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <vector>
#define Max_size 120
using namespace std;

struct train {
    string stat1,stat2; // station names.
    float time1,time2; // timings.
    bool is_empty = true; // all are empty at the start.
};

class planner {
private:
    int N,size=0;
    train *A;

public:
    // constructor
    planner();

    // returns index at which the new element should be inserted
    int get_size();

    // inserts the train entry into array
    void insert(train);

    // prints details of that train
    void print_data(train);

    // query station
    vector<train> query1(string,float);

    // computing hash value 
    int hashValue(string);

    // finding free index after the hash value of key
    int findFreeIndex(int);

    // query journey
    void query2(string,float,string);

    // for direct travel
    pair<int,int> direct(string,float,string);
};