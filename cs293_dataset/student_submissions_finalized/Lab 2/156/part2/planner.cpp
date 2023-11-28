#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include<string.h>
#include "dictionary.cpp"
using namespace std;
#include<cstring>

struct Station {
  // define suitable fields here
  char name[32];
  Dictionary arrivals;//started station arrival time
  int a_added=0;
  Dictionary departure;//departure time final destination
  int d_added=0;

  void d_add(){
    d_added++;
  }
  void a_add(){
    a_added++;
  }
  int geta(){
    return a_added;
  }
  int getd(){
    return d_added;
  }
};

struct Journey {
  char start[32];
  char end[32];
  float jtime;
  // define suitable fields here
};

class Planner {


  Journey j[64];
  int j_added = 0;
  Station s[128];
  int s_added = 0;
  // define suitable fields here

    //adds journey by adding an entry in struct journey and also arrivals and deparure dictionaries are
    //added for the stations given
public:

  bool add_journey(char s1[32],float t1,char s2[32],float t2){
    if(j_added == 64){return false;}
    else{
        int s1_at = 0;
        int s2_at = 0;

        strcpy(j[j_added].start,s1);
        strcpy(j[j_added].end,s2);
        j[j_added].jtime = t2-t1;
        j_added++;

        for(s1_at =0;s1_at<s_added;s1_at++){
        if(strcmp(s[s1_at].name,s1)==0) break;
        else s1_at++;
        }
        if(s1_at==s_added){
        strcpy(s[s_added].name,s1);
        s_added++;
        }

        Entry e1;
        strcpy(e1.key,s2);
        e1.value = t1;
        s[s1_at].departure.put(e1);
        s[s1_at].d_add();

        for(s2_at = 0;s2_at<s_added;s2_at++){
        if(strcmp(s[s2_at].name,s2)==0) break;
        else s2_at++;
        }
        if(s2_at==s_added){
        strcpy(s[s_added].name,s2);
        s_added++;
        }

        Entry e2;
        strcpy(e2.key,s1);
        e2.value = t2;
        s[s2_at].arrivals.put(e2);
        s[s2_at].a_add();
    }
    return true;
  }

    //would retun all the trains after time t from station key and the destination station
    //This function uses the departure dictionary and the get(float) function in dictionary to get all possible trains
  void query_station(char key[32],float t){
    int s_at=0;
    for(s_at =0;s_at<s_added;s_at++){
      if(strcmp(s[s_at].name,key)==0) break;
      else s_at++;
    }
    if(s_at==s_added){
      cout << "No entry for the given station!";
    }
    else{
      s[s_at].departure.get(t,s[s_at].getd());
    }
  }

  bool query_journey(char s1[32],float start,char s2[32],int n){

    //n=0 means start station is being checked 
    //else means inter being checked
    //stores the list of intermediate stations to check for the soonest possible route
    string inter[64];
    float inter_time[64];
    float inter_start[64];//start from main station
    int inter_added = 0;
    float tm = 2500;
    float tm_inter = 2400;
    bool direct = true; 
    bool one_stop = false;

    int s1_at=0;
    for(s1_at =0;s1_at<s_added;s1_at++){
      if(strcmp(s[s1_at].name,s1)==0) break;
      else s1_at++;
    }
    if(s1_at == s_added){
        cout << "No such station";
        return false;
    }

    for(int i=0;i<j_added;i++){
        if(strcmp(j[i].start,s1)==0){
            if(strcmp(j[i].end,s2)==0 && direct){
                float z = s[s1_at].departure.getmintime(s2,start);
                if(z<2400){
                    tm = z;
                }
                else{
                    direct = false;
                    one_stop= true;
                }
            }
            else if(n==0){
                
                int s2_at=0;
                for(s2_at =0;s2_at<s_added;s2_at++){
                    if(strcmp(s[s2_at].name,j[i].end)==0) break;
                    else s2_at++;
                }
                float t = s[s1_at].departure.getmintime(j[i].end,start);
                float z = t+j[i].jtime;
                if(z<2400)
                {
                
                        strcpy(const_cast<char*>(inter[inter_added].c_str()),j[i].end);
                        inter_start[inter_added] = t;
                        inter_time[inter_added] = z; //time reaching interstation
                        inter_added++;
                
                }
            }
        }
    }

    if(n==1){return direct;}

    if(inter_added==0 && direct==true && n==0){cout << "Direct Journey" << endl; cout << tm; return true;}
    else if(inter_added==0 && direct==false && n==0){return false;}
    else{
        int index_min = 64;
        float t_min = 2500;

        bool tf[inter_added];//store true if further ourney present else false
        for(int i=0;i<inter_added;i++){
            tf[i] = query_journey(const_cast<char*>(inter[i].c_str()),inter_time[i],s2,1);
        }

        for(int i=0;i<inter_added;i++){
            if(tf[i]==true){
                if(inter_start[i]<t_min){
                    index_min = i;
                    t_min = inter_start[i];
                }
            }
        }

        if(index_min==64){return false;}
        else{
            int sj_at = 0;
            for(sj_at =0;sj_at<s_added;sj_at++){
                if(strcmp(s[sj_at].name,const_cast<char*>(inter[index_min].c_str()))==0) break;
                else sj_at++;
            }
            if(direct==true && tm<=inter_start[index_min]){
                cout << "Direct Journey" << endl;
                cout << tm;
            }

            else{
                float tt = s[sj_at].departure.getmintime(s2,inter_time[index_min]);
                cout << "One-stop";
                cout << inter_start[index_min] << " " << const_cast<char*>(inter[index_min].c_str()) << " " << tt;
            }
            
            return true; 
        
        }

    }
    //now we have excluded the case of more than one stop journey and if direct then we have printed the result
    //now deal with one-wayy using the bool tf array and print correspondingly
    return false;
  }

};

/*int main(){
    Planner planner;
    planner.add_journey("Berlin",1300,"Munich",1700);
    planner.add_journey("Gottingen",1000,"Hannover",1100);
    planner.add_journey("Hannoevr",900,"Berlin",1100);
    planner.add_journey("Munich",1400,"Frankfurt",1800);
    planner.add_journey()
    planner.add_journey
    planner.add_journey
    planner.add_journey
}
*/

#endif