#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

listOfObjects<listOfObjects<TrainInfoPerStation*>*>* final=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0)));
int** finalintpath=new int*[20];

listOfObjects<listOfObjects<TrainInfoPerStation*>*>* combined_list(listOfObjects<TrainInfoPerStation*>* a, listOfObjects<listOfObjects<TrainInfoPerStation*>*>* b){
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* final_list=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(a);
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* d=final_list;
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* c=b;
    int i=0;
    while(a!=nullptr){
        b=c;
        while(b!=nullptr){
            i++;
            listOfObjects<TrainInfoPerStation*>* newlist=new listOfObjects<TrainInfoPerStation*>(a->object);
            newlist->next=b->object;
            if(i==1){
                final_list->object=newlist;
            }
            else{
                final_list->next=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(newlist);
                final_list=final_list->next;
            }
            b=b->next;
        }
        a=a->next;
    }
    final_list=d;
    return final_list;
}

listOfObjects<TrainInfoPerStation*>* getlistoftrains(int srcindex, int destindex, StationAdjacencyList adjacency[]){
    listOfObjects<StationConnectionInfo*>* c=adjacency[srcindex].toStations;
    listOfObjects<StationConnectionInfo*>* d=c;
    listOfObjects<TrainInfoPerStation*>* a=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
    while(c!=nullptr){
        if(c->object->adjacentStnIndex==destindex){
            a=c->object->trains;
        }
        c=c->next;
    }
    return a;
}

bool check_time(listOfObjects<TrainInfoPerStation*>* a, int maxTransitTime, int index1, int index2, StationAdjacencyList adjacency[], Dictionary<int> stnNameToIndex ){
    string day_array[7];
    day_array[0]="SUN";
    day_array[1]="MON";
    day_array[2]="TUE";
    day_array[3]="WED";
    day_array[4]="THU";
    day_array[5]="FRI";
    day_array[6]="SAT";

    listOfObjects<TrainInfoPerStation*>* r=a;
    int dep_time=0,day=0,arr_time=0;
    int count=0;
    for(int i=0;i<7;i++){
        if(a->object->daysOfWeek[i])count++;
    }
    int array[count];
    bool arr[count];
    for(int i=0; i<count;i++){
        arr[i]=true;
    }
    int j=0;
    for(int i=0;i<7;i++){
        if(a->object->daysOfWeek[i]){
            array[j]=i;
            j=j+1;
        }
    }
    if(index2==1){
        int u=0;
        while(u<count){
            day=array[u];
            dep_time=a->object->depTime;
                listOfObjects<StationConnectionInfo*>* b=adjacency[finalintpath[index1][1]].fromStations;
                while(b!=nullptr){
                    listOfObjects<TrainInfoPerStation*>* c=b->object->trains;
                    while(c!=nullptr){
                        if(c->object->journeyCode==a->object->journeyCode){
                            arr_time=c->object->arrTime;
                            // cout<<arr_time<<" ";
                            break;
                        }
                        c=c->next;
                    }
                    b=b->next;
                }
                cout<<endl<<"Journey:"<<endl;
                if(arr_time<dep_time)cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][0])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][1])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[(day+1)%7]<<" ,"<<arr_time<<RESET<<endl;
                else cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][0])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][1])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[day]<<" ,"<<arr_time<<RESET<<endl;
                a=a->next;
            u++;
            a=r;
            cout<<endl;
        }
        return true;
    }  
    int k=0;
    while(k<count){
        // cout<<k<<":"<<endl;
        day=array[k];
        // cout<<day<<":"<<endl;
        dep_time=a->object->depTime;
        for (int j=1; j<index2; j++){
            listOfObjects<StationConnectionInfo*>* b=adjacency[finalintpath[index1][j]].fromStations;
            while(b!=nullptr){
                listOfObjects<TrainInfoPerStation*>* c=b->object->trains;
                while(c!=nullptr){
                    if(c->object->journeyCode==a->object->journeyCode){
                        arr_time=c->object->arrTime;
                        // cout<<arr_time<<" ";
                        if(arr_time<dep_time)day=(day+1)%7;
                        break;
                    }
                    c=c->next;
                }
                b=b->next;
            }
            if(a->object->journeyCode==a->next->object->journeyCode){
                dep_time=a->next->object->depTime;
                // cout<<1<<" :"<<dep_time<<" ";
                if(dep_time<arr_time){
                    day=(day+1)%7;
                }
            }
            else{
                dep_time=a->next->object->depTime;
                // cout<<2<<" :"<<dep_time<<" ";
                int day1=day;
                if(a->next->object->daysOfWeek[day] && dep_time>=arr_time){
                    // cout<<3<<" : "<<maxTransitTime;
                    if((dep_time-arr_time)/100>maxTransitTime)arr[k]=false;
                }
                else{
                    day1=(day+1)%7;
                    while(!a->next->object->daysOfWeek[day1]){
                        day1=(day1+1)%7;
                    }  
                    if(day<day1){
                        if((2400-arr_time+(day1-day-1)*2400+dep_time)/100>maxTransitTime)arr[k]=false;
                        else{
                            day=day1;
                        }
                    }
                    else if(day1<day){
                        if((2400-arr_time+(6-day+day1)*2400+dep_time)/100>maxTransitTime)arr[k]=false;
                        else{
                            day=day1;
                        }
                    }
                    else if(day==day1){
                        if((2400-arr_time+6*2400+dep_time)/100>maxTransitTime)arr[k]=false;
                    }
                    // cout<<4<<" :"<<day<<" "<<day1;
                }           
            }
            a=a->next;
            // cout<<endl<<"finish"<<endl;
        }
        a=r;
        k++;
    }
    int found=0;
    int t=0;
    for(int i=0; i<count;i++){
        int transit_time=0;
        if(arr[i]){
            found++;
            day=array[i];
            dep_time=a->object->depTime;
            for (int l=1; l<index2; l++){
                listOfObjects<StationConnectionInfo*>* b=adjacency[finalintpath[index1][l]].fromStations;
                while(b!=nullptr){
                    listOfObjects<TrainInfoPerStation*>* c=b->object->trains;
                    while(c!=nullptr){
                        if(c->object->journeyCode==a->object->journeyCode){
                            arr_time=c->object->arrTime;
                            // cout<<arr_time<<" ";
                            if(transit_time==0){
                                if(arr_time<=dep_time)cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l-1])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[(day+1)%7]<<" ,"<<arr_time<<RESET<<endl;
                                else cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l-1])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[day]<<" ,"<<arr_time<<RESET<<endl;
                            }
                            else{
                                if(arr_time<=dep_time)cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l-1])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[(day+1)%7]<<" ,"<<arr_time<<" "<<"   transit time:"<<" "<<transit_time<<RESET<<endl;
                                else cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l-1])<<" "<<RESET<<GREEN<<"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][l])<<" "<<endl<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"   "<<"arrives:"<<" "<<day_array[day]<<" ,"<<arr_time<<" "<<"   transit time:"<<" "<<transit_time<<RESET<<endl;
                            }
                            if(arr_time<dep_time)day=(day+1)%7;
                            break;
                        }
                        c=c->next;
                    }
                    b=b->next;
                }
                transit_time=0;
                if(a->object->journeyCode==a->next->object->journeyCode){
                    dep_time=a->next->object->depTime;
                    // cout<<1<<" :"<<dep_time<<" ";
                     if(dep_time<arr_time){
                        day=(day+1)%7;
                    }   
                }
                else{
                    dep_time=a->next->object->depTime;
                    // cout<<2<<" :"<<dep_time<<" ";
                    int day1=day;
                    if(a->next->object->daysOfWeek[day] && dep_time>=arr_time){
                        // cout<<3<<" : "<<maxTransitTime;
                        transit_time=dep_time-arr_time;
                        int a=dep_time%100;
                        int b=arr_time%100;
                        if(a<b) transit_time=(dep_time/100-arr_time/100-1)*100+(60+a-b);
                        if(transit_time/60>maxTransitTime)arr[k]=false;
                    }
                    else{
                        day1=(day+1)%7;
                        while(!a->next->object->daysOfWeek[day1]){
                            day1=(day1+1)%7;
                        }  
                        if(day<day1){
                            transit_time=2400-arr_time+(day1-day-1)*2400+dep_time;
                            int a,b,num;
                            if(arr_time%100!=0){
                                a=24-arr_time/100-1;
                                b=60-arr_time%100;
                                num=a*100+b;
                                if(b+dep_time%100>60)transit_time=(day1-day-1)*2400+(dep_time/100+num/100+1)*100+(b+dep_time%100-60);
                            }
                            if(transit_time/60>maxTransitTime)arr[k]=false;
                            else{
                                day=day1;
                            }
                        }
                        else if(day1<day){
                            transit_time=2400-arr_time+(6-day+day1)*2400+dep_time;
                            int a,b,num;
                            if(arr_time%100!=0){
                                a=24-arr_time/100-1;
                                b=60-arr_time%100;
                                num=a*100+b;
                                if(b+dep_time%100>60)transit_time=(6+day1-day)*2400+(dep_time/100+num/100+1)*100+(b+dep_time%100-60);
                            }
                            if(transit_time/60>maxTransitTime)arr[k]=false;
                            else{
                                day=day1;
                            }
                        }
                        else if(day==day1){
                            transit_time=2400-arr_time+6*2400+dep_time;
                            int a,b,num;
                            if(arr_time%100!=0){
                                a=24-arr_time/100-1;
                                b=60-arr_time%100;
                                num=a*100+b;
                                if(b+dep_time%100>60)transit_time=6*2400+(dep_time/100+num/100+1)*100+(b+dep_time%100-60);
                            }
                            if(transit_time/60>maxTransitTime)arr[k]=false;
                        }
                    }           
                }
                a=a->next;
                t=l;
            }
            listOfObjects<StationConnectionInfo*>* b=adjacency[finalintpath[index1][t+1]].fromStations;
                while(b!=nullptr){
                    listOfObjects<TrainInfoPerStation*>* c=b->object->trains;
                    while(c!=nullptr){
                        if(c->object->journeyCode==a->object->journeyCode){
                            arr_time=c->object->arrTime;
                            break;
                        }
                        c=c->next;
                    }
                    b=b->next;
                }
                if(transit_time==0){
                    if(arr_time<=dep_time)cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t])<<" "<<RESET<<GREEN"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t+1])<<" "<<endl<<RESET<<RED<<"      departs:"<<" ,"<<day_array[day]<<" "<<dep_time<<"   "<<"arrives:"<<" "<<day_array[(day+1)%7]<<" ,"<<arr_time<<RESET<<endl;
                    else cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t])<<" "<<RESET<<GREEN"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t+1])<<" "<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<" "<<"arrives:"<<" ,"<<day_array[day]<<" "<<arr_time<<RESET<<endl;
                }
                else{
                    if(arr_time<=dep_time)cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t])<<" "<<RESET<<GREEN"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t+1])<<" "<<endl<<RESET<<RED<<"      departs:"<<" ,"<<day_array[day]<<" "<<dep_time<<"   "<<"arrives:"<<" "<<day_array[(day+1)%7]<<" ,"<<arr_time<<" "<<"   transit time:"<<" "<<transit_time<<RESET<<endl;
                    else cout<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t])<<" "<<RESET<<GREEN"journeycode:"<<" "<<a->object->journeyCode<<" "<<RESET<<BLUE<<stnNameToIndex.getKeyAtIndex(finalintpath[index1][t+1])<<" "<<RESET<<RED<<"      departs:"<<" "<<day_array[day]<<" ,"<<dep_time<<"  "<<"arrives:"<<" "<<day_array[day]<<" ,"<<arr_time<<" "<<"   transit time:"<<" "<<transit_time<<RESET<<endl;
                }
            a=r;
            cout<<endl<<endl;
        }   
    }
    if(found>0) return true;  
    return false;
 }


bool valid(listOfObjects<TrainInfoPerStation*>* a,int maxStopOvers, int maxTransitTime,int index1,int index2, StationAdjacencyList adjacency[],Dictionary<int> stnNameToIndex){
    listOfObjects<TrainInfoPerStation*>* b=a;
    int no_of_changes=0;
    // if(a->next==nullptr)return true;
    while(b!=nullptr && b->next!=nullptr){
        // if((b->next->object->arrTime-b->object->depTime)>maxTransitTime)return false;
        if(b->object->journeyCode!=b->next->object->journeyCode)no_of_changes++;
        b=b->next;
    }
    if(no_of_changes>maxStopOvers)return false;
    if(!check_time(a,maxTransitTime,index1,index2,adjacency,stnNameToIndex))return false;
    // cout<<"_________________________________________";
    return true;
}

void printAllPathsUtil(string srcStnName, string destStnName, bool visited[],int* intpath, int& intpath_index, Dictionary<int> stnNameToIndex,StationAdjacencyList adjacency[], listOfObjects<TrainInfoPerStation*>* *path, listOfObjects<listOfObjects<TrainInfoPerStation*>*>* final, int& count, int& recursion_level, int& index){
    // Mark the current node and store it in path[]
    recursion_level++;
    int src_index=stnNameToIndex.hashValue(srcStnName);
    int dest_index=stnNameToIndex.hashValue(destStnName);
    visited[src_index] = true;
    intpath[intpath_index] = src_index;
    intpath_index++;
 
    // If current vertex is same as destination, then print
    // current path[]
    if (src_index == dest_index) {
        for (int i = 0; i < intpath_index; i++){
            finalintpath[index][i]=intpath[i];
        }
        index++;
    }
    else {
        listOfObjects<StationConnectionInfo*>* connection_info=adjacency[src_index].toStations;
        while (connection_info!=nullptr){
            if(!visited[connection_info->object->adjacentStnIndex]){
                printAllPathsUtil(stnNameToIndex.getKeyAtIndex(connection_info->object->adjacentStnIndex),destStnName, visited,intpath, intpath_index, stnNameToIndex, adjacency, path, final, count, recursion_level, index);
            }
            connection_info=connection_info->next;
        }
    }

    intpath_index--;
    recursion_level--;
    visited[src_index] = false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
    bool* visited = new bool[DICT_SIZE];
    for(int i=0;i<DICT_SIZE;i++){
        visited[i]=false;
    }
    int* intpath = new int[20];
    int intpath_index = 0;
    int count=0;
    for(int i=0;i<20;i++){
         finalintpath[i]=new int[20];
    }
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            finalintpath[i][j]=0;
        }
    }
    int recursion_level=0; 
    int index=0;
    listOfObjects<TrainInfoPerStation*>* *path=new listOfObjects<TrainInfoPerStation*>*[DICT_SIZE];
    printAllPathsUtil(srcStnName, destStnName, visited, intpath, intpath_index,stnNameToIndex, adjacency, path, final,count, recursion_level,index);
    int valid_paths=0;
    for(int i=0; i<20; i++){
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* finallist=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0)));
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* y=finallist;
        if(finalintpath[i][0]==0)break;
        int lastindex=0;
        for (int j=0; j<20; j++){
            if(finalintpath[i][j]==0){
                lastindex=j-1;
                break;
            }
        }
        listOfObjects<TrainInfoPerStation*>* a=getlistoftrains(finalintpath[i][lastindex-1],finalintpath[i][lastindex],adjacency);
        // printStationInfo(a);
        listOfObjects<TrainInfoPerStation*>* c=a;
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* b=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(a->object));
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* d=b;
        a=a->next;
        while(a!=nullptr){
            b->next=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(a->object));
            a=a->next;
            b=b->next;
        }
        a=c;
        b=d;
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* totallist=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0)));
        totallist=b;
        if(lastindex>=2){
            for(int k=lastindex-1; k>=1; k--){
                a=getlistoftrains(finalintpath[i][k-1],finalintpath[i][k],adjacency);
                totallist=combined_list(a,totallist);
            }
        }
        while(totallist!=nullptr){
            if(valid(totallist->object, maxStopOvers, maxTransitTime,i,lastindex,adjacency,stnNameToIndex)){
                if(valid_paths==0)finallist->object=totallist->object;
                else{
                    finallist->next=new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(totallist->object);
                    finallist=finallist->next;
                }
                // printStationInfo(totallist->object);
            }
            valid_paths++;
            totallist=totallist->next;
        }
    }
}

#endif