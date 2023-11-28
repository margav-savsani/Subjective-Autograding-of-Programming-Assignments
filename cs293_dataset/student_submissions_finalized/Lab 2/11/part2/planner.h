#include <string.h>
#include "Plannerdictionary.cpp"
#ifndef PLANNER_H
#define PLANNER_H


class Planner {
  private :
      Dictionary plan ; 
  public: 
   Journey* get(char start[])  { return plan.get(start) ; }

   void add(char start[],float start_time ,char end[] , float end_time) {
      Journey* temp = new Journey ; 
      strcpy(temp->start,start) ; 
      strcpy(temp->end,end) ; 
      temp->start_time = start_time ; 
      temp->end_time = end_time ; 
      plan.put(temp) ; 
   }
 
  void query_journey(char station[] , char dest[] ,float start_time )  {
    Journey* head = get(station) ;
    if (head == NULL )  cout<<"ERROR : No Such Station Exists"<<endl ; 
    else  {
        int min_time = -1; 
        Journey* soonest_journey ;  
        Journey* intermediate = nullptr ;

        do { 
          if (head->start_time  >= start_time) { 
            if ( strcmp(head->end,dest) ==0 )  {
                 if( min_time == -1 || head->start_time < min_time ) { 
                    min_time = head->start_time ; 
                    soonest_journey = head ; 
                }
            }   
            else {
               Journey* end_head = get(head->end);
               if (end_head != NULL ){ 
                   do { 
                     if (strcmp(end_head->end,dest) == 0 ) intermediate = end_head ;  
                     end_head = end_head->next ;   
                   } while(end_head != nullptr );

                   if (intermediate != nullptr) { 
                     if( min_time == -1 || head->start_time < min_time ) { 
                       min_time = head->start_time ; 
                       soonest_journey = head ; 
                     }
                   }
                } 
             }
           }
           head = head->next ;   
        }while(head != nullptr );
        
        if ( min_time == -1) cout<<"ERROR : No Journey Exists between two stations after given time"<<endl ; 
        else if (intermediate == nullptr ) { 
            cout<<soonest_journey->start_time<<endl ; 
        }
        else { 
            cout<< soonest_journey->start_time <<" "<< intermediate->start << " " << intermediate->start_time <<endl ; 
        }
     }
    }
 
  void query_station(char station[] , float time) {
    Journey* head = get(station) ;
    if (head == NULL )  cout<<"ERROR : No Station Exists"<<endl ; 
    else  {
        bool err = true ;  
        do { 
           if ( head->start_time >= time ) { 
              cout<<head->start_time<<" "<<(head->end)<<endl ;
              err = false  ; 
           }
              head = head->next ;   
        }while(head != nullptr );  
        if (err) cout<<"ERROR : No Journey Exists"<<endl ; 
     } 
   }


};

#endif