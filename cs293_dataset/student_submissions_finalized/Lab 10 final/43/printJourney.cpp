#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
// This function gives the listOfObjects which contains every journey route
listOfObjects<listOfObjects<TrainInfoPerStation *>*> * recursion(string srcStnName, string destStnName,Dictionary<int> stnNameToIndex,StationAdjacencyList* adjacency){
        Entry<int> *p = stnNameToIndex.get(srcStnName);
        listOfObjects<StationConnectionInfo *> * m1 = adjacency[p->value].toStations;
        //This is the base case for getting the route
        if(srcStnName == destStnName){
            return new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0)));
        }
        //This is the term which terminates the other cases(unnecessary cases).
        if(m1 == nullptr){
            return nullptr;
        }
        listOfObjects<listOfObjects<TrainInfoPerStation *>*> * result = nullptr;
        while(m1 != nullptr){
            listOfObjects<TrainInfoPerStation*> * trains = m1->object->trains; 
            string st = stnNameToIndex.getKeyAtIndex(m1->object->adjacentStnIndex);
            //This gives the list of routes from adjacent station to destination.
            listOfObjects<listOfObjects<TrainInfoPerStation *>*> * h = recursion(st,destStnName,stnNameToIndex,adjacency); 
            if(h != nullptr){
               while(h != nullptr){
                 listOfObjects<TrainInfoPerStation*> * trains1 = trains;
                 while(trains1 != nullptr){
                        //This is taking each train and adding to the recursion.
                        listOfObjects<TrainInfoPerStation*>* s = new listOfObjects<TrainInfoPerStation*>(trains1->object);
                        //Linking inside the list using pointers
                        s->next = h->object;
                        h->object->prev = s;
                        if(result == nullptr){
                            // Creating a new object
                            result = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(s);
                        }
                        else{
                            //Adding everything to the listOfObjects
                            listOfObjects<listOfObjects<TrainInfoPerStation *>*>*z = result;
                            while(z->next != nullptr){
                                z = z->next;
                            }
                            //Linking inside the list using pointers.
                            listOfObjects<listOfObjects<TrainInfoPerStation *>*> * y= new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(s);
                            y->prev = z;
                            z->next = y;
                        }
                        trains1 = trains1->next;
                    }
                h = h->next;
               } 
            }
            m1 = m1->next;
        }
        // Returns the list of all the routes from source to destination.
        return result;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{   
    // This gives the list of routes from source to destination
   listOfObjects<listOfObjects<TrainInfoPerStation *>*> * rs1 =  recursion(srcStnName,destStnName,stnNameToIndex,adjacency);
   int k = 0;
   // If a route exists
   if(rs1 != nullptr){
        int j = 1;
        while(rs1 != nullptr){
            // Taking each journey route and analysing them
            listOfObjects<TrainInfoPerStation*>* journey = rs1->object;
            int l = 0;
            bool check = true;
            // This is the variable keeps track of maxStopsOver and maxTransittime
            while(journey != nullptr){
                if(journey->next != nullptr&&journey->next->object->journeyCode != 0){
                    if(journey->object->journeyCode != journey->next->object->journeyCode){
                        l++;//Counting number of stopOvers.
                        int p = journey->next->object->arrTime - journey->object->depTime;
                        if(p < 0){p = p + 2400;}
                        p = p/100;
                        if( p > maxTransitTime){
                            //Checking transittime.
                            check = false;
                            break;
                        }    
                    }
                }
                journey = journey->next;
            }
            if(l > maxStopOvers){
                //This checks the maxStopOvers
                check = false;
            }
            if(check){
                int s = 1;
                //This prints the journey number
                cout<<"-----------------JOURNEY:"<<j<<"-------------"<<endl;
                listOfObjects<TrainInfoPerStation*>* d = rs1->object;
                int jc = d->object->journeyCode;
                while(d->object->journeyCode!= 0){
                    if(d->object->journeyCode != jc){
                        //Shows whether a train change is required
                        jc = d->object->journeyCode;
                        cout<<"--------TRAIN CHANGE REQUIRED-----------"<<endl;
                    }
                    listOfObjects<TrainInfoPerStation*>* e = new listOfObjects<TrainInfoPerStation*>(d->object);
                    cout<<"Station :"<<s<<" to "<<endl;
                    printStationInfo(e);
                    cout<<"Station :"<<s+1<<endl;
                    s++;
                    d = d->next;
                }
                j++;
            }
            rs1 = rs1->next;  
        }
        //If no route is available.
        if( j == 1){
           cout<<"----------NO JOURNEYS AVAILABLE--------"<<endl; 
        }
   }
   else{
    //This is if route doesnt exist.
    cout<<"---------NO JOURNEYS AVAILABLE--------"<<endl;
   }
}
#endif
