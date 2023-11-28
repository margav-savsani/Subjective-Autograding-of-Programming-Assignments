#include <iostream>
#include "array.h"
using namespace std;
void copy(char a[], char b[]);
bool compare(char a[], char b[]);

const int DICT_SIZE = 8;

struct Journey{
    char station2[32]; //the "other" station
    float i_time = 0;
    float f_time = 0;
    bool indirect = false;
    char intermediate[32];
    float int_time;
    void display(){
        cout << "Station 2: " << station2 << endl;
        cout << "Journey time: " << i_time << " to " << f_time << endl;
        cout << "Indirect: " << indirect << endl;
        if(indirect) cout << "Intermediate station: " << intermediate << endl;
    }
    Journey& operator=(Journey& rhs){
        copy(rhs.station2, station2);
        i_time = rhs.i_time;
        f_time = rhs.f_time;
        indirect = rhs.indirect;
        copy(rhs.intermediate, intermediate);
        int_time = rhs.int_time;
        return *this;
    }
};

struct Station{
    bool filled = false;
    char station1[32];
    int num_journeys = 0; //no. of journeys from/till the station
    int find_nearest_start(float time);
    int find_nearest_end(float time);
    int insert_starts(struct Journey j);
    int insert_ends(struct Journey j);
    //struct Journey journeys[8]; //array of those journeys
    array<struct Journey> journeys;
    void display(){
        cout << "Station: " << station1 << endl;
        for(int i = 0; i < num_journeys; i++){
            journeys[i].display();
        }
    }
};

class dictionary{
    struct Station *A;
    int size = DICT_SIZE;
public:
    dictionary(){
        A = new Station[size];
    }
    //No need for remove functionality (?)
    //Can be added
    void display();
    int hashValue(char station[]);
    int findFreeIndex(char station[]);
    struct Station *get(char station[]);
    struct Station *add(char start[]);

    ~dictionary(){
        delete[] A;
    }
};

class planner{
    dictionary starts;
    dictionary ends;
public:
    void add_journey(char start[], char end[], float i_time, float f_time);
    void q_station(char station[], float time);
    void q_journey(char start[], char dest[], float time);
    void display();
};  