#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

const int DICT_SIZE = 64;                                       // max number of trains between 2 stations

const int EMPTY_VAL = -1;
const double EPSILON = 1e-5;

struct Journey {
  double start, end; 
};

class Dictionary {
 private:
  int N; 
 public:
    string end_station;
    struct Journey *trains;
    int current_size; 
    
    Dictionary(){
      N = DICT_SIZE; current_size = 0;
      trains = new Journey[N]; 
      Journey dfault; dfault.start = EMPTY_VAL; dfault.end = EMPTY_VAL; 
    
      for(int i=0; i<N; i++){
          trains[i] = dfault;
      }
    }

    bool put(struct Journey e){
      if (current_size == N) return false;                            // if array full, return false
      if (current_size == 0){
        trains[0] = e; current_size++;
        return true;
      }
      if (current_size == 1){
        trains[0] = e; current_size++;
        return true;
      }

      int i_req = 0;

      double target = e.start;
      while (true){
          int low_index = 0; int high_index = current_size-1;
          int mid_index = (low_index + high_index)/2;

          if(trains[mid_index].start < trains[low_index].start && abs(trains[mid_index].start - trains[low_index].start)>EPSILON){      // edge case-1 of Binary Search
            for(int i=1; i<current_size; i++){
              trains[i] = trains[i-1];
            }
            trains[0] = e;
            current_size++;
            return true;
          }

          if(trains[mid_index].start > trains[high_index].start && abs(trains[mid_index].start - trains[high_index].start)>EPSILON){      // edge case-2 of Binary Search
            trains[current_size] = e;
            current_size++;
            return true;
          }

          if (abs(target - trains[mid_index].start)<EPSILON) 
              i_req = mid_index;
          else if (target > trains[mid_index].start && abs(target - trains[mid_index].start)>EPSILON) 
              low_index = mid_index;                                  // x is on the right side
          else 
              high_index = mid_index;                                 // x is on the left side       
          if(high_index-low_index <= 1){
              i_req = high_index;
              break;
          }
      }

      if(i_req > 0){
          for(int i=i_req; i<current_size; i++){
              trains[i] = trains[i-1];
          }
          trains[i_req-1] = e;
          current_size++;
          return true;
      }
      return false;
    }

    // Given a minimum time to start the journey between the SPECIFIED STATIONS, 
    //                  return the index of the earliest Journey in the db array 
    int get(double start_time_min){
      if(current_size==0) return -1  ;                                // if EMPTY, return NULL
    
      for(int i=0; i<current_size; i++){
          if(abs(start_time_min - trains[i].start)<EPSILON || ((start_time_min < trains[i].start) && abs(start_time_min - trains[i].start)>EPSILON)){
              return i;                                               // if journey found, return it's index
          }
      }
      return -1;
    }
};

///////////////////////////////////////////////////////////////////////////////////

const int MULT = 33;                                    // for hash calc
const int MOD = 86743; //9973; //86743; //38083;        // for hash calc
const int SIZE = 32;                                    // max number of distinct stations

//////////////////////////////////////////////////////////////

int hashValue(string key) {
    int hash = 0; double A = (sqrt(5)-1)/2;

    int num = 1;
    for(int i=0; i<key.length(); i++){
        hash = (hash + (key[i])*(num))%MOD;
        num = (num*MULT)%MOD;
    }

    double frac = hash*A; frac = frac - (int) frac; 
    int h = SIZE*frac;
    return h;
}

string dept_station(string x){
    string t=x; 
    if(x[x.length()-1] == '\r') t = x.substr(0,x.length()-1);
    if(t[t.length()-1] != ' ') t = t + " ";                     // removing '\r' and extra space from string

    int p1 = t.find(" ");
    return t.substr(0,p1);
}

double dept_time(string x){
    string t=x; 
    if(x[x.length()-1] == '\r') t = x.substr(0,x.length()-1);
    if(t[t.length()-1] != ' ') t = t + " ";                     // removing '\r' and extra space from string

    int p1 = t.find(" "); int p2 = t.find(" ", p1+1);
    return stod(t.substr(p1+1,p2-p1-1));
}

string arri_station(string x){
    string t=x; 
    if(x[x.length()-1] == '\r') t = x.substr(0,x.length()-1);
    if(t[t.length()-1] != ' ') t = t + " ";                     // removing '\r' and extra space from string

    int p1 = t.find(" "); int p2 = t.find(" ", p1+1); int p3 = t.find(" ",p2+1);
    return t.substr(p2+1,p3-p2-1);
}

double arri_time(string x){
    string t=x; 
    if(x[x.length()-1] == '\r') t = x.substr(0,x.length()-1);
    if(t[t.length()-1] != ' ') t = t + " ";                     // removing '\r' and extra space from string

    int p1 = t.find(" "); int p2 = t.find(" ", p1+1); int p3 = t.find(" ",p2+1); int p4 = t.find(" ", p3+1);
    return stod(t.substr(p3+1,p4-p3-1));
}

//////////////////////////////////////////////////////////////

class Planner {
    Dictionary db[SIZE][SIZE];
  public:
    bool ADD(string x)
    {
        double d = dept_time(x), a = arri_time(x+" ");
        string ds = dept_station(x), as = arri_station(x);
        Journey e; e.start = d; e.end = a; 

        db[hashValue(ds)][hashValue(as)].end_station = as;
        
        if(db[hashValue(ds)][hashValue(as)].put(e)) return true;
        else return false;
    }

    bool QUERY_STATION(string q)
    {
        string ds = dept_station(q);                                        // start station name

        double d_min = dept_time(q);                                        // trains after (d_min) time
        int d_hash = hashValue(ds);                                         // first index
        bool trigger = 0;

        for(int a_hash=0; a_hash<SIZE; a_hash++){
            if (db[d_hash][a_hash].current_size==0) continue;               // if dictionary is empty
            
            string as = db[d_hash][a_hash].end_station;                     // end station name
            int index = db[d_hash][a_hash].get(d_min); 
            if (index == EMPTY_VAL) continue;

            int max_index = db[d_hash][a_hash].current_size - 1;

            if (max_index < index) continue;
            else if (max_index == index) {
                cout << to_string(db[d_hash][a_hash].trains[index].start) << " " << as << endl;
                trigger = 1;
            }
            else {
                for(int i=index; i<max_index; i++){
                    cout << to_string(db[d_hash][a_hash].trains[i].start) << " " << as << endl;
                }
                trigger = 1;
            }
        }
        if (!trigger){
            return false;
        }
        return true;
    }

    bool QUERY_JOURNEY(string q)
    {
        string ds = dept_station(q), as = arri_station(q);                  // station names
        int d_hash = hashValue(ds), a_hash = hashValue(as);                 
        double d_min = dept_time(q);                                        // trains after (d_min) time

        int earliest_journey_index = 0; bool trigger1 = 0; double earliest_train_straight = 0;

        if (db[d_hash][a_hash].current_size != 0){
          // Case-1 (direct routes)

          for (int k=0; k<db[d_hash][a_hash].current_size; k++){
              if (db[d_hash][a_hash].trains[k].start >= d_min){
                  if (db[d_hash][a_hash].trains[k].start <= db[d_hash][a_hash].trains[earliest_journey_index].start){
                      earliest_journey_index = k; 
                      trigger1 = 1;
                  }
              }
          }

          earliest_train_straight = db[d_hash][a_hash].trains[earliest_journey_index].start;
        }

        // Case-2 (1-intermediate station)
        int isi=0, eji1=0, eji2=0; bool trigger2=0; double earliest_train_with_stop = 0;

        for(int intmd_station_index=0; intmd_station_index<SIZE; intmd_station_index++){
            if (db[d_hash][intmd_station_index].current_size == 0) continue;    // if the 1st route dictionary is empty
            if (db[intmd_station_index][a_hash].current_size == 0) continue;    // if the 2nd route dictionary is empty

            for (int index1=0; index1<db[d_hash][intmd_station_index].current_size; index1++){
                for (int index2=0; index2<db[intmd_station_index][a_hash].current_size; index2++){          // going through all the specified trains
                    if ((db[d_hash][intmd_station_index].trains[index1].start > d_min) && (abs(db[d_hash][intmd_station_index].trains[index1].start - d_min) > EPSILON) || (abs(db[d_hash][intmd_station_index].trains[index1].start - d_min)<EPSILON)){                     // train1 has valid time
                        if (((db[intmd_station_index][a_hash].trains[index2].start > db[d_hash][intmd_station_index].trains[index1].end) && (abs(db[intmd_station_index][a_hash].trains[index2].start - db[d_hash][intmd_station_index].trains[index1].end)>EPSILON)) || (abs(db[intmd_station_index][a_hash].trains[index2].start - db[d_hash][intmd_station_index].trains[index1].end)<EPSILON)){            // train2 has valid time 
                            if (((db[d_hash][intmd_station_index].trains[index1].start < db[d_hash][intmd_station_index].trains[eji1].start) && (abs(db[d_hash][intmd_station_index].trains[index1].start - db[d_hash][intmd_station_index].trains[eji1].start)>EPSILON)) || (abs(db[d_hash][intmd_station_index].trains[index1].start - db[d_hash][intmd_station_index].trains[eji1].start)<EPSILON)){        // 
                                isi = intmd_station_index; eji1 = index1; eji2 = index2; 
                                earliest_train_with_stop = db[d_hash][intmd_station_index].trains[index1].start;
                                trigger2 = 1;
                            }
                        }
                    }
                }
            }
        }

        if(trigger1 && trigger2){
            if ((earliest_train_straight < earliest_train_with_stop) && (abs(earliest_train_straight - earliest_train_with_stop)>EPSILON)){
                cout << earliest_train_straight << endl;
            }
            else {
                cout << earliest_train_with_stop << " " << db[d_hash][isi].end_station << " " << db[isi][a_hash].trains[eji2].start << endl;
            }
            return true;
        }
        else if (trigger1){
            cout << earliest_train_straight << endl;
            return true;
        }
        else if (trigger2){
            cout << earliest_train_with_stop << " " << db[d_hash][isi].end_station << " " << db[isi][a_hash].trains[eji2].start << endl;
            return true;
        }
        return false;
    }
};

#endif