#include"planner.h"
#include<fstream>
#include<string.h>
#include<cstring>
using namespace std;

int main(){
    Planner system;
      ifstream fin;
        string a;
        string file;
        file ="sample-planner.txt";
        fin.open(file.c_str());

        while(fin>>a){
                if(a=="ADD"){
                    fin>>a;
                    Journey travel;
                    travel.station1 = a;
                    fin>>a;
                    travel.starttime = stof(a);
                    fin>>a;
                    travel.station2 = a;
                    fin>>a;
                    travel.endtime = stof(a);
                    system.add(travel);
                }
                if(a=="QUERY_STATION"){
                    Journey travel;
                    fin>>a;
                    travel.station1 = a;
                    fin>>a;
                    travel.starttime = stof(a);
                    system.Query(travel);
                }
                if(a=="EXIT"){
                    break;
                }
        }

}