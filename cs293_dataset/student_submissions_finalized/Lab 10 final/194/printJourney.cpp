#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


class Queue{
  public:
    int index;
    int jcode;
    int arr;
    int dept;
    bool days[7];
    //Queue *next;
    Queue *path;
    Queue *next;
    Queue(int ind, int j, int a, int d,bool D[]){
      index = ind;
      jcode = j;  
      arr = a;
      dept = d;
      next = nullptr;
      path = nullptr;
      for(int i=0;i<7;i++){
        days[i] = D[i];
      }
    }
    Queue(){

    }

    void empty(){
      Queue* trav = this->next;
      while(trav!=nullptr){
        Queue* Del = trav;
        trav = trav->next;
        Del = nullptr;
      }
    }
};

void func(string srcStnName, string destStnName, int stops, int maxTransitTime, Dictionary<int> stnNameToIndex, StationAdjacencyList adjacency[], Queue *&valid, Queue *&q){
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  static Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);
  int srcStnIndex=srcStnIndexEntry->value;
  static int destStnIndex=destStnIndexEntry->value;

  //cout<<srcStnIndex<<endl;
  //int idx = srcStnIndex;
  listOfObjects<StationConnectionInfo *> *temp=adjacency[srcStnIndex].toStations;
  //cout<<"skdj"<<valid<<endl;
  while(temp!=nullptr){
    
    int Index = temp->object->adjacentStnIndex;
      //add stn to queue
      //valid add queue
      //empty queue
      //return
    
    listOfObjects<TrainInfoPerStation*> *t = temp->object->trains;
    while(t!=nullptr){
        if(t->object->depTime-t->object->arrTime > maxTransitTime){
          //q->empty();
          return;
        }
      if(Index == destStnIndex){
        //cout<<"ukwk\n";
        //cout<<valid<<endl;
        Queue *nxt = q->next;
        while(nxt!=nullptr){
          nxt = nxt->next;
        }
        nxt = new Queue(Index,t->object->journeyCode,t->object->arrTime,t->object->depTime,t->object->daysOfWeek);

        if(valid==nullptr){
          //cout<<1<<endl;
          Queue *st = q;
          valid = new Queue(st->index,st->jcode,st->arr,st->dept,st->days);
          Queue *temp2 = valid;
          st = st->next;
          //temp2=temp2->path;
          //cout<<temp2<<endl;
          while(st!=nullptr){ 
            //cout<<2<<endl;
            temp2->path = new Queue(st->index,st->jcode,st->arr,st->dept,st->days);
            temp2 = temp2->path;
            st = st->next;
            //cout<<valid->path->jcode<<"edjwe"<<endl;
          }
          //cout<<valid->jcode<<endl;
        }
        else{
          //cout<<2<<endl;
          Queue *tr = valid;
          //cout<<valid;
          while(tr->next!=nullptr){
            tr = tr->next;
          }
          //tr = new Queue(q->index,q->jcode,q->arr,q->dept,q->days);
          //tr->next = new Queue(Index,t->object->journeyCode,t->object->arrTime,t->object->depTime,t->object->daysOfWeek);
          //cout<<valid->jcode<<endl;
          //cout<<tr->jcode<<endl;
          //cout<<valid->next<<endl;
          Queue *st = q;
          tr->next = new Queue(st->index,st->jcode,st->arr,st->dept,st->days);
          Queue *temp2 = tr->next;
          st = st->next;
          //temp2 = temp2->path;
          //cout<<3<<endl;
          while(st!=nullptr){ 
            //cout<<4<<endl;
            temp2->path = new Queue(st->index,st->jcode,st->arr,st->dept,st->days);
            //cout<<temp2<<"wueuw"<<endl;
            temp2 = temp2->path;
            st = st->next;
          }
        }

        if(t->next==nullptr){  
          // Queue* Next = new Queue(Index,t->object->journeyCode,t->object->arrTime,t->object->depTime,t->object->daysOfWeek);
          // while(Next!=nullptr){
          //   Next = Next->next;
          // }
          q->empty();
        }
        else{
          Queue* Next = q;
          while(Next->next!=nullptr){
            Next = Next->next;
          }
          Next = nullptr;
        }
        return;
      }
      
      if(stops<0){
        q->empty();
        return;
      }
      //Queue* curr;
      if(q==nullptr){ 
        q = new Queue(Index,t->object->journeyCode,t->object->arrTime,t->object->depTime,t->object->daysOfWeek);
      }
      else{
        Queue *nxt = q;
        //cout<<nxt->jcode<<92388;
        while(nxt->next!=nullptr){
          nxt = nxt->next;
        }
        nxt->next = new Queue(Index,t->object->journeyCode,t->object->arrTime,t->object->depTime,t->object->daysOfWeek);
        if(nxt->next->jcode != nxt->jcode){
          stops--;
        }
      }
      
      func(stnNameToIndex.getKeyAtIndex(Index),destStnName,stops,maxTransitTime,stnNameToIndex,  adjacency , valid, q);
      //cout<<t->object->journeyCode<<endl;
      t=t->next;
    }
    //cout<<temp->object->adjacentStnIndex<<endl;
    temp = temp->next;
  }
  return;
};

void print(Queue *&q , int src, Dictionary<int> stnNameToIndex){
  Queue *trav = q;
  while(trav!=nullptr){
    Queue *p = trav->path;
    string s = stnNameToIndex.getKeyAtIndex(src);
    cout<<"START YOUR JOURNEY FROM "<<s<<" TO REACH "<<stnNameToIndex.getKeyAtIndex(trav->index)<<endl;
    while(p->path!=nullptr){
      cout<<"CHANGE FROM "<<stnNameToIndex.getKeyAtIndex(p->index)<<" TO REACH "<<stnNameToIndex.getKeyAtIndex(p->path->index)<<endl;
      cout<<"JOURNEY CODE:" <<p->jcode<<"       "<<"Arr: "<<p->arr<<" Dep: "<<p->dept<<endl;
      p=p->path;
    }
    trav=trav->next;
    cout<<endl<<endl;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  int srcStnIndex=srcStnIndexEntry->value;

  static Queue *valid;
  Queue *paths=nullptr;
  func(srcStnName, destStnName,maxStopOvers,maxTransitTime,stnNameToIndex, adjacency, valid, paths);
  //cout<<valid->path->jcode<<endl;
  //cout<<valid->next->jcode<<" asjkas"<<endl;
  //listOfObjects<TrainInfoPerStation *> *fin;
  //cout<<valid<<endl;
  Queue *h = valid;
  //cout<<h->path->jcode<<endl;
  if(h==nullptr){
    cout<<"NO TRAINS AVAILABLE"<<endl;
  }
  else{ 
    // while(h->next!=nullptr){
    //   Queue* g = h;
    //   cout<<h->index<<" "<<h->jcode<<" "<<h->arr<<endl;
    //   while(g->path!=nullptr){
    //     cout<<"  "<<g->index<<" "<<g->jcode<<" "<<g->arr<<endl;
    //     g=g->path;
    //   }
    //   h=h->next;
    // }
    print(valid,srcStnIndex,stnNameToIndex);
  }

  return;
}

#endif


// class Queue{
//   public:
//     int index;
//     int jcode;
//     int arr;
//     int dept;
//     bool days[7];
//     Queue *next;
//     Queue *next;
//     Queue(int ind, int j, int a, int d,bool D[]){
//       index = ind;
//       jcode = j;  
//       arr = a;
//       dept = d;
//       for(int i=0;i<7;i++){
//         days[i] = D[i];
//       }
//     }
//     Queue(){

//     }

//     void empty(){
//       Queue* trav = this->next;
//       while(trav!=nullptr){
//         Queue* Del = trav;
//         trav = trav->next;
//         Del = nullptr;
//       }
//     }
// };





  /*listOfObjects<listOfObjects<TrainInfoPerStation *>*> *journeys;
  
  
  listOfObjects<StationConnectionInfo *> *next= adjacency[srcStnIndex].toStations->next;
  listOfObjects<listOfObjects<TrainInfoPerStation *>*> *q;
  listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation*>(adjacency[srcStnIndex].toStations->object->trains->object);
  listOfObjects<TrainInfoPerStation *> *temp3 = temp;
  listOfObjects<TrainInfoPerStation *> *temp2 = adjacency[srcStnIndex].toStations->object->trains;*/
  //fin = new listOfObjects<TrainInfoPerStation *>();

  // int stops = maxStopOvers;
  // int idx = srcStnIndex;
  // listOfObjects<StationConnectionInfo *> *temp=adjacency[idx].toStations;

  // while(temp!=nullptr){
    
  //   listOfObjects<TrainInfoPerStation*> *t = temp->object->trains;
  //   while(t!=nullptr){
  //     Queue* curr;
  //     int index = temp->object->adjacentStnIndex;
  //     curr = new Queue(index,t->object->journeyCode,t->object->arrTime,t->object->depTime);
  //     while(stops>=0){
  //       printPlanJourneys(stnNameToIndex.getKeyAtIndex(index),destStnName,stops,maxTransitTime);
  //     }
  //     t=t->next;
  //   }
  //   temp = temp->next;
  // }