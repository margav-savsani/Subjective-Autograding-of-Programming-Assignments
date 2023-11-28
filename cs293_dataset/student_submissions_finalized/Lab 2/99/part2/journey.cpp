#include "trainplanner.h"

using namespace std;

const double x = 33;
const double fibval = (sqrt(5) - 1)/2; 

planner::planner()
{
    n = 64;
    A = new journey[n];
    B = new three_s[n];
    stations = new string[n];
    num_stations = 0;
}

int planner::hashValue(string s1)
{
    double sum = 0;
    int i = 0;
    int s = s1.length();
    for (int i = 0; i < s; i++)
    {
        double add = fibval*s1[i];
        add = add - int(add);
        sum = sum*x + add;
        sum = sum - int(sum);
    }
    int hv = (sum * n);
    return hv;
}

int planner::findFreeIndexA(string s1)
{
    int start = hashValue(s1);
    while (start < n)
    {
        if (A[start].start_time == float(INT_MIN)) return start;
        start++;
    }
    return -1;
}

int planner::findFreeIndexB(string s1)
{
    int start = hashValue(s1);
    while (start < n)
    {
        if (B[start].start_time1 == float(INT_MIN)) return start;
        start++;
    }
    return -1;
}

bool planner::getall(string s1, float st, journey a[], int index[], int &k)
{
    bool exists = 0;
    for (int i = 0; i < num_stations; i++)
    {
        exists = (exists || (stations[i] == s1));
    }
    if (!exists) return 0;
    int start = hashValue(s1);
    while ((A[start].start_time != float(INT_MIN)) && (start < n))
    {
        if (A[start].station_1 == s1 && A[start].start_time >= st)
        {
            a[k] = A[start];
            index[k] = start;
            k++;
        }
        start++;
    }
    return 1;
    // in the main function, if returned 0, display error message THAT THE STATION DOES NOT EXIST
    // if n is zero, message displayed that no such journey is present
}

bool planner::getspecific(string s1, string s2, float st, journey a[], int index[], int &k)
{
    bool exists = 0;
    int start = hashValue(s1);
    while (A[start].start_time != float(INT_MIN))
    {
        if (A[start].station_1 == s1 && A[start].station_2 == s2 && A[start].start_time >= st)
        {
            exists = 1;
            a[k] = A[start];
            index[k] = start;
            k++;    
        }
        start++;
    }
    return exists;
    // returns 0 IF THE JOURNEY DOESN'T EXIST
}

bool planner::getthree(string s1, string s2, string s3, float st, three_s a[], int index[], int &k)
{
    bool exists = 0;
    int start = hashValue(s1);
    while (B[start].start_time1 != float(INT_MIN))
    {
        if(B[start].s1 == s1 && B[start].s2 == s2 && B[start].s3 == s3 && B[start].start_time1 >= st)
        {
            exists = 1;
            index[k] = start;
            a[k].s1 = s1;
            a[k].s2 = s2;
            a[k].s3 = s3;
            a[k].start_time1 = B[start].start_time1;
            a[k].start_time2 = B[start].start_time2;
            k++;
        }
        start++;
    }
    return exists;
}

bool planner::addjourney(journey ADD)
{
    bool one = 0, two = 0;
    for (int i = 0; i < num_stations; i++)
    {
        if (stations[i] == ADD.station_1) one = 1;
        if (stations[i] == ADD.station_2) two = 1;
    }
    if (!one) { stations[num_stations] = ADD.station_1; num_stations++; }
    if (!two) { stations[num_stations] = ADD.station_2; num_stations++; }

    for (int i = 0; i < n; i++)
    {
        if (A[i].issame(ADD)) return 1;
    }
    int x = findFreeIndexA(ADD.station_1);
    if (x == -1) return 0;
    A[x] = ADD;
    for (int i = 0; i < n; i++)
    {
        //ADD.station_1 -> ADD.station_2 == A[i].station_1 -> A[i].station_2
        if ((ADD.station_2 == A[i].station_1) && (ADD.finish_time <= A[i].start_time) && (ADD.station_1 != A[i].station_2))
        {
            int k = findFreeIndexB(ADD.station_1);
            if (k < 0) continue;
            B[k].s1 = ADD.station_1;
            B[k].s2 = ADD.station_2;
            B[k].s3 = A[i].station_2;
            B[k].start_time1 = ADD.start_time;
            B[k].start_time2 = A[i].start_time;
        }
        //A[i].station_1 -> ADD.station_1 == A[i].station_2 -> ADD.station_2
        else if ((ADD.station_1 == A[i].station_2) && (ADD.start_time >= A[i].finish_time) && (ADD.station_2 != A[i].station_1))
        {
            int k = findFreeIndexB(A[i].station_1);
            if (k < 0) continue;
            B[k].s1 = A[i].station_1;
            B[k].s2 = ADD.station_1;
            B[k].s3 = ADD.station_2;
            B[k].start_time1 = A[i].start_time;
            B[k].start_time2 = ADD.start_time;
        }
    }
    return 1;
}

int planner::getsoonest(string s1, float st, string s2, int &ref)
{
    journey two[n];
    three_s three[n];
    int fortwo[n], forthree[n], index_2 = 0, index_3 = 0;
    float mintime2 = INT_MAX, mintime3 = INT_MAX;
    bool TWO = getspecific(s1, s2, st, two, fortwo, index_2);
    bool THREE[n], present = 0;
    for (int i = 0; i < num_stations; i++)
    {
        THREE[i] = getthree(s1, stations[i], s2, st, three, forthree, index_3);
        present = (present || THREE[i]);
    }
    if (!TWO && !present) return -1;
    int ref2 = -1, ref3 = -1;
    for (int i = 0; i < index_2; i++)
    {
        if (mintime2 > two[i].start_time)
        {
            ref2 = fortwo[i];
            mintime2 = two[i].start_time;
        }
    }
    for (int i = 0; i < index_3; i++)
    {
       if (mintime3 > three[i].start_time1)
       {
            ref3 = forthree[i];
            mintime3 = three[i].start_time1;
       }
       else if (mintime3 == three[i].start_time1)
       {
            if (!(B[ref3].start_time2 <= three[i].start_time2)) ref3 = forthree[i];
       }
    }
    if (mintime2 == float(INT_MAX) && mintime3 == float(INT_MAX)) return -1;
    else if (mintime2 <= mintime3)
    {
        ref = ref2;
        return 1;
    }
    ref = ref3;
    return 0;
}

three_s * planner::getB(int ref)
{
    return &B[ref];
}

journey * planner::getA(int ref)
{
    return &A[ref];
}