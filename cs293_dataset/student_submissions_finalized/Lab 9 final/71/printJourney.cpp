#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
#include<algorithm>

using namespace std;

vector<int> getListOfJourneyCode(int src,int dest,listOfObjects<TrainInfoPerStation *> **stationInfo){

  vector<int> ans;
  listOfObjects<TrainInfoPerStation *> *s=stationInfo[src];
  while(s!=nullptr){
    if(s->object->depTime!=-1) {
      listOfObjects<TrainInfoPerStation *> *d=stationInfo[dest];
      while(d!=nullptr){
        if(d->object->arrTime!=-1 && d->object->journeyCode==s->object->journeyCode) {
          if(s->object->stopSeq==d->object->stopSeq-1) ans.push_back(s->object->journeyCode);
          break;
        }
        d=d->next; 
      }
    }
    s=s->next; 
  }

  return ans;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

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
    cout<<"No direct journeys available"<<endl;
    return;
  }

  //-------------------//

  //REVERSE FROM DESTINATION

  vector<listOfObjects<int>*> final_list;
  listOfObjects<int> *temp=new listOfObjects<int>(dest_i);
  final_list.push_back(temp);
  vector<vector<int>> list_jc;

  vector<int> dest_jc;
  listOfObjects<TrainInfoPerStation *> *d=stationInfo[dest_i];
  while(d!=nullptr){
    if(d->object->arrTime!=-1) dest_jc.push_back(d->object->journeyCode);
    d=d->next; 
  }

  list_jc.push_back(dest_jc);

  while(true){

    temp=final_list[0];
    vector<int> prevJc=list_jc[0];

    listOfObjects<StationConnectionInfo *> *adj=adjacency[temp->object].fromStations;
    
    
    while(adj!=nullptr){

      if(level[adj->object->adjacentStnIndex]!=-1){

        vector<int> curJc=getListOfJourneyCode(adj->object->adjacentStnIndex,temp->object,stationInfo);
        vector<int> cmnJc;

        for(int i=0; i<curJc.size(); i++){

          vector<int>::iterator it = std::find(prevJc.begin(),prevJc.end(),curJc[i]);
          if(it!=prevJc.end()) cmnJc.push_back(curJc[i]);

        }

        if(cmnJc.size()>0){
         
          listOfObjects<int> *temp1=new listOfObjects<int>(adj->object->adjacentStnIndex);
          temp1->next=temp;
          final_list.push_back(temp1);
          list_jc.push_back(cmnJc);
        }
      }

      adj=adj->next;
    }

    final_list.erase(final_list.begin());
    list_jc.erase(list_jc.begin());

    bool done=true;
    for(int i=0; i<final_list.size(); i++){
      if(final_list[i]->object!=src_i){
        done=false;
        break;
      }
    }

    if(done) break;
  }

  //PRINTING 

  if(final_list.size()>0){
    cout<<"______LIST OF JOURNEYS______"<<endl<<endl<<endl;

    for(int i=0; i<final_list.size(); i++){

      cout<<"             ____ROUTE____("<<i+1<<")"<<endl<<endl;
      listOfObjects<int> *temp=final_list[i];
      while(temp!=nullptr){
        if(temp->object==dest_i) {
          cout<<stnNameToIndex.getKeyAtIndex(temp->object);
          break;
        }
        cout<<stnNameToIndex.getKeyAtIndex(temp->object)<<" -> ";
        temp=temp->next;
      }
      cout<<endl<<endl;
      cout<<"     ___AVAILABLE TRAIN FOR THIS ROUTE___"<<endl<<endl;
      for(int j=0; j<list_jc[i].size(); j++){
        cout<<"JOURNEY CODE("<<j+1<<"): "<<list_jc[i][j]<<endl;
      }
    }

  }
  else cout<<"No direct journeys available"<<endl;

  return;
}