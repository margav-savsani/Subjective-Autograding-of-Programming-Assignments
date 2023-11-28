#include"plannerdivakar.h"
#include<fstream>
#include<string.h>
#include<cstring>
using namespace std;

int main(){
    Planner system;
      ifstream fin;
        string input;
        string file;
        file ="sample-planner.txt";
        fin.open(file.c_str());

        while(fin>>input){
                if(input=="ADD"){
                    fin>>input;
                    Journey j;
                    j.station1 = input;
                    fin>>input;
                    j.strttm = stof(input);
                    fin>>input;
                    j.station2 = input;
                    fin>>input;
                    j.endtm = stof(input);
                    system.add(j);
                }
                else if(input=="QUERY_STATION"){
                    Journey j;
                    fin>>input;
                    j.station1 = input;
                    fin>>input;
                    j.strttm = stof(input);
                    system.Querystation(j);
                }
                else if(input=="QUERY_JOURNEY"){
                    Journey j;
                    fin>>input;
                    j.station1 = input;
                    fin>>input;
                    j.strttm = stof(input);
                    fin>>input;
                    j.station2 = input;
                    system.Queryjourney(j);
                }
                else if(input=="EXIT"){
                    break;
                }

                }

        }
        

