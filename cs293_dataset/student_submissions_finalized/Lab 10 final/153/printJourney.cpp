#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef RESET
#define RESET "\033[0m"
#endif
#ifndef GREEN
#define GREEN "\033[32m"
#endif
#ifndef RED
#define RED "\033[31m"
#endif
#ifndef BLUE
#define BLUE "\033[34m"
#endif
#ifndef ORANGE
#define ORANGE "\033[33m"
#endif
#ifndef CYAN
#define CYAN "\033[36m"
#endif
#ifndef MAG
#define MAG "\033[35m"
#endif

using namespace std;
  
class Transition{
private:
  int station_id, wait, cur_jc, next_jc;
  //Naturally, wait is in minutes, because of the used time representation

public:
  Transition(){station_id=wait=cur_jc=next_jc=-1;}
  Transition(int sid, int cjc, int njc, int w){
    station_id=sid;
    cur_jc=cjc;
    next_jc=njc;
    wait=w;
  }
  ~Transition(){}

  bool isFirst(){return this->cur_jc==-1;}
  bool isLast(){return this->next_jc==-1;}

  int getStationId(){return this->station_id;}
  int getWait(){return this->wait;}
  int getArrCode(){return this->cur_jc;}
  int getDepCode(){return this->next_jc;}

};

listOfObjects<listOfObjects<Transition *> *> *getJourneyPlans(int, int, int);
int computeWaitingTime(int, int, int);
bool* computeRunningDays(listOfObjects<Transition*>*);
void printTransition(Transition*);
template <typename T>
listOfObjects<T>* mergeLists(listOfObjects<T>*, listOfObjects<T>*);
void printColoured(string, string);

string DAY_NAMES[7] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};

int g_dest_id, g_max_wait;
StationAdjacencyList* g_adj_lists;
listOfObjects<TrainInfoPerStation*> **g_stnInfo;
Dictionary<int>* g_name_index;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp


  // TODO: See plan.todo for complete plan
  g_adj_lists=this->adjacency;
  g_stnInfo = this->stationInfo;
  g_max_wait = maxTransitTime*60;
  g_name_index = &(this->stnNameToIndex);

  Entry<int> *entry =  this->stnNameToIndex.get(srcStnName);
  if(entry == nullptr) return;
  int src_ind = entry->value;
  entry =  this->stnNameToIndex.get(destStnName);
  if(entry == nullptr) return;
  g_dest_id = entry->value;

  listOfObjects<listOfObjects<Transition *> *> *plan_list = getJourneyPlans(src_ind, -1, maxStopOvers), *plan_list_iter;
  plan_list_iter = plan_list;
  listOfObjects<Transition *> *transition_iter = nullptr;
  bool* runningDays = nullptr;

  cout << "Journey Plans: ";printColoured(srcStnName, CYAN);cout<<" to ";printColoured(destStnName,CYAN);cout<<"\n";
  bool printed=false, common_exists; bool* running_days;
  while(plan_list_iter != nullptr){
    transition_iter = plan_list_iter->object;

    if(transition_iter == nullptr) continue;
    // TODO: Add code here to check which all days the journey plan is possible
    // That is, the days when all the involved trains are running. Bitwise AND of the days thing is enough for this
    // If there is no common day, avoid printing this.
    // Thus, a `bool printed;` would be required now

    common_exists = false;
    running_days = computeRunningDays(transition_iter);
    for(int i=0; i<7; i++) if(running_days[i]) common_exists = true;

    if(!common_exists){plan_list_iter=plan_list_iter->next;continue;}
    printed = true;
    cout << "\nPlan Availability Days: \n";printColoured("| ", BLUE);
    for(int i=0; i<7; i++) if(running_days[i]) printColoured(DAY_NAMES[i] + " | ", BLUE);
    cout << "\n";

    while(transition_iter != nullptr){
      printTransition(transition_iter->object);
      transition_iter = transition_iter->next;
    }

    plan_list_iter = plan_list_iter->next;
  }
  if(!printed) printColoured("No journey plans could be found\n\n", RED);
  if(printed) printColoured("Please check the days at which the respective plans are possible\n", RED);

  return;
}

listOfObjects<listOfObjects<Transition *> *> *getJourneyPlans(int cur_stat_id, int cur_j_id, int changes_left){
  if(changes_left < -1) return nullptr;
  if(cur_stat_id == g_dest_id) return new listOfObjects(new listOfObjects(new Transition(g_dest_id, cur_j_id, -1, 0)));

  listOfObjects<listOfObjects<Transition *> *> *res = nullptr, *cb_added = nullptr, *cb_added_iter = nullptr;
  listOfObjects<Transition *> *to_append_to;
  StationAdjacencyList *adj_list = &(g_adj_lists[cur_stat_id]);
  listOfObjects<StationConnectionInfo *> *cur_con = adj_list->toStations;
  listOfObjects<TrainInfoPerStation *> *cur_train;
  int adj_stat_id, waiting_time;

  while(cur_con != nullptr){
    adj_stat_id = cur_con->object->adjacentStnIndex;
    cur_train = cur_con->object->trains;
    while(cur_train != nullptr){
      if(cur_train->object->journeyCode != cur_j_id){
        waiting_time = cur_j_id==-1 ? 0 : computeWaitingTime(cur_stat_id, cur_j_id, cur_train->object->journeyCode);
        if(waiting_time < 0 || waiting_time > g_max_wait){
          cur_train = cur_train->next;
          continue;
        }


        cb_added = getJourneyPlans(adj_stat_id, cur_train->object->journeyCode, cur_stat_id == -1 ? changes_left : changes_left - 1);
        
        if(cb_added != nullptr){
          cb_added_iter = cb_added;
          while(cb_added_iter != nullptr){
            cb_added_iter->object = mergeLists(new listOfObjects(new Transition(cur_stat_id, cur_j_id, cur_train->object->journeyCode, waiting_time)), cb_added_iter->object);
            cb_added_iter=cb_added_iter->next;
          }
          res = mergeLists(res, cb_added);
        }
      }else{
        cb_added = getJourneyPlans(adj_stat_id, cur_j_id, changes_left);
        res = mergeLists(res, cb_added);
      }
      cur_train = cur_train->next;
    }
    cur_con=cur_con->next;
  }

  return res;
}

int computeWaitingTime(int stat_ind, int arr_jc, int dep_jc){
  if(arr_jc == dep_jc) return 0;

  listOfObjects<TrainInfoPerStation *> *train_info = g_stnInfo[stat_ind], *arr_train = nullptr, *dep_train = nullptr;

  while(train_info != nullptr && (arr_train == nullptr || dep_train == nullptr)){
    if(train_info->object->journeyCode == arr_jc) arr_train = train_info;
    if(train_info->object->journeyCode == dep_jc) dep_train = train_info;
    train_info = train_info->next;
  }

  if(arr_train == nullptr || dep_train == nullptr) return -1;

  int wait, t;
  t = dep_train->object->depTime;t = 60*(t/100) + t%100;
  wait = t;
  t = arr_train->object->arrTime;t = 60*(t/100) + t%100;
  wait = wait-t;

  return wait;
}

bool* computeRunningDays(listOfObjects<Transition *>* trans){
  // cout<<"\tflag\n";
  bool *res = (bool*)malloc(7*sizeof(bool));fill(res, res+7, 1);
  int train_id = trans->object->getDepCode(), station_id;
  listOfObjects<TrainInfoPerStation *> *info_source = nullptr;
  while(train_id != -1){
    station_id = trans->object->getStationId();
    info_source = g_stnInfo[station_id];

    // cout<<"\tflag1\n";
    while(info_source != nullptr && info_source->object->journeyCode != train_id) info_source = info_source->next;

    if(info_source == nullptr){
      for(int i=0; i<7; i++) res[i]=false;
      return res;
    }

    for(int i=0; i<7; i++) res[i] = res[i] && info_source->object->daysOfWeek[i];
    trans=trans->next;
    train_id = trans->object->getDepCode();
  }

  return res;
}

void printTransition(Transition* tr){
  if(tr->isFirst()) cout << "----------------------------------------\n\n";
  else cout << "\t|\n\t|\n";

  string stat_name = g_name_index->getKeyAtIndex(tr->getStationId());
  cout<<"At station ";printColoured(stat_name, CYAN);cout<<"\n";
  if(tr->isLast()) printColoured("You have arrived at your destination.\n", GREEN);
  else{
    if(tr->isFirst()) cout<<"Board ";
    else {cout<<"Change from ";printColoured("train "+to_string(tr->getArrCode()), ORANGE);cout<<" to ";}

    printColoured("train "+to_string(tr->getDepCode()), ORANGE);cout<<"\n"; 
    if(!tr->isFirst()) {cout << "Waiting time: ";printColoured(to_string(tr->getWait())+" minutes", MAG);cout<<"\n";}
  }

  if(tr->isLast()) cout << "\n";
  else cout << "\t|\n\t|\n";
}

template <typename T>
listOfObjects<T>* mergeLists(listOfObjects<T> *l1, listOfObjects<T> *l2){
  if(l1 == nullptr) return l2;
  if(l2 == nullptr) return l1;

  listOfObjects<T> *t1 = l1, *t2 = l2;
  while(t1->next != nullptr && t2->next != nullptr){
    t1=t1->next;
    t2=t2->next;
  } 

  if(t1->next == nullptr){
    t1->next = l2;
    l2->prev = t1;
    return l1;
  }
  if(t2->next == nullptr){
    t2->next = l1;
    l1->prev = t2;
    return l2;
  }

  return nullptr;
}

void printColoured(string txt, string color){
  cout << color << txt << RESET;
}

#endif
