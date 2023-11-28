#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

*/

void dictionaryHandler(Dictionary &dictionary){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // INS <key> <value>
    if(strcmp(input,"ADD") == 0){
      
      char station1[32]; 
      cin >> station1; 
      double start; 
      cin >> start; 
      char station2[32];
      cin >> station2;
      double finish; 
      cin >> finish;

      Journey journey;
      strcpy(journey.station1,station1); 
      strcpy(journey.station2, station2); 
      journey.start  = start;
      journey.end = finish;

      int hashValueData = dictionary.hashValue(journey.station1); 
      int freeIndexData = dictionary.findFreeIndex(journey.station1);
      if(freeIndexData >= 0){
        dictionary.put(journey);
      }
      else{
        cout << "ERROR : No Available Space" << endl;
      }
    }

    // DEL <key>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char station1[32];
      cin >> station1; 
      double start;
      cin >> start;
      Query q;
      strcpy(q.station.station, station1);
      q.start = start;
      Journey* outputs = dictionary.get(q);
      
      int i = 0;
      //cout << "Available trains \n ===========================================  " << endl;
      //cout << "Sr.no Start time :          Destination : " << endl;
      while (outputs[i].start != -1){
         cout <<  outputs[i].start << " " << outputs[i].station2 << endl;
         i++;
      }
      if (i == 0) cout << "ERROR" << endl;
      
    }

    // FIND <key>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char station1[32];
      cin >> station1;
      double start;
      cin >> start;
      char station2[32];
      cin >> station2;
      
      Query q;
      strcpy(q.station.station, station1);
      q.start = start;
      Journey *outputs = dictionary.get(q);
      
      double min_time = 100000;
      int i = 0;
      Journey final; Journey journey2;
      bool two_journeys = false;
      bool single_journey = false;
      while (outputs[i].start != -1){
        // find minimum time, check if destination has a train to final destination. 
        // find direct path first. 
        if (equal(outputs[i].station2, station2)){
            double cur_time = outputs[i].start;
            if (cur_time < min_time){
                min_time = cur_time;
                final = outputs[i];
                two_journeys = false;
                single_journey = true;
            }
        }
        else {
            // intermediate station fixed in every iteration. 
            
            char intermediate[32];
            strcpy(intermediate, outputs[i].station2);
            Query q; 
            q.start = outputs[i].end; strcpy(q.station.station, intermediate); // lists all possible things from intermediate
            Journey *journeys2 = dictionary.get(q);

            // checks if anything is possible from the intermediate station ? yes -> find minimum possible start time, no -> get out.
            
            int j = 0; 
            
            
            while (journeys2[j].start!=-1){
              
                if (equal(journeys2[j].station2, station2)){
                    double cur_time = outputs[i].start;
                    if (cur_time < min_time) {
                        min_time = cur_time;
                        final = outputs[i];
                        journey2 = journeys2[j];
                        two_journeys = true;
                        single_journey = false;
                        
                    }
                    // this start time should be after end time of journey 1 (taken care of)
                    // should be as low as possible -- checking here. 
                }
                j++;
            }
            if (j == 0) two_journeys = false; 
            
        }
        i++;

      }

      if (!(single_journey || two_journeys)) {cout << "ERROR" << endl;} // this case will never be used, just a safegaurd for testing.
      // now among these trains, check which journey or which combination of journeys is best.
      else{
        // now everything is computed -- PRINTING
        std::cout << std::fixed;
        std::cout << std::setprecision(0);
        if (two_journeys) {
          cout << final.start << " " << final.station2 << " " << journey2.start << endl;
        }
        else {
          cout << final.start << endl;
        }
      }
      
    }
  }
}

void automatic()
{
  Dictionary dictionary;
  freopen("sample.txt", "r", stdin);
  // dictionaryHandler(dictionary);
  // TODO
  int frequency[DICT_SIZE] = {0};

  char word[32];
  while(cin >> word){
    int hash = dictionary.hashValue(word);
    frequency[hash]++;
  }

  for(int i = 0; i < DICT_SIZE; i++){
    cout << frequency[i] << endl;
  }

}

void interactive()
{
  Dictionary dictionary;
  dictionaryHandler(dictionary);
}


int main()
{
  cout<<"Enter 1 for interactive testing and 0 for automatic"<<endl;
  int which;
  cin>>which;
  
  if(which == 1){
    interactive();
  }
  else{
    automatic();
  }
  return 0;
}
