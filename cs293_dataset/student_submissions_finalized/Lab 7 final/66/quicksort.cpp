#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif
#include<vector>
#include <cstdlib>


// function to compare two TrainInfoPerStation with daysOFWeek and depTime as things to be compared.
int compare(TrainInfoPerStation *t1,TrainInfoPerStation *t2){
    
    for(int i=0;i<7;i++){
       if(t1->daysOfWeek[i]==true && t2->daysOfWeek[i]==true){
       
           if(t1->depTime<t2->depTime){ return 0; }
           else if(t1->depTime==t2->depTime){ return 2; }
           else { return 1; }
       }
       else if(t1->daysOfWeek[i]==true ) {return 0;}
       else if(t2->daysOfWeek[i]==true){return 1;}
       
    }
}

//function for finding pivot with value k given.
listOfObjects<TrainInfoPerStation *>*pivot(vector<listOfObjects<TrainInfoPerStation *> *> a,int k,listOfObjects<TrainInfoPerStation *> *f1){
   
    int r1 = rand()%(a.size()),h; 
    f1 = a[r1];
   
    for(h=0;h<k;h++){ 
    
        if(f1->next!=nullptr) f1=f1->next;
        else break;
    }
    
    f1 = a[r1];
    int r2 = rand()%(h+1);
   
    for(int i=1;i<=r2;i++){f1->next;}
    return f1;
 }

int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end,listOfObjects<TrainInfoPerStation *> *f,listOfObjects<TrainInfoPerStation *> *p,listOfObjects<TrainInfoPerStation *> *b,vector<listOfObjects<TrainInfoPerStation *>*> a,int K){
    
    f = stnInfoList;b = stnInfoList;      // variables to store listOfObjects pointer containing starting train and ending train given for the partition.
    
    listOfObjects<TrainInfoPerStation *> *f1;
    
    for(int i=1;i<=start;i++){  f = f->next; }   // to find listOfObjects pointer having starting train given for partition
    
    for(int i=1;i<=end;i++){  b = b->next; }     // to find listOfObjects pointer having ending train given for partition
     
    f1 = f;
     
    int x=1,n = (end-start+1)/K; if((end-start+1)/K - n !=0) {n++;}
    
    // dividing listOfObjects into n/k groups and adding starting listOfObject in each group to vector       
    for(int i=start;i<=end;i++){
     
        if(x==1) a.push_back(f1);
        f1 = f1->next; if(x==n) {x=1;} else x++;
    }
    
    // passing vecctor and vvalue k to find pivot 
    p = pivot(a,K,f1);
     
    a.clear(); 
    int i=start,j=end;
    
    // while loop for swapping elements and then returning a value.
    while(true){
    
        while((compare(f->object,p->object)==0||compare(f->object,p->object)==2)&&i<end){ i++;f = f->next; }
        while(compare(b->object,p->object)==1&&j>start){ j--; b=b->prev;}
       
        if(i<j){TrainInfoPerStation *s = f->object;f->object=b->object;b->object=s;}
        else if(i==j&&j==end){ TrainInfoPerStation *s = f->object;f->object = p->object;p->object = s;return j; }
        else if(i==j&&j==start){TrainInfoPerStation *s = f->object;f->object = p->object;p->object = s;return j;}
        else {return j;}  
    }
     
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;
  
    static listOfObjects<TrainInfoPerStation *> *f,*b,*p;    
  
    static vector<listOfObjects<TrainInfoPerStation *>*> a;
  
    if(start != end){
        int i = partition(stnInfoList, start, end,f,b,p,a,K);
        
        if(i==end){ QuicksortSimple(stnInfoList, start,i-1 ); }
        else if(i==start){  QuicksortSimple(stnInfoList, i+1,end ); }
        else{
            QuicksortSimple(stnInfoList, start,i );
            QuicksortSimple(stnInfoList, i+1, end);
        }
    }
    
    if (recursionLevel == 0) {
      delete f;delete b;delete p;
    }
      
    recursionLevel--;
    return;
}

#endif
