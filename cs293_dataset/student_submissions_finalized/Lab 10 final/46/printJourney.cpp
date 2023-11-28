#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

using namespace std;  

class data{ // contains the information of one part of journey
  public:
    int jrnycode,day,day2,start_time,end_time;
    string start_stn,end_stn;
  data(int jrnycode,int day,int day2,int start_time,int end_time,string start_stn,string end_stn){
    this->jrnycode = jrnycode;
    this->day = day;
    this->day2 = day2;
    this->start_time = start_time;
    this->end_time = end_time;
    this->start_stn = start_stn;
    this->end_stn = end_stn;
  }
  data(){};
};

template<typename T> class list {
 public:
  data object;
  list<T> *next;
  list<T> *prev;
  
  // Constructor
  list(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~list() {;}
};

list<data> *store,*end = nullptr;

void my_recur(string srcname,Dictionary<int> stnNameToIndex,StationAdjacencyList adjacency[512], list<data> *store,int index,int jrnycode,int day,int ar_time,int &cnt,int maxStopOvers,int maxTransitTime,int destStnIdx);

int time_diff(int d1,int t1,int d2, int t2) {
  if(d1>d2){
    d2+=7;
  }
  if(d1==d2 && t1>t2) return -1;
  int t1_h = t1/100;
  int t2_h = t2/100;
  int t1_min = t1%100;
  int t2_min = t2%100;
  int del_min = t2_min-t1_min;
  int del_h = t2_h-t1_h+(24*(d2-d1));
  if(del_min<0){
    del_min+=60;
    del_h-=1;
  }
  return del_h*100+del_min;
}

int len(list<data> *stor){
  if(stor==nullptr) return 0;
  list<data> *n = stor;
  int code = n->object.jrnycode;
  //cout <<"************"<<endl;
  //cout <<"old_code = "<<code<<endl;
  int i=0;
  while(n!=nullptr){
    n = n->prev;
    if(n!=nullptr){
    if(n->object.jrnycode!=code){
      i++;
      code = n->object.jrnycode;
      // cout <<"new_code  = "<<code<<endl;
    }
    }
  }
  //cout << "'''''''''''''"<<endl;
  return i;
}

string ind_to_name(int i){
  int n=i;
  string s="bllll";
switch (n)
    {
    case 0:
      s = "Sunday";
      break;
    case 1:
      s = "Monday";
      break;
    case 2:
      s = "Tuesday";
      break;
    case 3:
      s = "Wednesday";
      break;
    case 4:
      s = "Thursday";
      break;
    case 5:
      s = "Friday";
      break;
    case 6:
      s = "Saturday";
      break;
    default:
      break;
    }
    return s;
}

void my_print(list<data> *stor){
  if(stor==nullptr) return;
  list<data> *n = stor;
  while(stor->prev!=nullptr){
    stor=stor->prev;
  }

  while(stor!=nullptr){
    data store=stor->object;
    
    int n=store.day;
    int n2 = store.day2;
    string d1=ind_to_name(n);
    string d2=ind_to_name(n2);

    cout << "Train number is "<<RED<<store.jrnycode<<RESET<<" from "<< GREEN<<store.start_stn<<RESET<<" -- start day is "<<d1<<" start time is "<<RED<<store.start_time<<RESET<<" end day is "<<d2<< " end time is "<<RED<<store.end_time<<RESET<<" to "<<BLUE<<store.end_stn<<RESET<<endl;
    cout <<endl;
    stor = stor->next;
  }
  stor = n;
  cout <<"=================================================\n"<<endl;

}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;
  
  if(srcStnIdx==destStnIdx){
    cout << "There are no trains, you should walk by yourself :) "<<endl;
    return;
  }

  listOfObjects<StationConnectionInfo *> * adj = adjacency[srcStnIdx].toStations;
  
  while(adj!=nullptr) {

    StationConnectionInfo* st_info = adj->object; // contains the info the station in the adjacent list of the srcStn
    listOfObjects<TrainInfoPerStation*> *trains = st_info->trains; // contains the list of all trains from srcstn to a stn from adj_list
    
    while(trains!=nullptr){

      int cnt = 0; // src stn is not a intermediate stn

      int ar_time = trains->object->arrTime; // time at which it reaches the src stn
      
      int dep_time = trains->object->depTime; // time at which it departs from the src stn
      
      int jrnycode = trains->object->journeyCode; // jrny code of the particular train

      // cout << "code = "<<jrnycode<<endl;

      bool *days = trains->object->daysOfWeek; // It's weekly schedule basically

      int index =  st_info->adjacentStnIndex; // index of the adjacent station(A)

      string name = stnNameToIndex.getKeyAtIndex(index); // name of the adjacent station(A)

      for(int i=0;i<7;i++) { // for each day in a week
        if(days[i]==0) continue; // If there is no train on that day
        else{ // recurring on the adjacent station
        //cout <<"11111111111111111"<<endl;
          my_recur(srcStnName,stnNameToIndex,adjacency,store,index,jrnycode,i,dep_time,cnt,maxStopOvers,maxTransitTime,destStnIdx);
          //cout <<"22222222222222"<<endl;
        }
      }    
      trains = trains->next; // iteration on trains
    }   
    adj =adj->next; // iteration on adjacent stations
  }
  return;   
}


void my_recur(string srcnaam,Dictionary<int> stnNameToIndex,StationAdjacencyList adjacency[512],list<data> *store, int index,int code,int day,int t1,int &cnt,int maxStopOvers,int maxTransitTime,int destStnIdx){

  int pr_index = stnNameToIndex.get(srcnaam)->value;
  int get_cnt = len(store);
  if(get_cnt>maxStopOvers){
    return;
  }
   string curr_name = stnNameToIndex.getKeyAtIndex(index);
   string d_name = stnNameToIndex.getKeyAtIndex(destStnIdx);


  listOfObjects<StationConnectionInfo *> * adj1 = adjacency[index].toStations; // adjacent stations list

  if(adj1==nullptr && index==destStnIdx){

    listOfObjects<StationConnectionInfo*> *from = adjacency[index].fromStations;// contains the list of all the trains reaching the curr_station
    while(from!=nullptr){

      StationConnectionInfo* prev_info = from->object;

      if(pr_index==prev_info->adjacentStnIndex){

        listOfObjects<TrainInfoPerStation*> *my_trains = prev_info->trains;
        while(my_trains!=nullptr){
          if(my_trains->object->journeyCode == code){
            int day_2=0;
            int my_arr = my_trains->object->arrTime;
            bool *my_days = my_trains->object->daysOfWeek;
            for (int j=0;j<14;j++){
              int i=j;
              if(my_days[j%7]==1&&i>=day){
                if(i==day && my_arr>t1){
                  day_2=day;
                  break;
                }
                else if(i==day && my_arr<=t1){
                  continue;
                }
                else{
                  day_2=i%7;
                  break;
                }
              }
            }

      data tmp = data(code,day,day_2,t1,my_arr,srcnaam,curr_name); // storing the information of one part of the journey
      if(store==nullptr){
       store = new list<data> (tmp);
      }
      else{
        store->next = new list<data> (tmp);
        (store->next)->prev = store;
        store = store->next;
      }

  int new_cnt = len(store);
  if(new_cnt>maxStopOvers){
    return;
  }
      my_print(store);
         if(store!=nullptr){
          store=store->prev;
          if(store!=nullptr){
            store->next=nullptr;
            cnt--;
            return;
          }
        }
        break;
          }
          my_trains=my_trains->next;
        }
      }
      from  = from->next;
    }
    // cnt--;
    return;
  }

  if(adj1==nullptr and index!=destStnIdx){
    return;
  }

   //cout <<"===========firstpart============="<<endl;
  while(adj1!=nullptr) {
    
    StationConnectionInfo* st_info = adj1->object; // contains the info the station in the adjacent list of the srcStn

    listOfObjects<TrainInfoPerStation*> *trains = st_info->trains; // contains the list of all trains from srcstn to a stn from adj_list

    while(trains!=nullptr){

      int t2=-123; // some random number :)
                   // t2 is the time at which the train reaches the curr_stn
      int day_2=-1;

      int jrnycode = trains->object->journeyCode; // jrny code of this particular train

      int ar_time = trains->object->arrTime; // time at which it reaches the current station

      int dep_time = trains->object->depTime; // time at which it departs from the current station

      bool *days = trains->object->daysOfWeek; // weekly schedule of the train

      for (int j=0;j<14;j++){
        int i=j;
        if(days[j%7]==1&&i>=day){
          if(i==day && ar_time>t1){
            day_2=day;
            break;
          }
          else if(i==day && ar_time<=t1){
            continue;
          }
          else{
            day_2=i%7;
            break;
          }
        }
      }

      int inde =  st_info->adjacentStnIndex; // index of adjacent station 

      string name = stnNameToIndex.getKeyAtIndex(inde); // name of the adjacent station

      string srcname = srcnaam; // srcname (i.e, the parent station of the current station) is passed as an argument

      // t1 == dep_time from the prev stn
      // t2 == arr_time for the new stn in the adj list

      t2 = ar_time;

      data tmp = data(code,day,day_2,t1,t2,srcname,curr_name); // storing the information of one part of the journey

      // cout <<endl;
      // cout <<"#############before#############"<<endl;
      // my_print(store);

      if(store==nullptr){
       store = new list<data> (tmp);
      }
      else{
        list<data> *my = store;
        if (!(my->object.start_stn==tmp.start_stn)){ 
        store->next = new list<data> (tmp);
        (store->next)->prev = store;
        store = store->next;
        }
      }
      // cout << "############after###########"<<endl;
      // my_print(store);
      cout <<endl;

      if(index == destStnIdx) {
         my_print(store);
         if(store!=nullptr){
          store=store->prev;
          if(store!=nullptr){
            store->next=nullptr;
          }
        }
        //cnt--;
        return;
      }

      for(int i=0;i<7;i++) {

        if(days[i]==0) continue; // if there are no trains on that day

        else{
          int day_1 = day_2,day_2 = i; // day_1 = day on which the train reaches the curr_station from parent station
                                     // day_2 = day on which the train departs from the curr_station to the adjacent station

          int time_1 = ar_time, time_2 = dep_time; // AS the name suggests, they are the arraival and dept time from the current station

          // cout <<"|||||||||||||"<<endl;
          // cout <<ar_time<<endl;
          // cout <<"|||||||||||||||"<<endl;
          int transit = time_diff(day_1,time_1,day_2,time_2); // transit time

          if(code == jrnycode) transit = 0;
          int c = transit/100+1; // some manipulations
          if(transit%100==0){
            c--;
          }

          if(transit==-1 || c >maxTransitTime){
          if(store!=nullptr){
            store=store->prev;
            if(store!=nullptr){
              store->next=nullptr;
            }
          }
          // cnt--;
            return;
          }
          //cnt++;
          //cout <<"33333333333333333333333"<<endl;
          my_recur(curr_name,stnNameToIndex, adjacency,store,inde,jrnycode,i,dep_time,cnt,maxStopOvers,maxTransitTime,destStnIdx);
          // cout <<"4444444444444444444444444444"<<endl;
          break;
        }
      }
      trains = trains->next;
    }   
    adj1 =adj1->next;
  }
  //cnt--;
}

#endif