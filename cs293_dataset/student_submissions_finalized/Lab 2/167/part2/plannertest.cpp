#include<iostream>
#include"planner.cpp"
#include<string.h>
using namespace std;


void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"QUIT") == 0){
      break;
    }

    
    if(strcmp(input,"ADD") == 0){

      char s1[32];
      cin >> s1;
      float t1;
      cin >> t1;
      char s2[32];
      cin >> s2;
      float t2;
      cin >> t2;
      Journey  jour;
      strcpy(jour.stn1.stn,s1);
      strcpy(jour.stn2.stn,s2);
      jour.tm2=t2;
      jour.tm1 =t1;
      int hashValueData = planner.hashValue(jour.stn1.stn);
      int freeIndexData = planner.findFreeIndex(jour.stn1.stn);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData>= 0){
        planner.put(jour);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }   
    
    
   if(strcmp(input,"QUERY_STATION") == 0){
      
      char s1[32];
      cin >> s1;
      float t1;
      cin >> t1;
      planner.get(s1,t1);
     }
    if(strcmp(input,"QUERY_JOURNEY") == 0){
      char s1[32];
      cin >> s1;
      float t1;
      cin >> t1;
      char s2[32];
      cin >> s2;
      planner.soonest(s1,t1,s2);
     }
    
  }
}


int main()
{
  cout<<"Welcome to Rail Planner \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
  return 0;
}
