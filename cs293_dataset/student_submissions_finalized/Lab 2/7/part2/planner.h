#ifndef PLANNER_H
#define PLANNER_H
#include<string>
#include<cmath>
using namespace std;


//struct Station {
//    string station_name;
//  // define suitable fields here
//};

struct Journey {
    string station_name1;
    string station_name2;
    float start_time;
    float end_time;
    int value;
  // define suitable fields here
};

//struct Query{
//  // define suitable fields here
//};

class Planner {
    
    Journey *j;
    
public:
    Planner(){
        j = new Journey[64];
    }
    
    
    int hashValue(string key){
        double n=0;
        for(int i=0; i<key.length(); i++){
            n = (key[(key.length())-i-1] + n)*37;
        }
        
        double x = n*0.618;
        
        return floor((x-(long)x)*64);    //
    }
    
    int freeIndex(string s){
        
        int x = this->hashValue(s);
        
        if (j[x].value != -1){
               // value = -1 means the place is occupied.
            j[x].value = -1;
            return x;
        }
        
        else {
            for(int i = x+1; i < 64+x; i++){
                if(j[i%64].value != -1){
                    j[x%64].value = -1;
                    return i;
                }
            }
        }
        
        return -1;
        
    }
    
    
    // will add all the routes.
    void dictionary(string s1, float f1, string s2, float f2){
        int n = this->freeIndex(s1);
    
        j[n].station_name1 = s1;
        j[n].station_name2 = s2;
        j[n].start_time = f1;
        j[n].end_time = f2;
    }
    
    void query_station(string s, float f){
        int q=0;
        for(int i=0; i<64; i++){
            if((j[i].station_name1 == s) && (j[i].start_time >= f)){
                cout << j[i].start_time << " " << j[i].station_name2 << endl;
                q=1;
            }
        }
        if(q==0){
            cout << "ERROR" << endl;
        }
        
    }
    
    void query_journey(string s1, float f, string s2){
        float time=2500;
        int p=-1; // index of journey
        int q=-1;  // index of second route if needed
        for(int i=0; i<64; i++){
            if((j[i].station_name1 == s1)&&(f<=j[i].start_time)){
                if(j[i].station_name2 == s2){
                    if(time>=(j[i].end_time-j[i].start_time)){   // direct train will be prefered over connecting train.
                        time = j[i].end_time - j[i].start_time;
                        p = i;
                    }
                }
                else {
                    for(int k=0; k<64; k++){
                        if((j[i].station_name2 == j[k].station_name1) && (j[k].station_name2 == s2)&& (j[i].end_time<=j[k].start_time)){
                            if(time>=(j[k].end_time - j[i].start_time)){
                                time =j[k].end_time - j[i].start_time;
                                p=i;
                                q=k;
                            }
                        }
                    }
                }
            }
        }
        if(q!=-1)
            cout << j[p].start_time << " " << j[q].station_name1 << " " << j[q].end_time << " " << j[q].station_name2 << endl;
        
        else if(p!=-1){
            cout << j[p].start_time << " " << j[p].station_name2 << endl;
        }
        
        else if(p==-1){
            cout << "ERROR" << endl;
        }
//
    }
    
  // define suitable fields here
};

#endif
