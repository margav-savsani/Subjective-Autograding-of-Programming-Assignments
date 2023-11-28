#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
class Stnconninfo {
public:
  int StnIndex;
  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t;
  listOfObjects<TrainInfoPerStation *> *train;

  Stnconninfo(int index = -1) {
    StnIndex = index;
    train = nullptr;
    t = nullptr;
  } 
};   

int getday(TrainInfoPerStation *t){
    for(int i=0;i<7;i++)
      if(t->daysOfWeek[i]) {return i;break;}
   }   

listOfObjects<TrainInfoPerStation *>* modify(listOfObjects<TrainInfoPerStation *> * t){
  TrainInfoPerStation* T2=new TrainInfoPerStation(0,0,0,0); 
  listOfObjects<TrainInfoPerStation *>* T1=new listOfObjects<TrainInfoPerStation *>(T2);
  listOfObjects<TrainInfoPerStation *> * t1=t;
  while(t1!=NULL){
     for(int i=0;i<7;i++)
       {
         if(t1->object->daysOfWeek[i])
          {
             TrainInfoPerStation* X=new TrainInfoPerStation(t1->object->journeyCode,t1->object->stopSeq,t1->object->arrTime,t1->object	->depTime);
             X->daysOfWeek[i]=true;
             listOfObjects<TrainInfoPerStation *>* T3=T1;
             while(T3->next!=NULL)
                T3=T3->next;
             T3->next=new listOfObjects<TrainInfoPerStation *>(X);
           }
         }
        t1=t1->next; 
      }  
     return T1->next;
}              
                       
     
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
 
  cout<<"hiii"<<endl;
  int src = stnNameToIndex.get(srcStnName)->value;
  int dstn = stnNameToIndex.get(destStnName)->value; 
  
  TrainInfoPerStation* T=new TrainInfoPerStation(0,0,0,0); 
  listOfObjects<TrainInfoPerStation *>* Journey=new listOfObjects<TrainInfoPerStation *>(T);
  
  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* J1=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(Journey);  
  Stnconninfo* S=new Stnconninfo(-10); 
  listOfObjects<Stnconninfo *>* Q=new listOfObjects<Stnconninfo *>(S);
  listOfObjects<StationConnectionInfo *>* Que;     
  Que = adjacency[src].toStations;
  while(Que!=NULL){
       
   
     Stnconninfo* S1=new Stnconninfo(-10);
     S1->StnIndex=Que->object->adjacentStnIndex;
     S1->train=modify(Que->object->trains);
     listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t1=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(Que->object->trains);
     listOfObjects<TrainInfoPerStation *> *train1=S1->train;
     while(train1!=NULL){
         listOfObjects<TrainInfoPerStation *> *train2=new listOfObjects<TrainInfoPerStation *>(train1->object);
         train2->next=NULL;
         listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t2=t1;
         while(t2->next!=NULL)
            t2=t2->next;
         t2->next=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(train2);
         train1=train1->next;
        }
           
     S1->t=t1->next;

     listOfObjects<Stnconninfo *>* Q1=Q;
     while(Q1->next!=NULL)
        Q1=Q1->next;

     Q1->next=new listOfObjects<Stnconninfo *>(S1);   
     Que=Que->next;
    }       
  Q=Q->next; 
     
  int c=0;
  while(Q!=NULL){
    int b=1; 
    if(c==0){
       c++;
       b=0;
        }
  
  
     Stnconninfo* S=new Stnconninfo(-10);
     listOfObjects<Stnconninfo *>* Qnew=new listOfObjects<Stnconninfo *>(S);  
     while(Q!=NULL){    
                                                                                      
       if(Q->object->StnIndex==dstn)
        {    
          if(b==0){
             listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t8=Q->object->t;
             while(t8!=NULL){
listOfObjects<listOfObjects<TrainInfoPerStation *>*>* J = J1;
              while(J->next!=NULL)
                 J = J->next;
              J->next = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(t8->object);  
        t8=t8->next;}Q=Q->next;continue;
        }
          listOfObjects<TrainInfoPerStation *> *train1=Q->object->train;
          while(train1!=NULL){
                    listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t8=Q->object->t;
   
     while(t8!=NULL){
       int a=1;
       listOfObjects<TrainInfoPerStation *>*t7= t8->object;
         TrainInfoPerStation* T=new TrainInfoPerStation(0,0,0,0); 
       listOfObjects<TrainInfoPerStation *>*t10=new listOfObjects<TrainInfoPerStation *>(T);
        listOfObjects<TrainInfoPerStation *>*t9;
        while(t7!=NULL){
                  listOfObjects<TrainInfoPerStation *>*t11=t10;
                  while(t11->next!=NULL) 
                     t11=t11->next;
                     
                 t11->next=new listOfObjects<TrainInfoPerStation *>(t7->object);
                 t9=t11->next;	
                 t7=t7->next;
                 a=a+1; 
                    }
          unsigned short Seq;                   
          int jc=t9->object->journeyCode;  
          int dayi;     
          int at;
          int dt;
            
            listOfObjects<StationConnectionInfo *> *stns = adjacency[Q->object->StnIndex].fromStations;  
            while(stns!=NULL){
              listOfObjects<TrainInfoPerStation *>* s = stns->object->trains;
              while(s!=NULL){
               if(s->object->journeyCode==jc) 
                {
                  for(int i=getday(t9->object);i<7;i++)
                   {
                     if(s->object->daysOfWeek[i]) {dayi=i;break;}
                     if(i==6) i=0;
                    } 
                  Seq= s->object->stopSeq; 
                  at = s->object->arrTime;
                  dt = s->object->depTime;
                  break;
                 }
                s=s->next; 
              }   
             stns=stns->next;
            }  
          if(a>maxStopOvers) break; 
              if(dayi==getday(train1->object)){ 
                  if(at<=train1->object->depTime){ 
                     if(train1->object->depTime - at > maxTransitTime*100) {t8=t8->next;continue;}}
                  else{
                    if(6*24*100+at- train1->object->depTime > maxTransitTime*100) {t8=t8->next;continue;}}
                }
              else{
                 if(at <= train1->object->depTime){
                    if(((getday(train1->object)-dayi)%7)*24*100+train1->object->depTime-at > maxTransitTime*100) {t8=t8->next;continue;}} 
                  else{
                    if(((getday(train1->object)-dayi)%7)*24*100-at+train1->object->depTime > maxTransitTime*100) {t8=t8->next;continue;}}
                 }

              TrainInfoPerStation* T1=new TrainInfoPerStation(jc,Seq,at,dt);
              T1->daysOfWeek[dayi]=true;
              t9->next=new listOfObjects<TrainInfoPerStation *>(T1);                                                
              t9->next->next=new listOfObjects<TrainInfoPerStation *>(train1->object); 
             listOfObjects<listOfObjects<TrainInfoPerStation *>*>* J = J1;
              while(J->next!=NULL)
                 J = J->next;
              J->next = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(t10->next);  
        t8=t8->next;
       	}   
       	    if(train1->next==NULL) break;                         
              train1=train1->next;
              }
              Q = Q->next;   
             continue;
           }
           
           
           
           
           	

   listOfObjects<listOfObjects<TrainInfoPerStation *>*>* tnew1=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(Q->object->train);
 
           if(b==0){b=1;
             listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t8=Q->object->t;
             while(t8!=NULL){
listOfObjects<listOfObjects<TrainInfoPerStation *>*>* tnew = tnew1;
              while(tnew->next!=NULL)
                 tnew = tnew->next;
              tnew->next = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(t8->object);  
        t8=t8->next;}
        }
 
   else{
          listOfObjects<TrainInfoPerStation *> *train1=Q->object->train;
          while(train1!=NULL){
                    listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t8=Q->object->t;
              listOfObjects<listOfObjects<TrainInfoPerStation *>*>* t0=Q->object->t;
   
     while(t8!=NULL){
       int a=1;
       listOfObjects<TrainInfoPerStation *>*t7= t8->object;
         TrainInfoPerStation* T=new TrainInfoPerStation(0,0,0,0); 
       listOfObjects<TrainInfoPerStation *>*t10=new listOfObjects<TrainInfoPerStation *>(T);
        listOfObjects<TrainInfoPerStation *>*t9;
        while(t7!=NULL){
                  listOfObjects<TrainInfoPerStation *>*t11=t10;
                  while(t11->next!=NULL) 
                     t11=t11->next;
                 t11->next=new listOfObjects<TrainInfoPerStation *>(t7->object);
                 t9=t11->next;	
                 t7=t7->next;
                 a=a+1; 
                    }

          unsigned short Seq;                   
          int jc=t9->object->journeyCode; 
          int dayi;     
          int at;
          int dt;
            
            listOfObjects<StationConnectionInfo *> *stns = adjacency[Q->object->StnIndex].fromStations;  
            while(stns!=NULL){
              listOfObjects<TrainInfoPerStation *>* s = stns->object->trains;
              while(s!=NULL){
               if(s->object->journeyCode==jc) 
                {
                  for(int i=getday(t9->object);i<7;i++)
                   {
                     if(s->object->daysOfWeek[i]) {dayi=i;break;}
                     if(i==6) i=0;
                    } 
                  Seq= s->object->stopSeq; 
                  at = s->object->arrTime;
                  dt = s->object->depTime;
                  break;
                 }
                s=s->next; 
              }   
             stns=stns->next;
            }   
 
          if(a>maxStopOvers) break; 
              if(getday(t9->object)==getday(train1->object)){ 
                  if(t9->object->arrTime<=train1->object->depTime){ 
                     if(train1->object->depTime-t9->object->arrTime>maxTransitTime*100) {t8=t8->next;continue;}}
                  else{
                    if(6*24*100+t9->object->arrTime-train1->object->depTime>maxTransitTime*100) {t8=t8->next;continue;}}
                }
              else{
                 if(t9->object->arrTime<=train1->object->depTime){
                     if((getday(t9->object)-getday(train1->object)%7)*24*100+train1->object->depTime-t9->object->arrTime>maxTransitTime*100) {t8=t8->next;continue;}} 
                  else{
                    if((getday(t9->object)-getday(train1->object)%7)*24*100-t9->object->arrTime+train1->object->depTime>maxTransitTime*100) {t8=t8->next;continue;}}
                 }
              TrainInfoPerStation* T1=new TrainInfoPerStation(jc,Seq,at,dt);
              T1->daysOfWeek[dayi]=true;                     
              t9->next=new listOfObjects<TrainInfoPerStation *>(T1);                                                
              t9->next->next=new listOfObjects<TrainInfoPerStation *>(train1->object);                          
             listOfObjects<listOfObjects<TrainInfoPerStation *>*>* tnew = tnew1;
              while(tnew->next!=NULL)
                 tnew = tnew->next;
              tnew->next = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(t10->next);  
        t8=t8->next;
       	}   
       	    if(train1->next==NULL) break;                         
              train1=train1->next;
              }
         }
  
 
       listOfObjects<StationConnectionInfo *>* Q1;   
       Q1 = adjacency[Q->object->StnIndex].toStations;             
      listOfObjects<StationConnectionInfo *>* Que = Q1;      
      while(Que!=NULL){
           Stnconninfo* S=new Stnconninfo(-5);
           S->StnIndex=Que->object->adjacentStnIndex;
           S->train=modify(Que->object->trains);
           S->t=tnew1->next;
           listOfObjects<Stnconninfo *>* Q2=Qnew;
           while(Q2->next!=NULL)
             Q2=Q2->next;
           Q2->next=new listOfObjects<Stnconninfo *>(S);   
           Que=Que->next;
          }      
       Q=Q->next;
     }  
   Q = Qnew->next; 
  }  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* J2=J1->next;
  while(J2!=NULL){
     if(J2->object!=NULL)cout<<"--JOURNEY--"<<endl;
     printStationInfo(J2->object);     
     J2=J2->next;
    }
  return;   
}

#endif
