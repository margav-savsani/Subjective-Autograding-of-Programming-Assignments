#include <bits/types/struct_sched_param.h>

#include <string>
#ifndef PRINT_JOURNEY_CPP
#include "planner.cpp"
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

string maxString = "                               ";

class Node {
   public:
    TrainInfoPerStation *journeyCode;
    TrainInfoPerStation *journeyCodeTO;
    int day;
    Node *parent;
    string station;
    listOfObjects<Node *> *adjacentNode;
    Node(Node *parent = nullptr) {
        adjacentNode = nullptr;
        this->parent = parent;
    }
};

bool isPresent(listOfObjects<TrainInfoPerStation *> *o, int a) {
    listOfObjects<TrainInfoPerStation *> *c = o;
    while (c != nullptr) {
        if (c->object->journeyCode == a) return true;
        c = c->next;
    }
    return false;
}

bool isValid(TrainInfoPerStation *A, TrainInfoPerStation *B, int maxTransitTime) {
    int day1;
    for (int i = 0; i < 7; i++) {
        if (A->daysOfWeek[i]) {
            day1 = i;
            break;
        }
    }

    int day2;
    for (int i = 0; i < 7; i++) {
        if (B->daysOfWeek[i]) {
            day2 = i;
            break;
        }
    }
    int diffday = (day2 - day1) * 24;
    double h1 = (double)A->arrTime / (double)100 + (double)(A->arrTime % 100) / (double)60;
    double h2 = (double)B->depTime / (double)100 + (double)(B->depTime % 100) / (double)60;
    double h = h2 - h1;
    h = h + diffday;
    return h <= maxTransitTime and h >= -0.001;
}

int findDay(TrainInfoPerStation *A){
    for (int i = 0; i < 7; i ++) {
        if(A->daysOfWeek[i]) return i;
    }
    return 0;
}

// int findDay(TrainInfoPerStation *A, TrainInfoPerStation *B){
//     for (int i = findDay(B); i < 7; i ++) {
//         if(A->daysOfWeek[i]) return i;
//     }
//     return 0;
// }
bool BFS(int journeycode, int srcIndex, int destIndex, int maxStopOvers, int maxTransitTime, Node *List,
         StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> **stationInfo,Dictionary<int> stnNameToIndex) {
    // List->index = srcIndex;
    if (maxStopOvers < 0) return false;
    if (srcIndex == destIndex) return true;

    listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[srcIndex];

    StationAdjacencyList *adjacentNode = &adjacency[srcIndex];

    while (currTrain != nullptr) {
        // finding next station
        listOfObjects<StationConnectionInfo *> *Stn = adjacentNode->toStations;
        while (Stn != nullptr) {
            listOfObjects<TrainInfoPerStation *> *Train = stationInfo[Stn->object->adjacentStnIndex];
            while (Train != nullptr) {
                if (Train->object->journeyCode == currTrain->object->journeyCode) {
                    if (currTrain->object->stopSeq + 1 == Train->object->stopSeq or true) {
                        // station is Stn Train is Train
                        // cout << Train->object->journeyCode << endl;
                        bool isFound = false;
                        Node *T = new Node(List);
                        T->journeyCode = currTrain->object;
                        T->journeyCodeTO = Train->object;
                        T->station = stnNameToIndex.getKeyAtIndex(Stn->object->adjacentStnIndex);
                        if (List->adjacentNode == nullptr) List->adjacentNode = new listOfObjects<Node *>(T);
                        else {
                            List->adjacentNode->prev = new listOfObjects<Node *>(T);
                            List->adjacentNode->prev->next = List->adjacentNode;
                            List->adjacentNode = List->adjacentNode->prev;
                        }
                        if (currTrain->object->journeyCode == journeycode) {
                            isFound = BFS(journeycode, Stn->object->adjacentStnIndex, destIndex, maxStopOvers,
                                          maxTransitTime, T, adjacency, stationInfo,stnNameToIndex);
                        } else if (isValid(currTrain->object, Train->object, maxTransitTime)) {
                            isFound = BFS(journeycode, Stn->object->adjacentStnIndex, destIndex, maxStopOvers - 1,
                                          maxTransitTime, T, adjacency, stationInfo,stnNameToIndex);
                        }
                        if (!isFound) {
                            List->adjacentNode = List->adjacentNode->next;
                            if (List->adjacentNode != nullptr) {
                                delete List->adjacentNode->prev;
                                List->adjacentNode->prev = nullptr;
                            }
                            delete T;
                        }
                    }
                }
                Train = Train->next;
            }
            Stn = Stn->next;
        }
        currTrain = currTrain->next;
    }
    return (List->adjacentNode != nullptr);
}


string journeyArr(int a){
    if ( a == -1) return "Starts";
    return to_string(a);
}
string journeyDep(int a){
    if ( a == -1) return "Ends";
    return to_string(a);
}

void printer(Node *N,Planner * P, bool isFirst = true, string s = "") {

    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    
    if (N == nullptr) {
        cout << "end" << endl;
        return;
    }
    if (!isFirst) {
        listOfObjects<TrainInfoPerStation *> *stnInfoList = new listOfObjects<TrainInfoPerStation *>(N->journeyCode);
    
        s = s + "\n"+BLUE+"JourneyCode : " +RED+ to_string(N->journeyCode->journeyCode)+RESET +" \n";
        s = s + "From : "+N->parent->station + &maxString[(N->parent->station).length()] +"\t"+ days[findDay(N->journeyCode)] + "\t" + BLUE+" arr: "+ RED + journeyArr(N->journeyCode->arrTime) +" \t "+BLUE+"dep: "+RED+ journeyDep(N->journeyCode->depTime)+RESET+"\n";
        s = s + "To : "+N->station+ &maxString[(N->station).length()] +"\t"+ days[findDay(N->journeyCodeTO)] + "\t" + BLUE+" arr: "+ RED + journeyArr(N->journeyCodeTO->arrTime) +" \t "+BLUE+"dep: "+RED+ journeyDep(N->journeyCodeTO->depTime)+RESET+"\n";
        delete stnInfoList;
        // cout << N->journeyCode->journeyCode << endl;
    }
    listOfObjects<Node *> *currNode = N->adjacentNode;
    if (currNode == nullptr) {
        cout << s << endl;
        cout << "-------------------------------------" << endl;
        return;
    }
    while (currNode != nullptr) {
        printer(currNode->object,P, false,s);
        currNode = currNode->next;
    }
}

void sortListing(Node *N, listOfObjects<TrainInfoPerStation *> *Stn, listOfObjects<TrainInfoPerStation *> *lastN,
                 Planner *P, bool notFirst = true) {
    if (N == nullptr) return;

    if (Stn == nullptr) {
        Stn = new listOfObjects<TrainInfoPerStation *>(N->journeyCode);
        lastN = Stn;
    }
    if (N->adjacentNode == nullptr) {
        // cout << "---------------------------------------------------" << endl;
        cout << "Station : "<<N->station << "\t";
        P->printStationInfo(Stn->next);
        cout << "---------------------------------------------------" << endl;
        return;
    }

    listOfObjects<Node *> *curr = N->adjacentNode;
    while (curr != nullptr) {
        if (!notFirst or curr->object->journeyCode->journeyCode != N->journeyCode->journeyCode) {
            lastN->next = new listOfObjects<TrainInfoPerStation *>(curr->object->journeyCode);
            sortListing(curr->object, Stn, lastN->next, P);
            delete lastN->next;
            lastN->next = nullptr;
        }
        else{
            sortListing(curr->object, Stn, lastN, P);
        }
        curr = curr->next;
    }
}

void deleteAll(Node *N) {
    if (N == nullptr) return;
    listOfObjects<Node *> *currNode = N->adjacentNode;
    // if(currNode == nullptr) cout << "end" << endl;
    while (currNode != nullptr) {
        deleteAll(currNode->object);
        currNode = currNode->next;
    }
    delete N;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
    int srcIndex = stnNameToIndex.get(srcStnName)->value;
    int destIndex = stnNameToIndex.get(destStnName)->value;
    Node *List = new Node();
    List->journeyCode = nullptr;
    List->station = stnNameToIndex.getKeyAtIndex(srcIndex);

    // BFS(srcIndex, destIndex, maxStopOvers, List, adjacency, stationInfo);
    // void (f)(listOfObjects<TrainInfoPerStation *>*);
    // f = this->printStationInfo;

    // listOfObjects<TrainInfoPerStation *> *Trains = stationInfo[srcIndex];
    // printStationInfo(Trains);
    // while (Trains != nullptr) {

    listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[srcIndex];

    while (currTrain != nullptr) {
        bool isFound = false;
        // Node *T = new Node(List);
        // T->journeyCode = currTrain->object;

        // if (List->adjacentNode == nullptr) List->adjacentNode = new listOfObjects<Node *>(T);
        // else {
        //     List->adjacentNode->prev = new listOfObjects<Node *>(T);
        //     List->adjacentNode->prev->next = List->adjacentNode;
        //     List->adjacentNode = List->adjacentNode->prev;
        // }
        isFound = BFS(currTrain->object->journeyCode, srcIndex, destIndex, maxStopOvers, maxTransitTime, List,
                      adjacency, stationInfo,stnNameToIndex);
        // if (!isFound) {
        //     cout << "come" << endl;
        //     List->adjacentNode = List->adjacentNode->next;
        //     if (List->adjacentNode != nullptr) {
        //         delete List->adjacentNode->prev;
        //         List->adjacentNode->prev = nullptr;
        //     }
        //     delete T;
        // }
        currTrain = currTrain->next;
    }
    cout << "---------------------------------------------------" << endl;
    // sortListing(List, nullptr, nullptr, this,false);
    printer(List,this);

    // // Node of all stations
    // Node Stn[DICT_SIZE];
    // // BFS

    // // Heap
    // listOfObjects<int> *Heap = new listOfObjects<int>(srcIndex);
    // listOfObjects<int> *lastNode = Heap;
    // // bool isVisited[DICT_SIZE];bool isVisited[DICT_SIZE];
    // for(int i = 0; i < DICT_SIZE; i++) isVisited[i] = false;

    // Stn[Heap->object].parent = nullptr;
    // while(Heap != nullptr){

    //   // Add adjacent nodes in the list
    //   listOfObjects<StationConnectionInfo *> *currStn =
    //   adjacency[Heap->object].toStations; while (currStn != nullptr) {
    //     Stn[Heap->object].index = Heap->object;
    //     if(!isVisited[currStn->object->adjacentStnIndex]){
    //       isVisited[currStn->object->adjacentStnIndex] = true;
    //       lastNode->next = new
    //       listOfObjects<int>(currStn->object->adjacentStnIndex); lastNode =
    //       lastNode->next;
    //     }
    //     currStn = currStn->next;
    //   }

    // }

    cout << endl << endl << "This function is to be implemented by you." << endl;

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp
    deleteAll(List);
    return;
}

#endif
