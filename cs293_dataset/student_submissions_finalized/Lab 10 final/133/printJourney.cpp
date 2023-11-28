#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

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

struct pa_ir{
  TrainInfoPerStation* first;
  TrainInfoPerStation* second;
};
listOfObjects<TrainInfoPerStation*>* expand(listOfObjects<TrainInfoPerStation*> *info){
  listOfObjects<TrainInfoPerStation*>* currList = info;
  listOfObjects<TrainInfoPerStation*>* expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    TrainInfoPerStation* currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
    
      for (int i=0; i < 7; i++) {
	if (currInfo->daysOfWeek[i]) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);	  
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);	  
	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
	  }
	  else {
	    newExpandedListElement->next = expandedList;
	    expandedList->prev = newExpandedListElement;
	    expandedList = newExpandedListElement;
	  }
	  listLength++;
	}
      }
    }
    currList = currList->next;
  }
  return expandedList;
}
class ParentConnectionInfo{    
  public: 
  int index; 
  listOfObjects<pa_ir> *head;
  listOfObjects<pa_ir> *tail;
    ParentConnectionInfo(){head = nullptr; tail= nullptr;}
    ParentConnectionInfo(int n){index = n; head = nullptr; tail= nullptr;}       //constructor
    void add(pa_ir info){                                         //add elements to the list
      if(head == nullptr){                                                       // if head is nullptr
        head = new listOfObjects<pa_ir>(info);                    // assign value to the head and tail
        tail = head;                                                                  
      } else{                                                        
        tail->next = new listOfObjects<pa_ir>(info);               // add element to the list 
        tail = tail->next;                                                        // update the tail pointer
      }
      return;
    }
    void del(){     
      if(head == nullptr) return;
      listOfObjects<pa_ir> *temp = tail; 
      listOfObjects<pa_ir> *h = head; 
      if(head == tail){
        head = nullptr;
        tail = nullptr;
      }else{
        while(h->next != tail) {          
          h=h->next;        
        }
        h->next = nullptr;
        tail = h;
      }          
      delete temp;      
      return;
    }
    bool isEmp(){
      return head == nullptr;                                                      // returns true if list is empty
    }
    ~ParentConnectionInfo(){};
};

class listOfParents{
  public:
  listOfObjects<ParentConnectionInfo*> *head; // head of the list
  listOfObjects<ParentConnectionInfo*> *tail; // tail of the list
  public:
    listOfParents(){head = nullptr; tail= nullptr;} // dafault constructor
   
    void add(ParentConnectionInfo* info){                                         //add elements to the list     
      if(head == nullptr){                                                       // if head is nullptr
        head = new listOfObjects<ParentConnectionInfo*>(info);                    // assign value to the head and tail
        tail = head;                                                                  
      } else{                                                        
        tail->next = new listOfObjects<ParentConnectionInfo*>(info);               // add element to the list 
        tail = tail->next;                                                        // update the tail pointer        
      }
      return;
    }
    void del(){     
      if(head == nullptr) return;
      listOfObjects<ParentConnectionInfo*> *temp = tail; 
      listOfObjects<ParentConnectionInfo*> *h = head; 
      if(head == tail){
        head = nullptr;
        tail = nullptr;
      }else{
        while(h->next != tail) {          
          h=h->next;        
        }
        h->next = nullptr;
        tail = h;
      }          
      delete temp;      
      return;
    }
    bool isEmp(){
      return head == nullptr;                                                      // returns true if list is empty
    }  
    ~listOfParents(){;}
};

class eval{
    listOfParents* list;
    int start;
    int end;
    int maxstop;
    int maxtime;
    listOfParents* final = new listOfParents();  
    ParentConnectionInfo* journeys = new ParentConnectionInfo();  
    listOfParents *required = new listOfParents();
    int n=0;
  public:
    eval (listOfParents* list,int start, int end,int maxstop, int maxtime){ 
      this->list = list; 
      this->start = start;
      this->end = end;
      this->maxstop = maxstop;
      this->maxtime = maxtime;
    }

    void check(ParentConnectionInfo* info){
      listOfObjects<pa_ir> *s = info->head;
      int stops = 0;     
      listOfObjects<pa_ir> *pre = nullptr;      
      while(s != nullptr){                
        int d1;
        int d2;
        for(int i=0;i<7;i++) {
          if(s->object.second->daysOfWeek[i]){d2=i;}    
          if(s->object.first->daysOfWeek[i]) {d1=i;}                
        }
                
        if(!(pre == nullptr)){
          int d ;
          for(int i=0;i<7;i++) if(pre->object.first->daysOfWeek[i]) d=i;
          if(pre->object.first->journeyCode == s->object.first->journeyCode){                        
            if(d2 == d && pre->object.first->depTime < s->object.second->arrTime) return;
            if((d2+1)%7 == d && pre->object.first->depTime > s->object.second->arrTime) return;
            if(d2 != d ) return;                       
          }          
          else{
            stops++;
            int t1 = s->object.second->arrTime/100;
            int m1 = s->object.second->arrTime%100;
            int t2 = pre->object.first->depTime/100;
            int m2 = pre->object.first->depTime%100;
            float wait_time;
            if(d2 == d){
              if(s->object.second->arrTime > pre->object.first->depTime) wait_time = 24*7+t1-t2+(m1-m2)/60;
              else wait_time = t2-t1+ (m2-m1)/60;
            } else{
              wait_time = 24*((7+(d-d2))%7) + t2-t1 + (m2-m1)/60;               
            }
            if(wait_time > maxtime){return;}        
          }
          
        }
        pre = s;                                            
        s=s->next;
        if(stops > maxstop){return;}
      }    
      n++;         
      form(info);   
      return;      
    }

    void make_jour(listOfObjects<ParentConnectionInfo*> *parents){
      if(parents == nullptr) return; 
      listOfObjects<pa_ir> *info = parents->object->head;             
      while(info != nullptr){
        journeys->add(info->object);             
        make_jour(parents->next);
        if(parents->object->index == start) check(journeys);      
        journeys->del();                    
        info = info->next;
      }        
    }
    
    void make_par(int n){
      if(n == start){
        make_jour(final->head);
        return;
      }       
      listOfObjects<ParentConnectionInfo*> *info = list[n].head; 
      while(info != nullptr){
        final->add(info->object);      
        make_par(info->object->index);
        final->del();  
        info = info->next;
      }
    }
    void print(listOfObjects<TrainInfoPerStation*> *info){
    listOfObjects<TrainInfoPerStation*> *currList = info;
    listOfObjects<TrainInfoPerStation*> *prev = nullptr;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  while (currList != nullptr) {
    TrainInfoPerStation* currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
    }
    void form(ParentConnectionInfo* info){      
      listOfObjects<pa_ir> *p = info->head;
      listOfObjects<TrainInfoPerStation*> *ti_head = nullptr;
      listOfObjects<TrainInfoPerStation*>* ti_tail = nullptr;
      while(p != nullptr){
        TrainInfoPerStation* i = p->object.first;
        TrainInfoPerStation* i2 = p->object.second;
        if(ti_head == nullptr) {          
          ti_tail = new listOfObjects<TrainInfoPerStation*>(i2);
          ti_head = ti_tail;
          ti_tail->next = new listOfObjects<TrainInfoPerStation*>(i);
          (ti_tail->next)->prev = ti_tail;
          ti_tail =ti_tail->next;          
        }
        else{         
          ti_tail->next = new listOfObjects<TrainInfoPerStation*>(i2); 
          (ti_tail->next)->prev = ti_tail;         
          ti_tail = ti_tail->next;          
          ti_tail->next = new listOfObjects<TrainInfoPerStation*>(i);
          (ti_tail->next)->prev = ti_tail;
          ti_tail = ti_tail->next;
        }        
        p = p->next;
      } 
      cout<<RED<<"JOURNEY NO: "<<RESET<<n<<endl;
      ti_head = ti_tail;
      listOfObjects<TrainInfoPerStation*> *temp = ti_head;
      while(temp != nullptr){
        temp->next = ti_tail->prev;
        temp = temp->next;
        ti_tail = ti_tail->prev;
      }
      
      print(ti_head);     
    }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  
  // insert your code here
  // insert your code here
  int index1 = stnNameToIndex.get(srcStnName)->value;                           // index of source station 
  int index2 = stnNameToIndex.get(destStnName)->value;                          // index of destination station 
  listOfParents parent[DICT_SIZE];
  
  int* color = new int[DICT_SIZE];                                              // stores the colour of the node 
  for(int i=0; i<DICT_SIZE; i++){                                               // initialize all elements to white color
    color[i] = 0;                                                               // 0 for white; 1 for grey
  }
  
  color[index1] = 1;                                                            // initialize source color to grey
  Queue q(DICT_SIZE);                                                           // create a queue
  q.enqueue(index1);                                                            // add source station to the queue
  
  while(q.sz() != 0){  
    int i = q.top();                                                             // top element of the queue
    listOfObjects<StationConnectionInfo *> *toStations =adjacency[i].toStations; // adjacent stations of station i
    if(i != index2){
      while(toStations != nullptr){
        int index = toStations->object->adjacentStnIndex;                        // index of a adjacent station of station(i)
          
        if(index != index1){        
          ParentConnectionInfo* par = new ParentConnectionInfo(i);
          listOfObjects<TrainInfoPerStation*> *info = toStations->object->trains;
          listOfObjects<TrainInfoPerStation*> *expanded = expand(info);
          listOfObjects<StationConnectionInfo *> *fromstat =adjacency[index].fromStations;
          while(fromstat->object->adjacentStnIndex != i) fromstat = fromstat->next; 
          listOfObjects<TrainInfoPerStation*> *from_info = fromstat->object->trains;
                
          while(expanded != nullptr){                      
            int d;            
            for (int i=0;i<7;i++) if(expanded->object->daysOfWeek[i]) {d = i; break;}
            listOfObjects<TrainInfoPerStation*> *from_expand = expand(from_info);
            while(from_expand->object->journeyCode != expanded->object->journeyCode) from_expand = from_expand->next; 
            while(from_expand->object->journeyCode == expanded->object->journeyCode){
              if(from_expand->object->daysOfWeek[d] && from_expand->object->arrTime > expanded->object->depTime) break;
              else if(from_expand->object->daysOfWeek[(d+1)%7] && from_expand->object->arrTime < expanded->object->depTime) break;
              from_expand = from_expand->next;
            }
            //cout<<from_info->object->depTime<<endl;
            pa_ir p;
            p.first = expanded->object ;   
            p.second = from_expand->object;              
            par->add(p);         
            //cout<<p.first->depTime<<" "<<p.second->depTime<<endl;  
            expanded= expanded->next;
          }           
          parent[index].add(par);    
        }
        // if the color is white, make it grey      
        if(color[index] == 0) {color[index] = 1;q.enqueue(index);}        
        toStations = toStations->next;     
      }
    }   
    q.dequeue();
  }

  eval e(parent,index1,index2,maxStopOvers,maxTransitTime);
  cout<<endl;
  e.make_par(index2);    
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}

#endif
