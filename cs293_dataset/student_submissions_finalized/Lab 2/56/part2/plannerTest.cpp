#include "planner.cpp"
#include <fstream>

void take_queries(Planner& planner, bool manual, istream& in){
    while(true){
        
        if(manual) cout << ">>> ";
        char query[32];
        in >> query;
        if(strcmp(query, "EXIT") == 0){
            break;
        }
        else if(strcmp(query, "ADD") == 0){
            char start_st[32]; in >> start_st;            
            float st_time; in >> st_time;            
            char end_st[32]; in >> end_st;            
            float end_time; in >> end_time;  
            
            planner.addJourney(start_st, st_time, end_st, end_time);        
                   
            
        }
        else if(strcmp(query, "QUERY_STATION") == 0){
            char stn[32]; in >> stn;
            float time; in >> time;

            planner.query_station(stn, time);            

        }
        else if(strcmp(query, "QUERY_JOURNEY") == 0){
            char start_stn[32]; in >> start_stn;
            float st_time; in >> st_time;
            char end_stn[32]; in >> end_stn;

            planner.query_journey(start_stn, st_time, end_stn);
        }
        else{
            cout << "Please enter a valid query" << endl;            
        }
    }
}



int main(int argc, char* argv[]){    
    cout << "Type in 1 for manual testing; 0 for automatic testing." << endl;
    int resp; cin >> resp;
    if(resp == 1){
        Planner planner(true);
        take_queries(planner, true, cin);
    }
    else{
        Planner planner(false);
        ifstream file;
        file.open(argv[1]);
        take_queries(planner, false, file);
        file.close();
    }    
}