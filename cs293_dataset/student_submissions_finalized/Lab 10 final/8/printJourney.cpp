#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int maxStopOvers = 0; 
int maxTransitTime = 0;
int destination;
StationAdjacencyList* adjacency_list;
listOfObjects<listOfObjects<TrainInfoPerStation *>*>* final_journeys;

listOfObjects<TrainInfoPerStation *>* reverse(listOfObjects<TrainInfoPerStation *>* end_node){
  listOfObjects<TrainInfoPerStation *>* head = new listOfObjects<TrainInfoPerStation *>(nullptr);
  // listOfObjects<TrainInfoPerStation *>* new_ptr = head;
  listOfObjects<TrainInfoPerStation *>* ptr = end_node;
  while (ptr != nullptr)
  {
    listOfObjects<TrainInfoPerStation *>* temp = head->next;
    head->next = new listOfObjects<TrainInfoPerStation *>(ptr -> object);
    head -> next -> next = temp;
    ptr = ptr -> prev;
  }
  return head->next; 
}

bool condition(TrainInfoPerStation* t,int level, int day){
// if it doesn't run on that day then return false simply
// check the condition of maxTriansitTime on a station
  if (!level) return true;
  
  if(t->daysOfWeek[day]){
    return false;
  }

  else if(t->depTime - t->arrTime >= maxTransitTime){
      return false;
  }

  else{
    return true;
  }
  
}

listOfObjects<TrainInfoPerStation*>* append(listOfObjects<TrainInfoPerStation *>* curr_journey,TrainInfoPerStation * train){
  listOfObjects<TrainInfoPerStation *>* new_train = new listOfObjects<TrainInfoPerStation *>(train);
  new_train -> prev = curr_journey;
  return new_train;
}

// int get_arrival_time(listOfObjects<StationConnectionInfo*>* from_stations,int prevStn,int journey_number){
//   listOfObjects<StationConnectionInfo *>* ptr = from_stations;
//   while (ptr != nullptr)
//   {
//     listOfObjects<TrainInfoPerStation *>* journey = ptr -> object -> trains;
//     while (journey != nullptr)
//     {
//       if (journey->object->journeyCode == journey_number)
//       {
//         return journey->object->arrTime;
//       }
//       journey = journey->next;
//     }
//    ptr = ptr -> next; 
//   }
  
//   cout << "error in finding the arrival time" << endl;
//   return 0;
// }

void journey_append(listOfObjects<TrainInfoPerStation*>* journey, listOfObjects<listOfObjects<TrainInfoPerStation*>*>* final_journeys){
  listOfObjects<listOfObjects<TrainInfoPerStation*>*>* new_journey = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(journey);
  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* temp = final_journeys -> next;
  final_journeys -> next = new_journey;
  new_journey -> next = temp;
}

void specialDFS(int stn,int day,listOfObjects<TrainInfoPerStation *>* curr_journey,int level)
  {

  // int arrival_time;
  if (level >= maxStopOvers) return;

  // if (level)
    // arrival_time = get_arrival_time(adjacency_list[stn].fromStations,prevStn, curr_journey->object->journeyCode);
  // else
    // arrival_time = INT32_MAX;
  

  if (stn == destination)
  {
    journey_append(curr_journey,final_journeys);
    return;
  }


  listOfObjects<StationConnectionInfo*>* connection = adjacency_list[stn].toStations;
  // int arrival_time = get_arrival_time(adjacency_list[stn].fromStations,prevStn, curr_journey->object->journeyCode);

  while (connection != nullptr)
  {
    // int curr_to_stn = connection->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *>* train = connection -> object -> trains;

    while (train != nullptr)
    {
      if (!level)
      {
        specialDFS(connection->object->adjacentStnIndex,day,append(curr_journey,train->object),level+1);
        return;
      }
       
      if (curr_journey->object->journeyCode == train->object->journeyCode)
      {
        specialDFS(connection->object->adjacentStnIndex,day,curr_journey,level);
      }

      if (condition(train->object,level, day)){
        specialDFS(connection->object->adjacentStnIndex,day,append(curr_journey,train->object),level+1);
      }

      train = train -> next;
    }

    connection = connection -> next; 
  }
  
  return; 
  //do special dfs
  //somehow keep track of the journeys we are following
}
// DFS(stn,day,curr_journey=list(stn),destination,final_journeys,level=0)
//  arrival_time = curr_journey.
//  if stn is destination:
// 		final_journeys.journey_append(journey)
// 	if level >= maxStopOvers:
// 			return  
// 	for connection in adjacency_list[station].toStn:
// 			for train in connection:
// 				if condition(train,day,maxTansittime,train):
// 					DFS(connection.adjacentStn,append(curr_journey,train),level+1)

// BFS(node)
// 	q.push(node) 
//  visited[node] = true 
// 	while not q.empty:
// 		process(q.top)
// 		
//  	for e in neighbour[node]:
//  		if not visited[e]	
// 				visited[e] = true
// 				q.push(e) 	
// 			
// 		q.pop()

// BFS(int source,int destination)
// 	q.push(source) 
//  visited[source] = true 
// 	int level = 0
// 	while not q.empty:
// 		if level >= maxStopOvers:
// 			break
// 		process(q.top)
// 		
//  	for e in toStations:
//  		if condition(e):	
// 				q.push(e) 	
// 		level++	
// 		
// 		q.pop()

void Planner::printPlanJourneys(string srcStnName, string destStnName, int _maxStopOvers, int _maxTransitTime)
{

  // insert your code here

  int source_stn = stnNameToIndex.get(srcStnName)->value;
  destination = stnNameToIndex.get(destStnName)->value;
  maxStopOvers = _maxStopOvers;
  maxTransitTime = _maxTransitTime*60;
  adjacency_list = this->adjacency;
  final_journeys = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(nullptr);
  // listOfObjects<TrainInfoPerStation *>* curr_journey = new listOfObjects<TrainInfoPerStation *>()
  
  for(int i=0; i<7; i++){
    specialDFS(source_stn,i, nullptr,0); 
  }

  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* ptr = final_journeys->next;

  if (ptr == nullptr)
  {
    cout << "no journeys for the given stations";
    return;
  }
  
  while (ptr -> next != nullptr)
  {
    printStationInfo(reverse(ptr->object));
    cout << "=============================================================================="<<endl;
    ptr = ptr -> next;
  }
  
  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp


  
  return;
}



#endif
