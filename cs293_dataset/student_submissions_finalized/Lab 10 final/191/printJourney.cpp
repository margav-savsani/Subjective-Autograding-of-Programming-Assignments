#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
using namespace std;
  
//this function takes in the required arguments and stores in the stations ans trains vectors the required journeys, by taking in values as reference
void DFS_VISIT(int index,int finish_index, StationAdjacencyList* adjacency, int maxStopOvers, int maxTransitTime, vector<vector<int>> &stations, vector<vector<TrainInfoPerStation*>> &trains){

	static vector<vector<int>> answer_station[DICT_SIZE]; // this dictionary that helps in coloring vertices in the DFS Algorithm in Graph 
	static vector<vector<TrainInfoPerStation*>> answer_train[DICT_SIZE];
	static int color[DICT_SIZE]; // 0 for white, 1 for gray, 2 for black
	static int vool = 1;
	
	if(vool==1){//one time working block of statement
		for(int i=0;i<DICT_SIZE;i++){
			color[i] = 0;
		}
	}
	vool++;
	color[index] = 1; // color the node GRAY indicating that it has been discovered but its processing is being done
	
	auto adj = adjacency[index].toStations; // the adjacent nodes, the adjacency dicitonary array is taken in as argument
	//adj is the the list of StationConnectionInfo
	while(adj != nullptr){
		auto id = adj->object->adjacentStnIndex;
		if(id == finish_index){ // this is the base case or the finish case   
			
			auto train_object = adj->object->trains; // train_object is the list of trains travelling from node index to its immediate neighbour (Note that we are iterating through the neighbours)
			while(train_object != nullptr){ // iterating through the list of trains
				for(int iter1=0;iter1<7;iter1++){ // iterating through the days in a list when the train is moving
					if(train_object->object->daysOfWeek[iter1]){
						TrainInfoPerStation* tt1;
						tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime); // new object of TrainInfoPerStation* that is used to create a vector that is pushed_back in the strains vectors
						tt1->daysOfWeek[iter1] =1;
						vector<TrainInfoPerStation*> q{tt1};
						vector<int> w{index};
						stations.push_back(w);
						trains.push_back(q);
						
					}
				}
				train_object = train_object->next;
			}
		}
		else if(color[id] == 2){ // if color code of the node is BLACK
			auto x = answer_station[id];
			auto y = answer_train[id];
			auto train_object = adj->object->trains; // train_object is a list we need to iterate
			//getting the list of trains stored as ***pp_trains*** from the index station to id station in the perspective of id station
			auto pp = adjacency[id].fromStations;
			listOfObjects<TrainInfoPerStation*>* pp_trains;
			while(pp!=nullptr){ // iterating through the adjacent from nodes to find required node and hence the required trains
				
				if(pp->object->adjacentStnIndex == index){
					pp_trains = pp->object->trains;
					break;
				}
				pp = pp->next;
			}
			//getting done
			
			//iterating through the trains of the index station to the id station in persepctive of index station
			while(train_object != nullptr){ // iterating through the train_object list
			
				auto train = train_object->object->journeyCode; // train is the journeyCode of the train we are currently in
				//iterating through the listof trains from id station to finish station
				for(int i=0;i<x.size();i++){ // iterating thtough the journeys from node id to finish_index
					auto p = y[i][0]->journeyCode; // the journeyCode of the first train in the current journey that we have reached while iterating
					if(train == p){ // checking for whether the train is the same, in that case, we just combine the two datas to produce the outcome and also note that stopOvers doesn't change 
						for(int iter1=0;iter1<7;iter1++){
							if(y[i][0]->daysOfWeek[iter1]){
								auto c = iter1;
								auto aTime = y[i][0]->arrTime;
								if(aTime==-1)aTime = y[i][0]->depTime;
								while(true){
									if(train_object->object->daysOfWeek[c] && train_object->object->depTime < aTime){
									
										TrainInfoPerStation* tt1;
										tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
										tt1->daysOfWeek[c] = 1;
										
										//inserting in the required list
										auto q = x[i];
										auto w = y[i];
										q.erase(q.begin()); // updating the vector list 
										q.insert(q.begin(),index);// updating the vector list 
										w.erase(w.begin());// updating the vector list 
										w.insert(w.begin(), tt1);// updating the vector list 
										stations.push_back(q); // updating the stations vector which contains the answers
										trains.push_back(w); //updating the trains vector which contains the answers
										break;
										
									}
									else{
										c = (c + 6)%7;
										aTime += 2400;
									}
								}
							}
						}	
					}
					else{
						if(x[i].size() != maxStopOvers+1){//if the train is not same, then the stops in x[i] can't be maxStopOvers+! since then we would violate conditions for maximum stop Overs
							//finding the mytrain that is the train_object->object but in the view of id station
							TrainInfoPerStation* mytrain; // the train we are riding from sttaion index to station id but in the perspective of station id
							auto c = pp_trains;
							while(c!=nullptr){
								if(c->object->journeyCode == train_object->object->journeyCode){
									mytrain = c->object;
									break;
								}
								c = c->next;
							}
							//found the required mytrain object
							auto mytrain_com = y[i][0];
							//cout << mytrain->depTime << endl;
							//cout << mytrain_com->depTime << endl;
							//cout << mytrain_com->depTime << endl;
							//compare time start and update the required vector lists 
							
							//this whole process below checks for the maxTransitTimes
							for(int iter1 = 0;iter1 < 7; iter1++){
								if(mytrain->daysOfWeek[iter1]){
									int start = iter1*2400 + mytrain->arrTime;
									int stop = start + maxTransitTime;
									
									for(int iter2 = 0;iter2<7;iter2++){
										if(mytrain_com->daysOfWeek[iter2]){
											int time = mytrain_com->depTime + iter2*2400;
											if(stop >= 16800){ // condition for maxTransitTime on weekends
												if(time > start || time <= stop%16800){
													TrainInfoPerStation* tt1;
													
													auto c = train_object->object;//only used in below while loop
													auto my_iter = iter1;
													auto aTime = mytrain->arrTime;//only used below while loop
													while(true){
														if(c->daysOfWeek[my_iter] == true && c->depTime <= aTime){
															break;
														}
														else{
															my_iter = (my_iter+6)%7;
															aTime = aTime+2400;
														}
													}
													
													tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
													tt1->daysOfWeek[my_iter] = 1;
													
													//inserting in the required list
													auto q = x[i];
													auto w = y[i];
													q.insert(q.begin(),index);
													w.insert(w.begin(), tt1);
													stations.push_back(q);// updating the stations vector which contains the answers
													trains.push_back(w);//updating the trains vector which contains the answers
												}
											}
											else{
												if(time <= stop && time > start){// condition for maxTransitTime on normal days
													TrainInfoPerStation* tt1;
													
													auto c = train_object->object;//only used in below while loop
													auto my_iter = iter1;
													auto aTime = mytrain->arrTime;//only used below while loop
													while(true){
														if(c->daysOfWeek[my_iter] == true && c->depTime <= aTime){
															break;
														}
														else{
															my_iter = (my_iter+6)%7;
															aTime = aTime+2400;
														}
													}
													
													tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
													tt1->daysOfWeek[my_iter] = 1;//tt1 is the object from whom a vector is created to be entered into the stations vector
													
													//inserting in the required list
													auto q = x[i];
													auto w = y[i];
													q.insert(q.begin(),index);
													w.insert(w.begin(), tt1);
													stations.push_back(q);
													trains.push_back(w);
												}
											}
										}
									}
								}
							}
						}
					}	
				}
				
				train_object = train_object->next;
			}
		}
		else if(color[id] == 1){ // if color code is GRAY, continue and don't do anything, since by doing we are allowing repetitions of stations in our journey
			continue;
		}
		else if(color[id] == 0){ // if the node is WHITE
			vector<vector<int>> x; // which contains the 2D-vector of stations
			vector<vector<TrainInfoPerStation*>> y;//which contains the 2D-vector of the trains in the form of TrainInfoPerStation*
			DFS_VISIT(id, finish_index, adjacency, maxStopOvers, maxTransitTime, x, y);//Recusively calling DFS_VISIT for a white node
			auto train_object = adj->object->trains; // train_object is a list we need to iterate
			//getting the list of trains stored as ***pp_trains*** from the index station to id station in the perspective of id station
			auto pp = adjacency[id].fromStations;
			listOfObjects<TrainInfoPerStation*>* pp_trains;
			while(pp!=nullptr){ // iterating through the adjacent from nodes to find required node and hence the required trains
				
				if(pp->object->adjacentStnIndex == index){
					pp_trains = pp->object->trains;
					break;
				}
				pp = pp->next;
			}
			//getting done
			
			//iterating through the trains of the index station to the id station in persepctive of index station
			while(train_object != nullptr){ // iterating through the train_object list
			
				auto train = train_object->object->journeyCode; // train is the journeyCode of the train we are currently in
				//iterating through the listof trains from id station to finish station
				for(int i=0;i<x.size();i++){ // iterating thtough the journeys from node id to finish_index
					auto p = y[i][0]->journeyCode; // the journeyCode of the first train in the current journey that we have reached while iterating
					if(train == p){ // checking for whether the train is the same, in that case, we just combine the two datas to produce the outcome and also note that stopOvers doesn't change 
						for(int iter1=0;iter1<7;iter1++){
							if(y[i][0]->daysOfWeek[iter1]){
								auto c = iter1;
								auto aTime = y[i][0]->arrTime;
								if(aTime==-1)aTime = y[i][0]->depTime;
								while(true){
									if(train_object->object->daysOfWeek[c] && train_object->object->depTime < aTime){
									
										TrainInfoPerStation* tt1;
										tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
										tt1->daysOfWeek[c] = 1;
										
										//inserting in the required list
										auto q = x[i];
										auto w = y[i];
										q.erase(q.begin()); // updating the vector list 
										q.insert(q.begin(),index);// updating the vector list 
										w.erase(w.begin());// updating the vector list 
										w.insert(w.begin(), tt1);// updating the vector list 
										stations.push_back(q); // updating the stations vector which contains the answers
										trains.push_back(w); //updating the trains vector which contains the answers
										break;
										
									}
									else{
										c = (c + 6)%7;
										aTime += 2400;
									}
								}
							}
						}	
					}
					else{
						if(x[i].size() != maxStopOvers+1){//if the train is not same, then the stops in x[i] can't be maxStopOvers+! since then we would violate conditions for maximum stop Overs
							//finding the mytrain that is the train_object->object but in the view of id station
							TrainInfoPerStation* mytrain; // the train we are riding from sttaion index to station id but in the perspective of station id
							auto c = pp_trains;
							while(c!=nullptr){
								if(c->object->journeyCode == train_object->object->journeyCode){
									mytrain = c->object;
									break;
								}
								c = c->next;
							}
							//found the required mytrain object
							auto mytrain_com = y[i][0];
							//cout << mytrain->depTime << endl;
							//cout << mytrain_com->depTime << endl;
							//cout << mytrain_com->depTime << endl;
							//compare time start and update the required vector lists 
							
							//this whole process below checks for the maxTransitTimes
							for(int iter1 = 0;iter1 < 7; iter1++){
								if(mytrain->daysOfWeek[iter1]){
									int start = iter1*2400 + mytrain->arrTime;
									int stop = start + maxTransitTime;
									
									for(int iter2 = 0;iter2<7;iter2++){
										if(mytrain_com->daysOfWeek[iter2]){
											int time = mytrain_com->depTime + iter2*2400;
											if(stop >= 16800){ // condition for maxTransitTime on weekends
												if(time > start || time <= stop%16800){
													TrainInfoPerStation* tt1;
													
													auto c = train_object->object;//only used in below while loop
													auto my_iter = iter1;
													auto aTime = mytrain->arrTime;//only used below while loop
													while(true){
														if(c->daysOfWeek[my_iter] == true && c->depTime <= aTime){
															break;
														}
														else{
															my_iter = (my_iter+6)%7;
															aTime = aTime+2400;
														}
													}
													
													tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
													tt1->daysOfWeek[my_iter] = 1;
													
													//inserting in the required list
													auto q = x[i];
													auto w = y[i];
													q.insert(q.begin(),index);
													w.insert(w.begin(), tt1);
													stations.push_back(q);// updating the stations vector which contains the answers
													trains.push_back(w);//updating the trains vector which contains the answers
												}
											}
											else{
												if(time <= stop && time > start){// condition for maxTransitTime on normal days
													TrainInfoPerStation* tt1;
													
													auto c = train_object->object;//only used in below while loop
													auto my_iter = iter1;
													auto aTime = mytrain->arrTime;//only used below while loop
													while(true){
														if(c->daysOfWeek[my_iter] == true && c->depTime <= aTime){
															break;
														}
														else{
															my_iter = (my_iter+6)%7;
															aTime = aTime+2400;
														}
													}
													
													tt1 = new TrainInfoPerStation(train_object->object->journeyCode, train_object->object->stopSeq, train_object->object->arrTime, train_object->object->depTime);
													tt1->daysOfWeek[my_iter] = 1;//tt1 is the object from whom a vector is created to be entered into the stations vector
													
													//inserting in the required list
													auto q = x[i];
													auto w = y[i];
													q.insert(q.begin(),index);
													w.insert(w.begin(), tt1);
													stations.push_back(q);
													trains.push_back(w);
												}
											}
										}
									}
								}
							}
						}
					}	
				}
				
				train_object = train_object->next;
			}
		}
		adj = adj->next;
	}
	color[index] = 2; // after completing the DFS-VISIT color the node BLACK
	answer_station[index] = stations;
	answer_train[index] = trains;
	vool--;
}
 

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
	
 	auto start_index = stnNameToIndex.get(srcStnName)->value; //the srcStnName index of the dictionary
	auto finish_index = stnNameToIndex.get(destStnName)->value; // the destStnName index of the dicitionary
	vector<vector<int>> answer_ordering;
	vector<vector<TrainInfoPerStation*>> answer_code;
	
	DFS_VISIT(start_index, finish_index, adjacency, maxStopOvers, maxTransitTime*100, answer_ordering, answer_code);
	
	for(int i=0;i<answer_ordering.size();i++){
		listOfObjects<TrainInfoPerStation*> *l = new listOfObjects<TrainInfoPerStation*>(answer_code.at(i).at(answer_ordering.at(i).size()-1));
		auto c = l;
		
		for(int j=0;j<answer_ordering.at(i).size();j++){
			cout << stnNameToIndex.getKeyAtIndex(answer_ordering.at(i).at(j)) << " -> ";
		}
		cout << stnNameToIndex.getKeyAtIndex(finish_index) << endl;
		
		for(int j=answer_ordering.at(i).size()-2;j>=0;j--){
			//cout << answer_ordering.at(i).at(j) << " and " << (answer_code.at(i).at(j))->journeyCode << endl;
			c->next = new listOfObjects<TrainInfoPerStation*>(answer_code.at(i).at(j));
			c = c->next;
		}
		printStationInfo(l);
		
	}		
	
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  return;
}

#endif
