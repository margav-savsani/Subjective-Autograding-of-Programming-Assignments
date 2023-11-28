struct Journey {
  char start[32]  ; 
  char end[32]  ; 
  float start_time ;
  float end_time ;
  Journey* next = nullptr ; 
};


class Queue {
     private : 
     Journey* head ; 
     public : 
       Queue() { 
        head = nullptr ; 
       }
       void add(Journey* j) {
             if ( head == nullptr )  head = j ;
             else { 
                 j->next = head ; 
                 head = j ; 
             }
       } 
       Journey* getjourneys() { 
           return head  ; 
       }
}; 

struct Station {
    char key[32] ; 
    int n = 0 ;  
    Queue journeys ;   
};

