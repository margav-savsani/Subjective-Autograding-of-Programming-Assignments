#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


class trainList{
    public:
    listOfObjects<TrainInfoPerStation *> *jour;
    string stnName;
    int dep;
    int arr;
    int wait;

    trainList(){
        TrainInfoPerStation* cons=new TrainInfoPerStation(-1, -1, -2, -2);
        jour = new listOfObjects<TrainInfoPerStation *>(cons);
        dep=-1;
        arr=-1;
        wait = 0;
    }
};

class journeyList{
    public:
    listOfObjects<trainList *> *trList;
    listOfObjects<int> *stops;

    journeyList(){
        trList=nullptr;
    }
};
  
listOfObjects<journeyList *> *dfs(string dest, listOfObjects<StationConnectionInfo*> *station, listOfObjects<journeyList*> *final, StationAdjacencyList *adjacency, Dictionary<int> *stnNameToIndex, listOfObjects<TrainInfoPerStation * > *prevTrain, int maxStopOvers, int maxTransitTime){
    //cout<<"Welcome"<<endl;
    static journeyList * construct=new journeyList();
    static int recursionDepth=0;
    static int stopOvers=0;
    listOfObjects<StationConnectionInfo *> *curr=station;
    listOfObjects<journeyList *> *answer=new listOfObjects<journeyList *>(construct);
    
    while(curr!=nullptr){
        listOfObjects<TrainInfoPerStation *> * train=curr->object->trains;
        while(train!=nullptr){
            //listOfObjects<trainList *> *finaltrain=
            cout<<stnNameToIndex->getKeyAtIndex(curr->object->adjacentStnIndex)<<endl; 
            cout<<recursionDepth<<endl;
            listOfObjects<trainList *> *finaltrain1=new listOfObjects<trainList*>(new trainList());
            finaltrain1->object->jour=prevTrain;
            finaltrain1->object->wait=0;
            finaltrain1->next=new listOfObjects<trainList *>(new trainList());
            if(recursionDepth!=0){
                if(train->object!=prevTrain->object){
                    stopOvers++;
                    int arr = prevTrain->object->arrTime;
                    int dep = train->object->depTime;
                    int transit=0;
                    if(dep<arr){
                        transit=dep+2400-arr;
                    }
                    else{
                        transit=dep-arr;
                    }
                    if(transit>maxTransitTime){
                        cout<<transit<<endl;
                        return nullptr;
                    }
                    else{
                        finaltrain1->object->wait=transit;
                        finaltrain1->object->dep=prevTrain->object->depTime;
                        finaltrain1->object->arr=train->object->arrTime;
                        finaltrain1->object->stnName=stnNameToIndex->getKeyAtIndex(curr->object->adjacentStnIndex);
                    }
                }
            }
            else{
                stopOvers=0;
                finaltrain1->object->wait=0;
                finaltrain1->object->dep=prevTrain->object->depTime;
                finaltrain1->object->arr=train->object->arrTime;
                finaltrain1->object->stnName=stnNameToIndex->getKeyAtIndex(curr->object->adjacentStnIndex);
            }
            
            if(stopOvers>maxStopOvers){
                //cout<<"ret2"<<endl;
                return nullptr;
            }
            if(curr->object->adjacentStnIndex == stnNameToIndex->hashValue(dest)){
                //cout<<"here"<<endl;
                listOfObjects<journeyList *> *toReturn = new listOfObjects<journeyList *>(construct);
                toReturn->object->trList=new listOfObjects<trainList *>(new trainList());
                toReturn->object->trList->object->jour=finaltrain1->object->jour;
                toReturn->object->trList->object->arr=finaltrain1->object->arr;
                toReturn->object->trList->object->dep=finaltrain1->object->dep;
                toReturn->object->trList->object->stnName=finaltrain1->object->stnName;
                toReturn->object->trList->object->wait=finaltrain1->object->wait;
                toReturn->object->stops->object=stopOvers;
                //listOfObjects<journeyList *> *temp1=final;
                //if(temp1==nullptr){
                //    final=toReturn;
                //   return final;
                //}
                //while(temp1->next!=nullptr){
                //    temp1=temp1->next;
                //}
                //temp1->next=toReturn;
                //return final;
                return toReturn;
            }
            recursionDepth++;
            listOfObjects<journeyList *> *ret=dfs(dest, adjacency[curr->object->adjacentStnIndex].toStations, final, adjacency, stnNameToIndex, train, maxStopOvers, maxTransitTime);
            recursionDepth--;
            stopOvers--;
            if(ret==nullptr){
                return nullptr;
            }
            else{
                if(finaltrain1!=nullptr){
                    //cout<<"here111"<<endl;
                    listOfObjects<journeyList *> *ret1=ret;
                    while(ret1!=nullptr){
                        listOfObjects<trainList *> *smn=new listOfObjects<trainList *>(finaltrain1->object);
                        smn->next=ret1->object->trList;
                        ret1->object->trList=smn;
                        ret1=ret1->next;
                    }
                }
                listOfObjects<journeyList *> *answer1=answer;
                if(answer1==nullptr){
                    answer=ret;
                }
                else{
                    while(answer1->next!=nullptr){
                        answer1=answer1->next;
                    }
                    answer1->next=ret;   
                }
            }
            train=train->next;
        }
        curr=curr->next;
    }
    return answer;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
    listOfObjects<StationConnectionInfo*> *curr=adjacency[stnNameToIndex.hashValue(srcStnName)].toStations;
    journeyList * construct=new journeyList();
    listOfObjects<journeyList *> *ans = nullptr;
    listOfObjects<journeyList *> *ans1 = ans;
    listOfObjects<trainList*> *answ=new listOfObjects<trainList*>(new trainList());

    ans=dfs(destStnName, curr, ans1, adjacency, &stnNameToIndex, curr->object->trains, maxStopOvers, maxTransitTime);
    cout<<"Yo"<<endl;
    cout<<(ans==nullptr)<<endl;
    ans1=ans;
    while(ans1!=nullptr){
        listOfObjects<trainList*> *temp=ans1->object->trList;
        while(temp!=nullptr){
            cout<<"Station Name: "<<RED<<temp->object->stnName<<RESET<<endl;
            cout<<"Train Journey Code: "<<BLUE<<temp->object->jour->object->journeyCode<<RESET<<endl;
            cout<<"Departure at: "<<GREEN<<temp->object->dep<<RESET<<" Arrival at: "<<GREEN<<temp->object->dep<<RESET<<endl;
            if(temp->object->wait!=0){
                cout<<"Transit Time: "<<temp->object->wait<<endl;
            }
            temp=temp->next;
        }
        if(ans1->object->stops!=0){
            cout<<"Number of stop overs: "<<GREEN<<ans1->object->stops<<RESET<<endl;
        }
        ans1=ans1->next;
    }

}

#endif
