#include"planner.h"
#include<cmath>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;

void handling(Planner &planner){
for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
    if (strcmp(input,"ADD")==0){
        char inputkey1[32];
        cin>>inputkey1;
        float value1;
        cin>>value1;
        char inputkey2[32];
        cin>>inputkey2;
        float value2;
        cin>>value2;
        Journey data;
        strcpy(data.station_one,inputkey1);
        data.start_time = value1;
        strcpy(data.station_two,inputkey2);
        data.finish_time = value2;
        
        int hashValueData = planner.hashValue(data.station_one);
      int freeIndexData = planner.findFreeIndex(data.station_one);
      if(freeIndexData >= 0){
        planner.ADD(data);
        cout<<"added"<<endl;
        cout <<data.station_one<<" " <<data.start_time<< " " <<data.station_two<<" " <<data.finish_time<< endl;
      }
    }
  
  else if(strcmp(input,"QUERY_STATION")==0){
    char inputkey[32];
    float value;
    cin>>inputkey;
    cin>>value;
    Journey* jry = planner.QUERY_STATION(inputkey,value);
    if (jry != NULL){
        cout<<jry->start_time<<" "<<jry->station_two<<endl;
        

    }
   else if(jry->station_one!=inputkey)
    cout<<"station does not exist"<<endl;
  }
   else if(strcmp(input,"QUERY_JOURNEY")==0){
    char inputkey1[32];
    float value;
    char inputkey2[32];
    cin>>inputkey1;
    cin>>value;
    cin>>inputkey2;
    Journey jry;
    strcpy(jry.station_one,inputkey1);
    jry.start_time = value;
    strcpy(jry.station_two,inputkey2);
    int Q = planner.QUERY_JOURNEY(jry.station_one,jry.start_time,jry.station_two);
    if(Q>0){
        cout<<Q<<endl;
    }
    
   }

}
}
void interactive()
{
  cout<<"Welcome to planner \n";
  cout<<"";
  Planner plan;
  handling(plan);
}


int main()
{
  cout<<"Enter 1 for interactive testing "<<endl;
  int which;
  cin>>which;
    interactive();
  
  return 0;
}
