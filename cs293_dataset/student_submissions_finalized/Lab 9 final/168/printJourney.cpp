#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

string itos(int n);   

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<string> *queue= new listOfObjects<string>(srcStnName);
  // start with source station
  // get its index with the following code
  // int i=stnNameToIndex.get(srcStnName)->value;
  // Obtain a list of all stations which have an edge from source to station with:
  // listOfObjects<StationConnectionInfo*>* l=adjacency[i].toStations;
  // Here, l contains a number of nodes. Each node contains info for each station:
  //      a station index:    l->object->adjacentStnIndex
  //      a list of trains from source to station       l->object->trains
  //
  // Define some kind of list which can store station index as well as jcode
  // Start with source, 

  Dictionary<bool> *directJourney= new Dictionary<bool>();
  // Dictionary<int> *visited = new Dictionary<int>();
  int i=stnNameToIndex.get(srcStnName)->value;
  listOfObjects<StationConnectionInfo*>* l=adjacency[i].toStations;
  //printStationInfo(l->object->trains);
  while(l){
    listOfObjects<TrainInfoPerStation*>* p=l->object->trains;
    while(p){
      string a=itos(p->object->journeyCode);
      Entry<bool> direct=new Entry<bool>(false);
      direct.key=a;
      direct.value=false;
      directJourney->put(direct);
      p=p->next;
    }
    l=l->next;
  }


  //BFS

  listOfObjects<string>* nodes = new listOfObjects<string>(srcStnName);
  listOfObjects<int>* als= new listOfObjects<int>(-1);
  listOfObjects<listOfObjects<int>*>* jcodes = new listOfObjects<listOfObjects<int>*>(als);
  listOfObjects<listOfObjects<int>*>* prevcodes= new listOfObjects<listOfObjects<int>*>(als);
  int len=0;
  while(nodes){
    // cout<<nodes->object<<endl;
    if(nodes->object.compare(srcStnName)==0){
      //cout<<"2"<<nodes->object<<endl;
      auto froms=adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
      auto jrnycodes=new listOfObjects<int>*(jcodes->object);
      for(int i=0;i<len;i++){
        nodes=nodes->next;
        jcodes=jcodes->next;
        prevcodes=prevcodes->next;
      }
      while(froms){
        nodes->next=new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(froms->object->adjacentStnIndex));
        nodes->next->prev=nodes;
        nodes=nodes->next;
        listOfObjects<int> *js=new listOfObjects<int>(-1);
        auto list=froms->object->trains;
        while(list){
          js->next=new listOfObjects<int>(list->object->journeyCode);
          js->next->prev=js;
          js=js->next;
          list=list->next;
        }
        while(js->prev){
          js=js->prev;
        }
        jcodes->next=new listOfObjects<listOfObjects<int>*>(js->next);
        jcodes->next->prev=jcodes;
        jcodes=jcodes->next;
        froms=froms->next;
        prevcodes->next=new listOfObjects<listOfObjects<int>*>(*jrnycodes);
        prevcodes->next->prev=prevcodes;
        prevcodes=prevcodes->next;
        len++;
      }
      for(i=0;i<len;i++){
        nodes=nodes->prev;
        jcodes=jcodes->prev;
        prevcodes=prevcodes->prev;
      }
      nodes=nodes->next;
      jcodes=jcodes->next;
      prevcodes=prevcodes->next;
      len--;
    }
    
    else{
      int index=stnNameToIndex.get(nodes->object)->value;
      int flag=0;
      listOfObjects<StationConnectionInfo*>* froms=adjacency[index].fromStations;
      // while(froms){
      //   listOfObjects<TrainInfoPerStation*>* prevs=froms->object->trains;
      //   while(prevs){
      //     if(directJourney->get(itos(prevs->object->journeyCode))){
      //       flag=1;
      //       break;
      //     }
      //     prevs=prevs->next;
      //   }
      //   if(flag==1){
      //     break;
      //   }
      //   froms=froms->next;
      // }

      //
      listOfObjects<listOfObjects<int>*>* temp = new listOfObjects<listOfObjects<int>*>(jcodes->object);
      while(temp->object){
        // cout<<temp->object->object<<endl;
        if(directJourney->get(itos(temp->object->object))){
          flag=1;
          break;
        }
        temp->object=temp->object->next;
      }
      
      //

      if(flag==0){
        nodes=nodes->next;
        jcodes=jcodes->next;
        if(prevcodes){
          prevcodes=prevcodes->next;
        }

        len--;
      }
      
      else{
        
        if(nodes->object.compare(destStnName)==0){
          // cout<<"hi"<<endl;
          while(jcodes->object){
            int found=0;
            int j=jcodes->object->object;
            // cout<<j<<endl;
            // cout<<"prev"<<endl;
            auto prevList=prevcodes->object;
            // cout<<"hi"<<  endl;
            if(prevList==als){
              found=1;
            }
            else{
              while(prevList){
                if(j==prevList->object){
                  found=1;
                  break;
                }
                prevList=prevList->next;
              }
            }
            if(found==1){
              Entry<bool> e=directJourney->get(itos(j));
              e.value=true;
              e.key=itos(j);
              directJourney->remove(itos(j));
              directJourney->put(e);
              // cout<<e.key<<e.value<<endl;
              /*
              if(directJourney->get(itos(j))->value){
                cout<<"hi"<<endl;
              }
              */
            }
            jcodes->object=jcodes->object->next;
          }
          // cout<<"1"<<nodes->object<<endl;
          nodes=nodes->next;
          jcodes=jcodes->next;
          prevcodes=prevcodes->next;
          len--;
        }
        
        else{
          //insert all next stations and jcodes
          // cout<<nodes->object<<endl;
          froms=adjacency[index].toStations;
          if(froms){
            auto jrnycodes=new listOfObjects<int>*(jcodes->object);
            for(int i=0;i<len;i++){
              nodes=nodes->next;
              jcodes=jcodes->next;
              prevcodes=prevcodes->next;
            }
            while(froms){
              nodes->next=new listOfObjects<string>(stnNameToIndex.getKeyAtIndex(froms->object->adjacentStnIndex));
              nodes->next->prev=nodes;
              nodes=nodes->next;
              listOfObjects<int> *js=new listOfObjects<int>(-1);
              auto list=froms->object->trains;
              while(list){
                js->next=new listOfObjects<int>(list->object->journeyCode);
                js->next->prev=js;
                js=js->next;
                list=list->next;
              }
              while(js->prev){
                js=js->prev;
              }
              jcodes->next=new listOfObjects<listOfObjects<int>*>(js->next);
              jcodes->next->prev=jcodes;
              jcodes=jcodes->next;
              if(prevcodes){
                prevcodes->next=new listOfObjects<listOfObjects<int>*>(*jrnycodes);
                prevcodes->next->prev=prevcodes;
                prevcodes=prevcodes->next;
              }
              froms=froms->next;
              len++;
            }
            for(i=0;i<len;i++){
              nodes=nodes->prev;
              jcodes=jcodes->prev;
            }
          }
          nodes=nodes->next;
          jcodes=jcodes->next;
          len--;
        }
      }
    }
    
  }



  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  l=adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
  TrainInfoPerStation* filler=new TrainInfoPerStation(-1,0,0,0);
  listOfObjects<TrainInfoPerStation*>* directTrains=new listOfObjects<TrainInfoPerStation*> (filler);
  while(l){
    listOfObjects<TrainInfoPerStation*>* trainsFromSource=l->object->trains;
    while(trainsFromSource){
      if(directJourney->get(itos(trainsFromSource->object->journeyCode))->value==true){
        // cout<<"true"<<endl;
        directTrains->next=new listOfObjects<TrainInfoPerStation*> (trainsFromSource->object);
        directTrains->next->prev=directTrains;
        directTrains=directTrains->next;
      }
      trainsFromSource=trainsFromSource->next;
    } 
    l=l->next;
  }
  
  while(directTrains->prev){
    directTrains=directTrains->prev;
  }

  printStationInfo(directTrains->next);
}


string itos(int a){
  string s="";
  while(a>0){
    int k=a%10;
    a=a/10;
    if(k==0){
      s=s+"0";
    }
    else if(k==1){
      s=s+"1";
    }
    else if(k==2){
      s=s+"2";
    }
    else if(k==3){
      s=s+"3";
    }
    else if(k==4){
      s=s+"4";
    }
    else if(k==5){
      s=s+"5";
    }
    else if(k==6){
      s=s+"6";
    }
    else if(k==7){
      s=s+"7";
    }
    else if(k==8){
      s=s+"8";
    }
    else{
      s=s+"9";
    }
  }
  string rev="";
  for (int i=0;i<s.length();i++){
    rev=rev+s.at(s.length()-i-1);
  }
  return rev;
}

#endif
