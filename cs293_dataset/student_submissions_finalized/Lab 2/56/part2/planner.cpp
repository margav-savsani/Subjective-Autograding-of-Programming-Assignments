
#include "dictionary.cpp"
#include <iostream>

using namespace std;

bool le(float a, float b){    //compares two floats using epsilon
    if(a < b + 1000*__FLT_EPSILON__){
        return true;
    }
    return false;
}

bool g(float a, float b){  //compares two floats using epsilon
    if(a > b + 10*__FLT_EPSILON__){
        return true;
    }
    return false;
}

bool ge(float a, float b){  //compares two floats using epsilon
    if(a > b - 1000*__FLT_EPSILON__){
        return true;
    }
    return false;
}

class Planner{     
    Dictionary dict;   //dict implementation from the inlab, now stores stations
    bool manual;   //stores a variable to check if the mode of operation is manual or automatic
    public:        
        Planner(bool manual){  //constructor
            this->manual = manual;
        }
        void addJourney(char start_st[32], float st_time, char end_st[32], float end_time){   //adds a journey with
                                                                //start station, staet time, end station, end time
            
            Station* stn = dict.get(start_st);      //find the station by name
            if(stn == NULL){     //station doesn't exist
                Station new_stn(start_st);      //temporary variable
                
                new_stn.journeys.push_back(Journey(start_st, st_time, end_st, end_time));  //add a new station  
                                                //to the list of end stations of new_stn
                
                dict.put(new_stn);   //add new_stn to the dictionary    
                
            
                if(manual) cout << "New Station " << start_st << " added" << endl; 
            }
            else{
                stn->journeys.push_back(Journey(start_st, st_time, end_st, end_time));  //station exists
                                                                    //update journeys of that station            
                if(manual) cout << "Station " << start_st << "'s journeys updated" << endl; 
            }
            
            stn = dict.get(end_st);    //check if end-stn is present in the dictionary
            if(stn == NULL){         //if not present, then add it
                Station new_stn(end_st);  
                dict.put(new_stn);
                
                if(manual) cout << "New Station " << end_st << " added" << endl; 
            }
        }
        void query_station(char stn[32], float time){   //query a station for all the stations emanating from it
            Station* query_stn = dict.get(stn);
            if(query_stn == NULL){    //station doesn't exist
                cout << "Station doesn't exist" << endl;
                return;
            }
            else{
                for(int i = 0; i < query_stn->journeys.size(); i++){   //iterate through all the journeys from that
                                                                        //station
                    if(le(time, query_stn->journeys[i].start_time)){   //check for journeys after start time
                        cout << query_stn->journeys[i].start_time << " " << query_stn->journeys[i].end_station << endl;
                    }
                }
            }
        }
        void query_journey(char start[32], float time, char end[32]){   //query for a journey
            Station* start_stn = dict.get(start);     //find start station
            Station* end_stn = dict.get(end);     //find end station
            float min_time = 1000000;     
            float lay_start = 1000000;
            char inter[32]; strcpy(inter, "no stn");
            bool direct = false;      //bool for storing if route is direct or not

            if(start_stn == NULL || end_stn == NULL){    //assert that both the stations are existing
                cout << "Station doesn't exist" << endl;
                return;
            }            
            else{
                for(int i = 0; i < start_stn->journeys.size(); i++){     //iterate through the stations emanating from start_stn
                    float temp = start_stn->journeys[i].start_time;
                    if(g(temp, time) && le(temp, min_time)){   //if start time of journey is greater than mentioned time
                        if(strcmp(start_stn->journeys[i].end_station, end) == 0){        // if end station is reachable from start_stn directly                      
                            
                            min_time = temp;
                            direct = true;
                            
                        }
                        else{
                            Station* int_stn = dict.get(start_stn->journeys[i].end_station);   //intermediate station
                            if(int_stn == NULL){
                                cout << "Unexpected error. Exiting ..." << endl;
                                exit(0);
                            }
                            else{
                                for(int j = 0; j < int_stn->journeys.size(); j++){   //find if end can be reached from intermeidate station
                                    if(strcmp(int_stn->journeys[j].end_station, end) == 0 && g(int_stn->journeys[j].start_time, start_stn->journeys[i].end_time) && le(int_stn->journeys[j].start_time, lay_start)){                                   
                                        
                                        min_time = temp;
                                        strcpy(inter, int_stn->key);     
                                        lay_start = int_stn->journeys[j].start_time;
                                        direct = false;   //path is indirect
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(min_time > 99990){   //no journey
                cout << "No journey from " << start << " to " << end << " during the specified time"<< endl;
                return;
            }
            if(direct){   //direct path
                cout << min_time << endl;
                return;
            }
            cout << min_time << " " << inter << " " << lay_start << endl;
        }
};


