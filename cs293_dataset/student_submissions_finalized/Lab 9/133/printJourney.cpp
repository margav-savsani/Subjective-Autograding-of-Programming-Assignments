#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// General queue
class Queue {
private:
  int N; // max size of the queue
  int f; // index of the front element
  int r; // index of the rear element
  int *A; // poiter to the array
public:
  Queue(int N){A = new int[DICT_SIZE]; this->N = N;f=0;r=0;} // inititalize
  void enqueue(int e){A[r]=e; r++;} // add elements 
  int top(){return A[f];} // returns top element
  void dequeue(){f++;} // removes top element
  int sz(){return r-f;} // returns size of the queue
  ~Queue(){;} // destructor
};

// a basic linked list of TrainInfoPerStation objects. add, isPresent, isEmpty, seq() are available member functions
class listOfTrains{
  public:
  listOfObjects<TrainInfoPerStation*> *head; // head of the list
  listOfObjects<TrainInfoPerStation*> *tail; // tail of the list
  public:
    listOfTrains(){head = nullptr; tail= nullptr;} // dafault constructor

    void add(TrainInfoPerStation* info){                                         //add elements to the list
      if(head == nullptr){                                                       // if head is nullptr
        head = new listOfObjects<TrainInfoPerStation*>(info);                    // assign value to the head and tail
        tail = head;                                                                  
      } else{
        if(isPres(info)) return;                                                  // don't add if element already in the list 
        tail->next = new listOfObjects<TrainInfoPerStation*>(info);               // add element to the list 
        tail = tail->next;                                                        // update the tail pointer
      }
      return;
    }

    bool isEmp(){
      return head == nullptr;                                                      // returns true if list is empty
    }

    bool isPres(TrainInfoPerStation* info){                                    // returns true if given element is in the list
      listOfObjects<TrainInfoPerStation*> *temp = head;
      while(temp != nullptr){        
        if(temp->object->journeyCode == info->journeyCode) return true;        // comparisions are made with journeycodes
        temp = temp->next;
      }
      return false;
    }

    int seq(TrainInfoPerStation* info){                                                        // returns the stop seq of the given train
      listOfObjects<TrainInfoPerStation*> *temp = head;
      while(temp != nullptr){        
        if(temp->object->journeyCode == info->journeyCode) return temp->object->stopSeq;        // comparisions are made with journeycodes
        temp = temp->next;
      }
      return 0;
    }
    
    void print(){                                                              // prints the journey code of the elements in the list
      listOfObjects<TrainInfoPerStation*> *temp = head;
      while(temp != nullptr) {
        TrainInfoPerStation* currInfo = temp->object;
        cout<<temp->object->journeyCode<<endl;
        temp = temp->next;
      }
      return;
    }

    //destructor
    ~listOfTrains(){
      listOfObjects<TrainInfoPerStation *> *currTrain = head;
      while (currTrain != nullptr) {
        listOfObjects<TrainInfoPerStation *> *deleteTrain = currTrain;
        currTrain = currTrain->next;
        delete deleteTrain;    
      }
    }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int index1 = stnNameToIndex.get(srcStnName)->value;                    // index of source station 
  int index2 = stnNameToIndex.get(destStnName)->value;                   // index of destination station 
  listOfTrains trains[DICT_SIZE];                                        // each element in the array stores a linked list of all trains passing
                                                                         // through the station with the index = index of the element 
  listOfTrains final;                                                    // required list of the trains between the given stations

  int* color = new int[DICT_SIZE];                                       // stores the colour of the node 
  for(int i=0; i<DICT_SIZE; i++){                                        // initialize all elements to white color
    color[i] = 0;                                                        // 0 for white; 1 for grey
  }
  
  color[index1] = 1;                                                     // initialize source color to grey
  Queue q(DICT_SIZE);                                                    // create a queue
  q.enqueue(index1);                                                     // add source station to the queue
  
  //finds the list of trains passing through source stations
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[index1].toStations;    
  while(toStations != nullptr){
    listOfObjects<TrainInfoPerStation*> *info = toStations->object->trains;
    while(info != nullptr){
      trains[index1].add(info->object);                                   // add the info to the source's element of the trains array  
      info = info->next;
    } 
    toStations = toStations->next;      
  }   

  // searching starts
  while(q.sz() != 0){
    int i = q.top();                                                      // top element of the queue
    
    listOfObjects<StationConnectionInfo *> *toStations =adjacency[i].toStations; // adjacent stations of station i
    while(toStations != nullptr){
      int index = toStations->object->adjacentStnIndex;                          // index of a adjacent station of station(i)    
      
      // add trains passing through station(index) which are coming from station(i)
      listOfObjects<StationConnectionInfo *> *toStat = adjacency[index].toStations;    // adjacent toStations of station(index)
      while(toStat != nullptr){
        listOfObjects<TrainInfoPerStation*> *info = toStat->object->trains;            
        while(info != nullptr){                  
          if(trains[i].isPres(info->object)){
            if(info->object->stopSeq == trains[i].seq(info->object)+1) trains[index].add(info->object);   // check common trains in the branch         
          }           
          info = info->next;          
        } 
        toStat = toStat->next;              
      }        

      // if we can reach dest from station(i) 
      // find all trains coming from station(i) to dest (such trains may or may not leave the dest)
      if(index == index2){                     
        listOfObjects<StationConnectionInfo *> *fromStat = adjacency[index].fromStations; // from stations of destn
        while(fromStat != nullptr){
          listOfObjects<TrainInfoPerStation*> *info = fromStat->object->trains;           
          while(info != nullptr){          
            if(trains[i].isPres(info->object)){                                                      // check whether trains in fromStations are coming from
              if(info->object->stopSeq == trains[i].seq(info->object)) final.add(info->object);      // station(i). if so, add it the final list       
            }                                                                                        
            info = info->next;          
          } 
          fromStat = fromStat->next;              
        }        
      }

      // if the color is white, make it grey      
      if(color[index] == 0) {color[index] = 1; if(!trains[index].isEmp())q.enqueue(index);}  // trains[index] means that there no trains leaving
                                                                                             // or there are no common trains between station(i) 
                                                                                             // and station(index). so subsequent sarches from station(index) will also be empty 
      toStations=toStations->next;
    }
    q.dequeue();
  }  

  // if there are no possible trains 
  if(final.isEmp()) cout<<"No direct journeys available"<<endl;                          
  else{
    string days[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    listOfObjects<TrainInfoPerStation*> *src = trains[index1].head;
    listOfObjects<TrainInfoPerStation*> *dest = final.head;
    cout<<endl;
    while(dest != NULL){
      TrainInfoPerStation* info = dest->object; // info of each train reaching destn from src
      while(src != NULL){if(src->object->journeyCode == info->journeyCode) break; src = src->next;} // find the trainsInfo of trains leaving from src to destn
      int JourneyCode = info->journeyCode;      
      int no_stop = info->stopSeq-src->object->stopSeq;                 
      cout<<"JourneyCode: "<<JourneyCode<<endl;     
      cout<<"Number Of stops: "<<no_stop<<endl;
      cout<<"Day(s): ";
      for(int i=0;i<7;i++) if(src->object->daysOfWeek[i]) cout<<days[i]<<" ";   
      cout<<endl;          
      cout<<endl;
      src = trains[index1].head;
      dest = dest->next;
    }
    
  }  
  
  return;
}
