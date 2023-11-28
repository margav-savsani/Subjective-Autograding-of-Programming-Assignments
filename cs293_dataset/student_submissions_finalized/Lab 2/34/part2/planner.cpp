#include "planner.h"

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Planner ::hashValue(char key[])
{
    int i = 0;
    int factor = 39;
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        sum = (sum * factor + int(key[i])) % (1000000);
    }
    double fibonacci_factor = (sqrt(5) - 1) / 2;
    double fractional = sum * fibonacci_factor - int(sum * fibonacci_factor);
    int m = N;
    return int(fractional * m);
};

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Planner ::findFreeIndex(char key[])
{
    int location = hashValue(key);
    int start = location;
    while (true)
    {
        if (A[location].key == NULL)
        {
            return location;
        }
        location = (location + 1) % N;
        if (location == start)
            return -1;
    }
};

// Default constructor
Planner ::Planner()
{
    N = DICT_SIZE;
    A = new Journey[N];
};

int Planner :: query_journey(string key, string end_journey, int start_time, bool intermediate)
{
    string station1 = key;
    string station2 = "\0";
    string station3 = end_journey;
    int inter_time = -1;
    int time = error_time;

    for(int i = 0; i < N; i++){
        // cout << "checkpoint1\n";
        if(A[i].key != NULL){
        if(compare(A[i].start, station1)){
            // cout << "checkpoint2\n";
            if(A[i].time_start >= start_time && A[i].time_start < time){
                // cout << "checkpoint3 : " << A[i].time_start << " " << time << "\n";
                if(compare(A[i].end, station3)){
                    time = A[i].time_start;
                    station2 = "\0";
                    inter_time = -1;
                    // cout << station1 << " " << A[i].end << " " << time << endl;
                }
                else{
                    for(int j = 0; j < N; j++){
                        if(A[j].key != NULL){
                        if(compare(A[j].end, station3) && compare(A[j].start, A[i].end)){
                            time = A[i].time_start;
                            station2 = A[j].start;
                            inter_time = A[j].time_start;
                            // cout << "info : " << time << " " << station2 << " " << inter_time << " " << A[j].start << endl;
                            // cout << "checkpoint4 : Inter added " << endl;
                            // cout << "inter : " << A[j].start << " " << A[j].time_start << " " << A[j].end << "\n";
                        }
                        }
                    }
                }
            }
        }
        }
    }
    if(time != error_time){
        if(inter_time == -1)cout << time << endl;
        else cout << time << " " << station2 << " " << inter_time << endl;
    }
    return time;
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the Planner
bool Planner ::query_station(char key[], int check_start)
{
    int place = hashValue(key);
    int start = place;
    bool found = false;
    for(int i = 0; i < N; i++)
    {
        // int j = (place + i)%N;
        if (A[i].key != NULL){
    
            if (compare(A[i].start, key) && A[i].time_start >= check_start)
            {
                found = true;
                //cout << place << " " << A[place].start << " " << A[place].time_start << " " <<  A[place].end << " " << A[place].time_end << "\n";
                cout << A[i].time_start << " " << A[i].end << endl;
            }
        }
    }
    //cout << "\n";
    return found;
};

// Put the given entry in the appropriate location (using hashing) in the Planner; return true if success, false if failure (array is full)
bool Planner ::put(struct Journey e)
{
    int place = findFreeIndex(e.key);
    //cout << "place : " << place << "\n";
    int start = place;
    bool found = false;
    //cout  << " " << e.start << " " << e.time_start << " " <<  e.end << " " << e.time_end << "\n";
    for(int i = 0; i < N; i++)
    {
        int j = (place + i)%N;
        if (A[j].key == NULL)
        {
            found = true;
            //cout << "key is NULL\n";
            A[j] = e;
            //cout << "after asigning at place : " <<  place << " " << A[j].start << " " << A[j].time_start << " " <<  A[j].end << " " << A[j].time_end << "\n";
            break;
        }
    }
    //cout << place << " " << A[place].start << " " << A[place].time_start << " " <<  A[place].end << " " << A[place].time_end << "\n";
    return found;
};

bool Planner :: compare(string a, string b){
    if(a.length() != b.length())return false;
    for(int i = 0; i < a.length();i++){
        if(a[i] != b[i]) return false;
        // cout << i << " ";
    }
    // cout << endl;
    return true;
};