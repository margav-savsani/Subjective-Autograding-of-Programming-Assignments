#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

	// insert your code here
	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp

	// cout << "\n\n****This function is to be implemented by you.*****" << endl;

	// Entry<int> E = stnNameToIndex.get(srcStnName);
	// int s = E.value;



	// First thing: Print the adjacency list
	// for(int i=0; i<DICT_SIZE; i++){
	// 	if(adjacency[i].toStations != nullptr || adjacency[i].fromStations != nullptr){
	// 		cout << "Station: " << stnNameToIndex.getKeyAtIndex(i) << "::::::::::"<< endl;

	// 		cout << "to-List\n";

	// 		auto currNode = adjacency[i].toStations;
	// 		while(currNode != nullptr){
	// 			cout << "---" << endl;
	// 			cout << stnNameToIndex.getKeyAtIndex(currNode->object->adjacentStnIndex) << endl;
	// 			auto iNode = currNode->object->trains;
	// 			while(iNode != nullptr){
	// 				cout << iNode->object->journeyCode << ", " << iNode->object->arrTime << ", " << iNode->object->depTime << endl;
	// 				iNode = iNode->next;
	// 			}
	// 			cout << "---" << endl;
	// 			currNode = currNode->next;
	// 		}

	// 		cout << "\nfrom-List\n";
	// 		currNode = adjacency[i].fromStations;
	// 		while(currNode != nullptr){
	// 			cout << "---" << endl;
	// 			cout << stnNameToIndex.getKeyAtIndex(currNode->object->adjacentStnIndex) << endl;
	// 			auto iNode = currNode->object->trains;
	// 			while(iNode != nullptr){
	// 				cout << iNode->object->journeyCode << ", " << iNode->object->arrTime << ", " << iNode->object->depTime << endl;
	// 				iNode = iNode->next;
	// 			}
	// 			cout << "---" << endl;
	// 			currNode = currNode->next;
	// 		}

	// 		cout << "\n\n\n" << endl; 
	// 	}
	// }





	// :::::::::::::::::::::::::::: BFS :::::::::::::::::::::::::::::::::::::::::::


	int currStn = stnNameToIndex.get(srcStnName)->value;
	int finalStn = stnNameToIndex.get(destStnName)->value;

	// Finding all possible paths of outgoing trains
	bool noPath = true;
	auto outstnlist = adjacency[currStn].toStations;
	while(outstnlist != nullptr){



		auto trainList = outstnlist->object->trains;
		// EXPLORE PATH OF EACH TRAIN IN TRAIN LIST, if it reaches destStn, print it, else explore next train path
		while( trainList !=  nullptr){

			int trainNumber = trainList->object->journeyCode;

			vector<int> s;
			s.push_back(currStn);	// Adding current station
			s.push_back(outstnlist->object->adjacentStnIndex); // Adding this adjacent station


			// right now, i am at outstn, nearest neighbout of srcstn
			int stnindex = outstnlist->object->adjacentStnIndex;
			while(true){
				auto nextOutStnList = adjacency[stnindex].toStations;

				// if u have reached destStation, print string and get out.
				if( stnindex == finalStn ){
					noPath = false;
					s.push_back(stnindex);
					// PRINTING
					
					cout << GREEN << "\n\n\n-----DIRECT JOURNEY-----" << RESET << endl;
					cout << "TRAIN NUMBER (Journey Code): " << trainNumber << "\n\n";
					for(int i=0; i<s.size()-1-1; i++){
						cout << stnNameToIndex.getKeyAtIndex(s[i]) << " ---> ";
					}
					cout << stnNameToIndex.getKeyAtIndex(s[s.size()-1]) << endl;
					cout << "\n\n\n";
					break;
				}
				
				// if train is not present in any of these nextOutStn, then get out.
				bool isPresent = false;
				// SEARCHING FOR THIS TRAIN
				while(nextOutStnList != nullptr){

					auto thistrainList = nextOutStnList->object->trains;
					while(thistrainList != nullptr){

						int thistrainNumber = thistrainList->object->journeyCode;
						if( thistrainNumber == trainNumber ){
							isPresent = true;

							// Now add this stn to s and move on to the next station 
							s.push_back(nextOutStnList->object->adjacentStnIndex);
							// update the stnindex 
							stnindex = nextOutStnList->object->adjacentStnIndex;
							break;
						}

						// END
						thistrainList = thistrainList->next;
					}

					if (isPresent) break;

					//END
					nextOutStnList = nextOutStnList->next;
				}


				if (!isPresent){
					break;
				}

			}




			// END
			trainList = trainList->next;
		}


		// END
		outstnlist = outstnlist->next;
	}


	if(noPath){
		cout << RED << "\n\n\nNO DIRECT JOURNEY AVAILABLE\n\n\n" << RESET << endl;
	}


	return;
}

#endif
