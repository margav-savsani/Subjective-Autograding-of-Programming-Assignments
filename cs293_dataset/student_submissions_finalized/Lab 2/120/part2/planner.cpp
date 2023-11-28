#include "planner.h"
#include <fstream>

int main(){
    Planner planner;
        ifstream fin;
        char word[50];
        string filename;
        filename="sample.txt";
        fin.open(filename.c_str());
        while(fin>>word){
            if(!strcmp(word,"ADD")){
            Journey j;
            fin>>word;
            strcpy(j.station1,word);
            fin>>word;
            j.starttime=stof(word);
            fin>>word;
            strcpy(j.station2,word);
            fin>>word;
            j.endtime=stof(word);
            planner.Add(j);
            }
            else if(!strcmp(word,"QUERY_STATION")){
                Station s;
                fin>>word;
                strcpy(s.station,word);
                fin>>word;
                s.time=stof(word);
                planner.Query_station(s);
            }
            else if(!strcmp(word,"QUERY_JOURNEY")){
                Query q;
                fin>>word;
                strcpy(q.station1,word);
                fin>>word;
                q.starttime=stof(word);
                fin>>word;
                strcpy(q.station2,word);
                planner.Query_journey(q);
            }
            else if(!strcmp(word,"EXIT")){
                break;}
            }
}