#include<sstream>
#include"dictionary.cpp"


#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
  char stName[32] = "\0";
};

struct Journey {
  // define suitable fields here
  
  Station from;
  Station to;
  float startTime;
  float finishTime;
  char * key = from.stName;
  int isOccupied = 0;
};

struct Query{
  // define suitable fields here
  char qstring[64];
};

class Planner {
  // define suitable fields here
  private: 
    Dictionary<Journey> plan = Dictionary<Journey>();
    

  public:
    bool QueryHandler(Query query){
      
      stringstream ss;
      ss << query.qstring;

      char option[32];
      ss >> option;


      if(strcmp(option, "ADD") == 0){
        char station1[32];
        char station2[32];
        float startTime;
        float finishTime;

        ss >> station1;
        ss >> startTime;
        ss >> station2;
        ss >> finishTime;

        Journey newJourney;

        strcpy(newJourney.from.stName,station1);
        strcpy(newJourney.to.stName,station2);
        newJourney.startTime = startTime;
        newJourney.finishTime = finishTime;

        //Add the new Journey to our dictionary
        plan.put(newJourney);
        
        return true;
        



          
      }
      else if(strcmp(option, "QUERY_STATION") == 0){

        char station1[32];
        float startTime = 0;

        ss >> station1;
        ss >> startTime;

        // get the first journey of the corresponding station

        Journey * a = plan.get(station1);
        Journey * b[64];

        int i = 0;
        
        int added = 0;

          //search for subseuent elements
          for(;a!= NULL && !strcmp(a->key, station1); i++){
            if (a != NULL){
              //print out the corresponding journeys from that station
              if (a->startTime >= startTime){
                added++;
                std::cout << (a->startTime) << " " << (a->to.stName) << endl;
              }
              b[i] = a;
              a->isOccupied = -1;
              a = plan.get(station1);
            }
          }

          // revert back to occupied elements from tombstones
          for (int j = 0; j < i; j++){
            b[j]->isOccupied = 1;
          }
          
         if (added == 0) {
          cout << "ERROR" << endl;
        }

        return true;


      }
      else if(strcmp(option, "QUERY_JOURNEY") == 0){
        char station1[32];
        char station2[32];
        float startTime;

        ss>>station1;
        ss>>startTime;
        ss>>station2;

        Journey * a = plan.get(station1);
        Journey * b[64];

        int i = 0;
        //set value of min to an arbitrary large value
        int min = 10000000;
        int steps = 0;
        Journey * minptr1;
        Journey * minptr2;



        
          for(; a!=NULL && !strcmp(a->key, station1); i++){
            if (a != NULL){
              if (a->startTime >= startTime){
                //search for an intermediate journey
                if(strcmp(station2,a->to.stName)){
                  int k = 0;
                  char newStation1[32];
                  strcpy(newStation1, a->to.stName);

                  Journey * c = plan.get(newStation1);
                  Journey * d[64];

                  for(;c !=NULL && !strcmp(c->key, newStation1);k++){
                    if(c!=NULL){
                      if(c->startTime >= a->finishTime){
                        //checking the last station of intermediate journey
                        if(!strcmp(station2, c->to.stName)){
                       // cout << a->startTime << " " << c->key<< " " << c->startTime << endl;
                        //found++;
                          if(a->startTime < min){
                            minptr1 = a;
                            minptr2 = c;
                            steps = 2;
                          }
                        }
                        
                      }
                      
                      //convert the element to a tombstone to check for the next element
                      d[k] = c;
                      c->isOccupied = -1;
                      c = plan.get(newStation1);
                    }

                    else {
                      break;
                    }
                  }

                  // revert back to occupied elements from tombstones
                  for (int l = 0; l < k; l++){
                    d[l]->isOccupied = 1;
                  }
                  
                } else {
                  if (a->startTime < min){
                    //cout << a->startTime << endl;
                    //found++;
                    minptr1 = a;
                    steps = 1;
                  }

                }
              }
            }



            b[i] = a;
            a->isOccupied = -1;
            a = plan.get(station1);
          }

          // revert back to occupied elements from tombstones
          for (int j = 0; j < i; j++){
            b[j]->isOccupied = 1;
          }
          
        if (steps == 1){
          cout << minptr1->startTime << endl;
        }

        if (steps == 2){
          cout << minptr1->startTime << " " << minptr2->key << " " << minptr2->startTime << endl ;
        }

        if (steps == 0){
          cout << "ERROR" << endl;
        }

        return true;




      }
      else if(strcmp(option, "EXIT") == 0){
        return false;
      }

      return true;

    }

  

};

#endif