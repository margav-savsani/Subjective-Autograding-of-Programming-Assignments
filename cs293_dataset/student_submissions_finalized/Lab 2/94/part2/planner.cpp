#include"planner.h"

void JourneyHandler(Journey &j){
  for(int i=0;i>=0;i++){
    char input[32];
    cout<<">>";
    cin>>input;
    if(strcmp(input,"QUIT") == 0){
      break;
    }
    if(strcmp(input,"ADD") == 0){
      Station a;
      store t;
      cin>>a.s;
      cin>>t.t1;
      cin>>t.s2;
      cin>>t.t2;
      a.add_station(t.s2,t.t1,t.t2);
      int hashValueData=j.hashValue(a.s);
      int freeIndexData=j.findFreeIndex(a.s);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        j.put(a);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
      
    }
    if(strcmp(input,"QUERY_JOURNEY") == 0){



    }
    if(strcmp(input,"QUERY_STATION") == 0){
      char query[32];
      cin>>query;
      int time;
      cin>>time;
      if(j.get(query)!=NULL){

      }



    }

  }

}

int main(){
  cout<<"Train Scheduler"<<endl;
  Journey j;
  JourneyHandler(j);

}