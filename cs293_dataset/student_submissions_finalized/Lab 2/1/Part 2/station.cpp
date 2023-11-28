//defines functions of the array, Station, Journey classes
#include "planner.h"

//binary search to return the index with i_time just >= given time
//returns size + 1 in case it is the largest
int Station::find_nearest_start(float time){
    if(num_journeys == 0) return 0;
    if(num_journeys == 1){
        if(journeys[0].i_time >= time) return 0;
        else return 1;
    }
    int left = 0, right = num_journeys - 1;
    int mid = (left + right)/2;
    while(right > left + 1){
        if(journeys[mid].i_time == time){
            int j = mid;
            while(journeys[j].i_time == time){
                j--;
                if(j == -1) break;
            }
            return j + 1;
        }
        else if(journeys[mid].i_time > time) right = mid;
        else left = mid;
        mid = (left + right) / 2;
    }
    if(time > journeys[right].i_time) return right + 1;
    else if(time > journeys[left].i_time) return right;
    else return left;
}

//binary search to return the index with f_time just >= given time
//returns size + 1 in case it is the largest
int Station::find_nearest_end(float time){
    if(num_journeys == 0) return 0;
    if(num_journeys == 1){
        if(journeys[0].f_time >= time) return 0;
        else return 1;
    }
    int left = 0, right = num_journeys - 1;
    int mid = (left + right)/2;
    while(right > left + 1){
        if(journeys[mid].f_time == time){
            int j = mid;
            while(journeys[j].f_time == time){
                j--;
                if(j == -1) break;
            }
            return j + 1;
        }
        else if(journeys[mid].i_time > time) right = mid;
        else left = mid;
        mid = (left + right) / 2;
    }
    if(time > journeys[right].f_time) return right + 1;
    else if(time > journeys[left].f_time) return right;
    else return left;
}

//use the binary search to insert new journey in the entry.
//maintains a sorted array of i_times
int Station::insert_starts(struct Journey j){
    int inserted_at = find_nearest_start(j.i_time);
    //cout << "Inserting at " << inserted_at;
    //cout << ", in array of " << station1 << endl;
    for(int i = num_journeys - 1; i >= inserted_at; i--){
        journeys[i+1] = journeys[i];
    }
    journeys[inserted_at] = j;
    return inserted_at;
}

//use the binary search to insert new journey in the entry.
//maintains a sorted array of f_times
int Station::insert_ends(struct Journey j){
    int inserted_at = find_nearest_end(j.f_time);
    //cout << "Inserting at " << inserted_at;
    //cout << ", in array of " << station1 << endl;
    for(int i = num_journeys - 1; i >= inserted_at; i--){
        journeys[i+1] = journeys[i];
    }
    journeys[inserted_at] = j;
    return inserted_at;
}

//growable array
template <typename T>
void array<T>::grow(){
    T* B = new T[size + GROW_SIZE];
    for(int i = 0; i < size; i++){
        B[i] = A[i];
    }
    size += GROW_SIZE;
    delete[] A;
    A = B;
}
