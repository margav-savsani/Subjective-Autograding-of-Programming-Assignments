#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// stores TrainInfoPerStation with station index
class TIPSWithSI : public TrainInfoPerStation {
 public:
    int stationIndex;

    TIPSWithSI(int jCode, unsigned short stpSq, int aTm, int dTm, int station): TrainInfoPerStation(jCode,stpSq,aTm,dTm){
        journeyCode = jCode;
        stopSeq = stpSq;
        arrTime = aTm;
        depTime = dTm;
        for (int i = 0; i < 7; i++) { daysOfWeek[i] = false;}
        stationIndex = station;
    }
};

// stores traversed paths
struct PATH {
    int stops = -1;
    int currentStationIndex; 
    listOfObjects<TIPSWithSI *> *path = NULL;

    PATH(){}
    PATH(TIPSWithSI *x, int index){ append(x,index); }

    void append(TIPSWithSI *x, int index){
        if (path == NULL){
            path = new listOfObjects<TIPSWithSI *>(x);
        }
        else {
            path->next = new listOfObjects<TIPSWithSI *>(x);
            if (path->object->journeyCode != path->next->object->journeyCode) stops++;
            path = path->next;
        }
        path->object->stationIndex = currentStationIndex = index;
    }
};

listOfObjects<TrainInfoPerStation *> *PSI(listOfObjects<TIPSWithSI *> *v){
    listOfObjects<TIPSWithSI *> *x = v;
    listOfObjects<TrainInfoPerStation *> *ret;

    while (x != NULL){
        TrainInfoPerStation *y = x->object;
        TrainInfoPerStation *t = new TrainInfoPerStation(x->object->journeyCode,x->object->stopSeq,x->object->arrTime,x->object->depTime);
        for(int i=0; i<7; i++){
            if (y->daysOfWeek[i]) t->daysOfWeek[i] = 1;
        }
        ret->object = t;
    }
    return ret;
}

// FIFO queue
template <typename T>
struct queue {	
    listOfObjects<T> *front, *back; 
  	int size;

	queue() {
		front = back = NULL; size = 0;
	}

	void push_back(T obj) {
		if (size == 0) {
			size = 1;
			back = front = new listOfObjects<T>(obj);
		}
		else {
			size++;
			back->next = new listOfObjects<T>(obj);
			back = back->next;
		}
	}

	void pop_front() {
		if (size <= 1){
            size = 0;
            back = front =  NULL;
        }
		else {
			size--;
            front = front->next;		
            front->prev = NULL;
		}
	}

	T front_element() {
		if (front != NULL) return front->object;
        else return NULL;
	}
};

// starting node of the list of outgoing trains from source
listOfObjects<TIPSWithSI *> * initializeSourceOutTrains(StationAdjacencyList *adjacency, int sourceIndex, queue<PATH *> *q){
    listOfObjects<TIPSWithSI *> *ret = NULL;
    
    // x,y,z are just temporary variables to iterate over the adjacent trains of the source
    listOfObjects<StationConnectionInfo *>* x = adjacency[sourceIndex].toStations;
    listOfObjects<TrainInfoPerStation*>* y = NULL;
    listOfObjects<TIPSWithSI*>* z = NULL;

    while (x!=NULL){
        y = x->object->trains;
        while (y!=NULL){
            TIPSWithSI *p = new TIPSWithSI(y->object->journeyCode,y->object->stopSeq,y->object->arrTime,y->object->depTime,sourceIndex);
            if (ret == NULL){
                ret = new listOfObjects<TIPSWithSI*>(p);
                z = ret;
            }
            else {
                z->next = new listOfObjects<TIPSWithSI *>(p);
                z = z->next;
            }
            y = y->next;
        }
        x = x->next;
    }

    // now adding first element to queue
    listOfObjects<TIPSWithSI *> *r = ret;

    while(y!=NULL){
        q->push_back(new PATH(r->object,sourceIndex));
        r = r->next;
    }

    return ret;
}

bool feasibleTrainChange(TrainInfoPerStation *x, TrainInfoPerStation *y, int max){
    int t1 = x->arrTime, t2 = y->depTime, d1, d2;

    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            if (x->daysOfWeek[i] && y->daysOfWeek[j]) {
                d1 = i; d2 = j;
                int t = (t2-t1+2400)%2400, d = (d2-d1+7)%7 + (t1==t2);
                if (d*2400+t<=max) return 1;
            }
        }
    }
    return 0;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
  int sourceIndex = stnNameToIndex.get(srcStnName)->value;
  int destinationIndex = stnNameToIndex.get(destStnName)->value;
  string days[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

  listOfObjects<TIPSWithSI *> *finalTrains = NULL;

  queue<PATH *> *BFSqueue = new queue<PATH *>();
  // starting node of the list of outgoing trains from source
  listOfObjects<TIPSWithSI*> *sourceOutTrains = initializeSourceOutTrains(adjacency,sourceIndex,BFSqueue);
  // now the sourceOutTrains node pointer is ready

  while (BFSqueue->size != 0) {
        PATH *now = BFSqueue->front_element();

        if (now->currentStationIndex == destinationIndex){
            cout << "   Journey\n";
            listOfObjects<TIPSWithSI *> *output = now->path;
            
            int whichDay;
            for(int i=0; i<7; i++){
                if (output->object->daysOfWeek[i]) whichDay = i;
            }

            cout << "Departs JC: " << output->object->journeyCode << " " << stnNameToIndex.getKeyAtIndex(output->object->stationIndex)  << " " << days[whichDay] << " " << output->object->depTime << " | ";
            listOfObjects<TIPSWithSI*> *prevOutput = now->path;

            output = output->next;

            while (output != NULL){
                if (output->object->journeyCode != prevOutput->object->journeyCode){
                    for(int i=0; i<7; i++){
                        if (prevOutput->object->daysOfWeek[i]) whichDay = i;
                    }

                    cout << "Arrives " << stnNameToIndex.getKeyAtIndex(prevOutput->object->stationIndex) << " " << days[whichDay] << " " << prevOutput->object->arrTime << endl;

                    for(int i=0; i<7; i++){
                        if (output->object->daysOfWeek[i]) whichDay = i;
                    }

                    cout << "Departs JC: " << output->object->journeyCode << " " << stnNameToIndex.getKeyAtIndex(prevOutput->object->stationIndex) << " " << days[whichDay] << " " << prevOutput->object->depTime << " | ";

                }
                prevOutput = prevOutput->next;
                output = output->next;
            }

            cout << "Arrives " << stnNameToIndex.getKeyAtIndex(prevOutput->object->stationIndex) << " " << days[whichDay] << " " << prevOutput->object->arrTime << endl;
			cout << endl;
			BFSqueue->pop_front();
			continue;
        }

        int currStI = now->currentStationIndex;
        listOfObjects<TIPSWithSI *> *x = now->path;

        while(x->next != NULL) x = x->next;

        listOfObjects<StationConnectionInfo *> *y = adjacency[currStI].toStations; 

        while (y != NULL){
            int nextStI = y->object->adjacentStnIndex;
            listOfObjects<TIPSWithSI *> *z;

            printStationInfo(PSI(z));
        }

    //     while (BFSqueue.size != 0) {
    //         int mainNode = BFSqueue.front_element();
    //         listOfObjects<StationConnectionInfo*>* listOutTrainsIterator = adjacency[mainNode].toStations;

    //         while (listOutTrainsIterator != NULL) {
    //             int adjacentStation = listOutTrainsIterator->object->adjacentStnIndex; 
    //             listOfObjects<TrainInfoPerStation*>* listOutTrains = listOutTrainsIterator->object->trains;

    //             while (listOutTrains != NULL) {
    //                 if (listOutTrains->object->journeyCode == train) {
    //                     if (adjacentStation == destination) {
    //                         // if (!directTrains){
    //                         //   listOfObjects<TrainInfoPerStation *> *trainsFromSource = stationInfo[source];
    //                         //   while(trainsFromSource != NULL){
    //                         //     if (trainsFromSource->object->journeyCode == train){
    //                         //       finalTrains = new listOfObjects<TrainInfoPerStation *>(trainsFromSource->object);
    //                         //       break;
    //                         //     }
    //                         //     trainsFromSource = trainsFromSource->next;
    //                         //   }
    //                         //   directTrains = true;
    //                         // }
    //                         // else {
    //                         //   listOfObjects<TrainInfoPerStation *> *trainsFromSource = stationInfo[source];
    //                         //   while(trainsFromSource != NULL){
    //                         //     if (trainsFromSource->object->journeyCode == train){
    //                         //       finalTrains->next = new listOfObjects<TrainInfoPerStation *>(trainsFromSource->object);
    //                         //       break;
    //                         //     }
    //                         //     trainsFromSource = trainsFromSource->next;
    //                         //   }
    //                         // }
    //                     }
    //                     else {
    //                         BFSqueue.push_back(adjacentStation);
    //                     }
    //                     break;
    //                 }
    //                 listOutTrains = listOutTrains->next;
    //             }
    //             listOutTrainsIterator = listOutTrainsIterator->next;
    //         }
    //         BFSqueue.pop_front();
    //     }
    //     sourceOutTrains = sourceOutTrains->next;
    }
}

#endif
