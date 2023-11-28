// :::::::::::::NOTE::::::::::::::
//The code below, does not completely implement the asked functionality but still it do something
// from which we can infer some information. So the overall output of the code is formatted in a nice manner,
// which lists the all possible paths means, what are the  possibilities of changing trains between a station
// could happen during a journey has been handled in this code but the task to implement the max Transition time to change trains
// hasn't been implemented.


#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"
#include <vector>

using namespace std;


// A newly defined struct which stores certain attributes for the Station Node.
struct StationNode
{
	int stnIndex;
	listOfObjects<TrainInfoPerStation *> *trains;
	listOfObjects<StationNode*>* adjacentPath;
	StationNode* parent;



	StationNode(int index, listOfObjects<TrainInfoPerStation*>* trn, listOfObjects<StationNode*>* adj, StationNode* par){
		stnIndex = index;
		trains = trn;
		adjacentPath = adj;
		parent = par;
	}
};

// Class representing the tree constructed out of the DFS traversal of the given station list, using the above defined struct.
class DFSTree{
	public:
	StationNode* root;

	DFSTree(int index, listOfObjects<TrainInfoPerStation*>* trn, StationNode* parent){
		root = new StationNode(index, nullptr, nullptr, parent);
		root->stnIndex = index;
	}
};


// main function which accordingly stores the station node at its correct position and alos providing the correct set of attributes to each StationNode object.
bool DFS(StationAdjacencyList* src, int srcIndex, StationAdjacencyList* dest, int destIndex, StationNode* node, StationAdjacencyList* adjacency){

	if(srcIndex == destIndex) {
		return true;
	}
	if(src->toStations == nullptr) {
		return false;
	}
	bool retWhat = false;
	if(src != nullptr){
		listOfObjects<StationNode*>* adj = nullptr;
		listOfObjects<StationConnectionInfo*>* temp = src->toStations;
		while(temp!= nullptr){
				StationNode* dummy = new StationNode(temp->object->adjacentStnIndex, temp->object->trains, nullptr, node);
				if(!DFS(&adjacency[temp->object->adjacentStnIndex], temp->object->adjacentStnIndex, dest, destIndex, dummy, adjacency)){
					delete dummy;
					temp = temp->next;
					continue;
				}
				else{
					if(adj == nullptr){
						adj = new listOfObjects<StationNode*>(dummy);
					}
					else{
						listOfObjects<StationNode*>* curr = adj;
						while(curr->next!= nullptr){
							curr = curr->next;
						}
						curr->next = new listOfObjects<StationNode*>(dummy);
						curr->next->prev = curr;
					}
					retWhat = true;
				}
			temp = temp->next;
		}
		node->adjacentPath = adj;
	}
	return retWhat;
}


// Just a sample function to check the correctness of tree stored.
void printTree(StationNode* node, Dictionary<int> stnNameToIndex){
	cout << stnNameToIndex.getKeyAtIndex(node->stnIndex) << endl;
	listOfObjects<StationNode*>* currNode = node->adjacentPath;
	while(currNode != nullptr){
		printTree(currNode->object, stnNameToIndex);
		currNode = currNode->next;
	}
}



// this stores the last leaf nodes of the DFS tree because we can easily find all possible 
// paths by travelling "UP", using the parent pointer of the DFS tree.
void lastNodes(StationNode* node, listOfObjects<StationNode*>* &possible){
	if(node->adjacentPath == nullptr){
		if(possible == nullptr){
			possible = new listOfObjects<StationNode*>(node);
		}
		else{
			listOfObjects<StationNode*>* curr = possible;
			while(possible->next != nullptr){
				possible = possible->next;
			}
			possible->next = new listOfObjects<StationNode*>(node);
		}
	}
	listOfObjects<StationNode*>* curr = node->adjacentPath;
	while(curr != nullptr){
		lastNodes(curr->object, possible);
		curr = curr->next;
	}
}


// These two function packed between dashed lines are just to store those above discussed "possible paths" into a 
// listofObjects of listofObjects, YES! it is a list of lists.

//--------------------------------------------------------------------------------
void storeIt(StationNode* node, listOfObjects<StationNode*>* &path){
	if(node->parent == nullptr){
		path = new listOfObjects<StationNode*>(node);
		return;
	}
	storeIt(node->parent, path);
	listOfObjects<StationNode*>* curr = path;
	while(curr->next != nullptr){
		curr = curr->next;
	}
	curr->next = new listOfObjects<StationNode*>(node);
}

listOfObjects<listOfObjects<StationNode*>*>* getPaths(listOfObjects<StationNode*>* &possible){
	listOfObjects<listOfObjects<StationNode*>*>* paths = nullptr;
	listOfObjects<StationNode*>* last = possible;
	while(last != nullptr){
		listOfObjects<StationNode*>* path = nullptr;
		storeIt(last->object, path);

		if(paths == nullptr){
			paths = new listOfObjects<listOfObjects<StationNode*>*>(path);
		}
		else{
			listOfObjects<listOfObjects<StationNode*>*>* dum = paths;
			while(dum->next != nullptr){
				dum = dum->next;
			}
			dum->next = new listOfObjects<listOfObjects<StationNode*>*>(path);
		}
		last = last->next;
	}
	return paths;
}
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////

// converting the time to hour(float)
float getHr(int time){
	float hr = time/100;
	float min = time%100;

	return (hr + (min/60));
}


// bool condition(){
// 	return true;
// }



// this function tries to give all possible journeys through all possible trains using the copy constructor functionality of vectors
void getWay(listOfObjects<StationNode*>* path, vector<vector<TrainInfoPerStation*>> &possWay, vector<TrainInfoPerStation*> currPath, TrainInfoPerStation* prevTrain, int maxStopOvers, int currCross){
	if(path == nullptr){
		// cout << currCross << ":" << maxStopOvers << endl;
		if(currCross <= maxStopOvers)
		possWay.push_back(currPath);
		return;
	}
	listOfObjects<TrainInfoPerStation*>* currTrain = path->object->trains;
	TrainInfoPerStation* keyTrain = nullptr;
	while(currTrain != nullptr){
		if(prevTrain == nullptr){
			getWay(path->next, possWay, currPath, currTrain->object, maxStopOvers, currCross);
			currTrain = currTrain->next;
			continue;
		}

		else if(currTrain->object->journeyCode == prevTrain->journeyCode){
			if(currTrain->object->depTime == -1 && path->next != nullptr){
				keyTrain = currTrain->object;
				break;
			}
			currPath.push_back(currTrain->object);
			getWay(path->next, possWay, currPath, currTrain->object, maxStopOvers, currCross);
			return;
		}

		currTrain = currTrain->next;
	}
	
	currTrain = path->object->trains;
	while(currTrain != nullptr && prevTrain != nullptr){
		if(keyTrain != currTrain->object){
			if(true){
				currPath.push_back(currTrain->object);
				getWay(path->next, possWay, currPath, currTrain->object, maxStopOvers, currCross + 1);
			}
		}
		currTrain = currTrain->next;
	}
}


// The callee function which calls all(not all though) the above defined functions. Also it prints the output of the code in a nicely framed manner. 
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	StationAdjacencyList* source = &adjacency[stnNameToIndex.get(srcStnName)->value];
	StationAdjacencyList* destination = &adjacency[stnNameToIndex.get(destStnName)->value];

	DFSTree tree(stnNameToIndex.get(srcStnName)->value, nullptr, nullptr);
	DFS(source, stnNameToIndex.get(srcStnName)->value, destination, stnNameToIndex.get(destStnName)->value, tree.root, adjacency);
	
	
	// adjacent pathes for root;
	tree.root->trains = stationInfo[stnNameToIndex.get(srcStnName)->value];

	// cout << "*************************************************" << endl;
	listOfObjects<StationNode*>* possible = nullptr;
	lastNodes(tree.root, possible);
	listOfObjects<listOfObjects<StationNode*>*>* paths = getPaths(possible);


	listOfObjects<listOfObjects<StationNode*>*>* currPath = paths;
	while(currPath!= nullptr){
		// cout << "ksdssss" << endl;
		vector<vector<TrainInfoPerStation*>> possWay;
		vector<TrainInfoPerStation*> dummy;
		getWay(currPath->object, possWay, dummy, nullptr, maxStopOvers, 0);
		// cout << possWay.size() << endl;
		int m=1;
		for(int i=0; i<possWay.size(); i++){
			listOfObjects<StationNode*>* A = currPath->object;
			cout << "Possible Routes:"<< endl;
			cout << "--------------------------------------------------------" << endl;
			for(int j=0; j<possWay[i].size(); j++){
				cout << "FROM  " << RED << stnNameToIndex.getKeyAtIndex(A->object->stnIndex) << RESET << "  " ;
				cout << "THROUGH  Train(" << GREEN << possWay[i][j]->journeyCode << RESET << ")  TO  " << RED << stnNameToIndex.getKeyAtIndex(A->next->object->stnIndex)  << RESET << endl;
				for(int p=0; p<7; p++){
					if(possWay[i][j]->daysOfWeek[p]){
						cout << RED << "Day: " << RESET << days[p] << "   "<< GREEN << "Arrival Time: " << RESET << possWay[i][j]->arrTime << "   " << BLUE << "Departure Time: " << RESET << possWay[i][j]->depTime << endl;
					}
				}
				cout << endl;
				A = A->next;
			}
			cout << endl;
		}
		currPath = currPath->next;
	}

	return;
}

#endif