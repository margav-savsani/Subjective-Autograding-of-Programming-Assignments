#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
#include"codes.h"
using namespace std;
  
vector<TrainInfoPerStation**> getListOfinfo(int src,int dest,listOfObjects<TrainInfoPerStation *> **stationInfo){

  vector<TrainInfoPerStation**> ans;
  listOfObjects<TrainInfoPerStation *> *s=stationInfo[src];
  while(s!=nullptr){
    if(s->object->depTime!=-1) {
      listOfObjects<TrainInfoPerStation *> *d=stationInfo[dest];
      while(d!=nullptr){
        if(d->object->arrTime!=-1 && d->object->journeyCode==s->object->journeyCode) {
          if(s->object->stopSeq==d->object->stopSeq-1) {
            TrainInfoPerStation **m= new TrainInfoPerStation*[2];
            m[0]=s->object;
            m[1]=d->object;
            ans.push_back(m);
          }
          break;
        }
        d=d->next; 
      }
    }
    s=s->next; 
  }

  return ans;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  //SIMPLE BFS

  int level[DICT_SIZE];
  for(int i=0; i<DICT_SIZE; i++) level[i]=-1;

  int src_i=stnNameToIndex.get(srcStnName)->value;
  level[src_i]=0;
  
  vector<int> cur_st;
  cur_st.push_back(src_i);

  int temp_src;

  while(cur_st.size()>0){
    temp_src=cur_st[0];
    listOfObjects<StationConnectionInfo *> *adj=adjacency[temp_src].toStations;

    while(adj!=nullptr){

      if(level[adj->object->adjacentStnIndex]==-1){
        level[adj->object->adjacentStnIndex]=level[temp_src]+1;
        cur_st.push_back(adj->object->adjacentStnIndex);
      }
      
      adj=adj->next;
    }

    cur_st.erase(cur_st.begin());
  }
  
  //-------------------//

  int dest_i=stnNameToIndex.get(destStnName)->value;
  if(level[dest_i]==-1){
    cout<<"No journeys available"<<endl;
    return;
  }

  //-------------------//

  //REVERSE FROM DESTINATION

  vector<listOfObjects<int*>*> final_list;
  vector<int> sto;

  int count=0;
  while(true){

    int* tint=new int(4);
    listOfObjects<int*> *temp= new listOfObjects<int*>(tint);
    if(count!=0) {
      temp=final_list[0];
      count++;
    }
    else{
      int *ar= new int[8];
      ar[1]=dest_i;
      temp=new listOfObjects<int*>(ar);
      count++;
    }

    listOfObjects<StationConnectionInfo *> *adj=adjacency[temp->object[1]].fromStations;
    
    if(temp->object[1]==src_i){
      listOfObjects<int*> *y=final_list[0];
      final_list.erase(final_list.begin());
      int x=sto[0];
      sto.erase(sto.begin());
      final_list.push_back(y);
      sto.push_back(x);

      bool done=true;
      for(int i=0; i<final_list.size(); i++){
        if(final_list[i]->object[1]!=src_i){
          done=false;
          break;
        }
      }

      if(done) break;
      continue;
    }

    while(adj!=nullptr){

      if(level[adj->object->adjacentStnIndex]!=-1){

        vector<TrainInfoPerStation**> s=getListOfinfo(adj->object->adjacentStnIndex,temp->object[1],stationInfo);
        
        for(int k=0; k<s.size(); k++){
          

          for(int l=0; l<7; l++){
            if(s[k][1]->daysOfWeek[l]){
              for(int m=0; m<7; m++){
                if(s[k][0]->daysOfWeek[m]){
                      int *ans= new int[8];

                  ans[0]=s[k][0]->journeyCode;
                  ans[1]=adj->object->adjacentStnIndex;
                  ans[2]=temp->object[1];
                  ans[4]=s[k][0]->depTime;
                  ans[6]=s[k][1]->arrTime;

                  ans[5]=l;
                  ans[3]=m;

                  if(count==1 && ((ans[3]<ans[5])||(ans[3]==ans[5] && ans[4]<ans[6]))){
                    ans[7]=0;
                    listOfObjects<int*> *t2= new listOfObjects<int*> (ans);
                    sto.push_back(0);
                    final_list.push_back(t2);               
                  }
                  else{
                    int tt=0;
                    bool yes=true;
                    if(ans[0]!=temp->object[0]){
                      if(temp->object[3]==ans[5]){
                        if(ans[6] > temp->object[4]) yes=false;
                        else{
                            int t=temp->object[4]-ans[6];
                            int min=temp->object[4]%100 - ans[6]%100,h=temp->object[4]/100 - ans[6]/100;
                            if(min < 0 ) {
                              h--;
                              min=min + 60;
                            }

                            if(h*100+min > maxTransitTime*100) yes=false;
                            else tt=h*100+min;

                        }
                      }
                      else{
                        if(temp->object[3] < ans[5]) yes=false;
                        else{
                          int h=(temp->object[3]-ans[5]-1)*24;
                          h+=temp->object[4]/100;
                          h+=(2360-ans[6])/100;
                          int min=temp->object[4]%100;
                          min+=(2360-ans[6])%100;
                          h+=min/60;
                          min=min%60;

                          if(h*100+min > maxTransitTime*100) yes=false;
                          else tt=h*100+min;
                        }
                      }
                    }
                    else{
                      if(temp->object[3]==ans[5]){
                        if(ans[6] > temp->object[4]) yes=false;
                      }
                      else{
                         if(temp->object[3] < ans[5]) yes=false;
                      }
                    }
                    if(yes && ((ans[3]<ans[5])||(ans[3]==ans[5] && ans[4]<ans[6]))){
                      ans[7]=tt;
                      listOfObjects<int*> *t2= new listOfObjects<int*> (ans);
                      t2->next=temp;
                      if(ans[0]!=temp->object[0]) {
                        if(maxStopOvers >= sto[0]+1) {
                          sto.push_back(sto[0]+1);
                          final_list.push_back(t2);
                        }
                      }
                      else {
                        sto.push_back(sto[0]);
                        final_list.push_back(t2);
                      }                     
                    }
                  }
                }
              }
            }
          } 
        }
      }
      adj=adj->next;
    }

    if(count!=1) {
      sto.erase(sto.begin());
      final_list.erase(final_list.begin());
    }

    bool done=true;
    for(int i=0; i<final_list.size(); i++){
      if(final_list[i]->object[1]!=src_i){
        done=false;
        break;
      }
    }

    if(done) break;
  }

  // PRINTING

  if(final_list.size()>0){
    cout<<RESET<<"______LIST OF JOURNEYS______"<<endl;

    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    for(int i=0; i<final_list.size(); i++){
      
      cout<<endl<<endl;
      cout<<RED<<"                ____JOURNEY NO: "<<i+1<<" ____"<<endl<<endl;
      listOfObjects<int*> *cur=final_list[i];

      int cjc=cur->object[0];

      cout<<GREEN<<"             JOURNEY CODE: "<<cjc<<endl<<endl;
      while(cur->next!=nullptr){
        cout<<RESET<<stnNameToIndex.getKeyAtIndex(cur->object[1])<<"( ";
        cout<<BLUE<<days[cur->object[3]]<<" ";
        cout<<BLUE<<cur->object[4];
        cout<<RESET<<" ) -> ( ";
        cout<<BLUE<<days[cur->object[5]]<<" ";
        cout<<BLUE<<cur->object[6];
        cout<<RESET<<(" )");

        if(cur->next->object[0]!=cjc){
          cout<<RESET<<stnNameToIndex.getKeyAtIndex(cur->object[2])<<endl<<endl;
          cout<<RESET<<"             TRANSIT TIME: "<<cur->object[7]<<endl<<endl;

          cjc=cur->next->object[0];
          cout<<GREEN<<"             JOURNEY CODE: "<<cjc<<endl<<endl;
        }
        cur=cur->next;
      }
      cout<<RESET<<stnNameToIndex.getKeyAtIndex(cur->object[1])<<"( ";
      cout<<BLUE<<days[cur->object[3]]<<" ";
      cout<<BLUE<<cur->object[4];
      cout<<RESET<<" ) -> ( ";
      cout<<BLUE<<days[cur->object[5]]<<" ";
      cout<<BLUE<<cur->object[6];
      cout<<RESET<<(" )");
      cout<<RESET<<stnNameToIndex.getKeyAtIndex(cur->object[2])<<endl<<endl;
    }
  }
  else cout<<RESET<<"No journeys available"<<endl;
}

#endif
