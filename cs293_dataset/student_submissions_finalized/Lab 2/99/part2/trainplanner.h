#include <iostream>
#include <string.h>
#include <climits>
#include <cmath>

using namespace std;

// stores a journey from one station to another
struct journey
{
    string station_1; // KEY
    string station_2;
    float start_time;
    float finish_time;

    journey(string s1 = "", string s2 = "", float s = INT_MIN, float f = INT_MAX)
    {
        station_1 = s1;
        station_2 = s2;
        start_time = s;
        finish_time = f;
    }
    void operator = (journey x)
    {
        station_1 = x.station_1;
        station_2 = x.station_2;
        start_time = x.start_time;
        finish_time = x.finish_time;
    }
    bool issame(journey x)
    {
        if ((station_1 == x.station_1) && (station_2 == x.station_2)
            && (start_time == x.start_time) && (finish_time == x.finish_time)) return true;
        else return false;
    }
};

// stores a journey from s1 to s3 via s2
struct three_s
{
    string s1;
    string s2;
    string s3;
    float start_time1, start_time2;

    three_s(string a = "", string b = "", string c = "", float start1 = INT_MIN, float start2 = INT_MIN)
    {
        s1 = a;
        s2 = b;
        s3 = c;
        start_time1 = start1;
        start_time2 = start2;
    }
};

class planner
{
    private:
        int n;
        journey * A;
        three_s * B;
        string * stations;
        int num_stations;

    public:
        planner(); // constructor
        int hashValue(string s1); // returns the hash value
        int findFreeIndexA(string s1); // Find the position where given key can be inserted (after resolving hash collision if any);
                                        //return value between 0 and N-1 if free location present; return -1 if no free location
        int findFreeIndexB(string s1);
        bool getall(string s1, float st, journey a[], int index[], int &k); // s1 is the start station, st the start time, a[] stores all the valid journeys and n the number of journeys
        bool getspecific(string s1, string s2, float st, journey a[], int index[], int &k); // gets all journeys from s1 to s2
        bool getthree(string s1, string s2, string s3, float st, three_s a[], int index[], int &k); // gets all journeys s1 -> s2 -> s3
        bool addjourney(journey ADD); // add this journey to the dictionary
        int getsoonest(string s1, float st, string s2, int &ref); // gets the soonest journey from s1 to s2 starting from time st
        three_s * getB(int ref); // pointer to B[ref]
        journey * getA(int ref); // pointer to A[ref]
};