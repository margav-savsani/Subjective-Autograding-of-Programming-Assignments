#ifndef PLANNER_H
#define PLANNER_H

#include<string.h>
#include "dictionary.h"
#include "dictionary.cpp"




class Planner {
  private:
    Dictionary journey_table;
    

    int search(Entry* e ,float time){
      
      unsigned int left = 0;
      unsigned int right = e->num_journeys - 1;
      
      if(e->journeys[left].start_time >= time){
        return -1;
      }

      if((e->journeys[right]).start_time < time){
        return right;
      }
      
      
      while (right - left > 1){
        unsigned int search_index = (left + right)/2;

        if((e->journeys)[search_index].start_time >= time){
          right = search_index;
        }

        else if ((e->journeys)[search_index].start_time < time)
        {
          left = search_index;
        }
      }
      //std::cout<< left << std::endl;
      return left;
      
    }

  public:

    void add(Journey to_add) {
      

      Entry* e = journey_table.get(to_add.start);
      if(e == NULL){
        Entry new_station;
        strcpy(new_station.key, to_add.start);
        new_station.journeys[0] = to_add;
        new_station.num_journeys = 1;

        journey_table.put(new_station);
        //std::cout << "Station Added\n";
        return;
      }

      if(e->num_journeys >= 64){
        std::cout << "Too many journeys!!\n";
        return;
      }

      int index = search(e, to_add.start_time);
      for(int i = e->num_journeys; i > index+1; i--){
        e->journeys[i] = e->journeys[i-1];
      }

      strcpy(e->journeys[index + 1].start, to_add.start);
      strcpy(e->journeys[index + 1].end, to_add.end);
      e->journeys[index + 1].start_time = to_add.start_time;
      e->journeys[index + 1].end_time = to_add.end_time; 
      e->num_journeys += 1;
      //std::cout << "Journey Added\n";
      return;
    }

    void query_station(char start_station[], float time = 0) {
      Entry* e = journey_table.get(start_station);
      if (e == NULL){
        std::cout << "Station doesn't exist!";
        return ;
      } 
      int index = search(e, time);

      //std::cout<<index;

      if(index+1 == e->num_journeys){
        std::cout<<"No journeys after "<<(e->journeys)[index].start_time<<"\n";
        return ;
      }

      for(int i = index + 1 ; i < e->num_journeys ; i++){
        std::cout << e->journeys[i].start_time << " "
        << e->journeys[i].end << "\n";
      }
    }

    bool direct_query (char start_station[], float time, char end_station[], float &journey){
      Entry* e = journey_table.get(start_station);
      if (e == NULL){
        // std::cout << "Station doesn't exist!";
        return false;
      }

      int index = search(e, time);
      for(int i = index + 1 ; i < e->num_journeys ; i++){
        if(strcmp((e->journeys)[i].end, end_station) == 0){
          journey = (e->journeys)[i].start_time;
          return true;
        }
      }
      return false;
    }
    
    void query_journey (char start_station[], float time, char end_station[]){
      Entry* e = journey_table.get(start_station);
      if (e == NULL){
        std::cout << "Station doesn't exist!";
        return;
      }
      int index = search(e, time);

      for(int i = index + 1 ; i < e->num_journeys ; i++){
        float layover;

        if( strcmp((e->journeys)[i].end, end_station) == 0){
          std::cout << (e->journeys)[i].start_time<<"\n";
          return;
        }
        
        else if (direct_query((e->journeys)[i].end , (e->journeys)[i].end_time , end_station, layover)){
          std::cout << (e->journeys)[i].start_time <<" " <<(e->journeys)[i].end << " " << layover << "\n";
          return;
        }
        
        
      }

      std::cout<< "No journeys available"; 

    }  
};

#endif