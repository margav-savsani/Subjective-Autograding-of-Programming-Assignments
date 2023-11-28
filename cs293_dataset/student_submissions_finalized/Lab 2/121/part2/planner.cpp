#include"dictionary.cpp"
using namespace std;
 
class Planner{
  Dictionary source_stations;
  int num_stations = 64;
public : 
    void add_path(char stn_one[], float start_time, char stn_two[], float end_time){
        Entry* e = source_stations.get(stn_one);  //entry of starting station
        if (e==NULL){    //if it isn't in source stations list
            Entry ent ;  //creating a temporary entry
            strcpy(ent.key, stn_one);
            Journey j;   //temporary journey
            j.arr_time = end_time;
            j.dept_time = start_time;
            strcpy(j.dest, stn_two);
            ent.value.add_journey(j);   //add the entry when it's finally made
            source_stations.put(ent);   //putting it in the dictionary
        }
        else{      //just adding a journey to it's departures
            Journey j;   //temporary journey
            j.arr_time = end_time;
            j.dept_time = start_time;
            strcpy(j.dest, stn_two);
            e->value.add_journey(j);   //adding journey
        }
    }
    void qry_stn(char stn_one[], float start_time){  
        Entry* e = source_stations.get(stn_one);   //finding the entry corresponding to stn_one
        if (e == NULL){    //if source station does not exist
            cout<<"ERROR : source station not found"<<endl;
            return;
        }
        else{   //if stn_one is a source station
            e->value.start_query(start_time);
        }
    }
    void qry_jrny(char stn_one[], float time, char stn_two[]){ 
        Entry* e = source_stations.get(stn_one);  //entry of stn 1
        if (e == NULL){   //checking if the source station in the query exists
            cout<<"ERROR : source station not found"<<endl;
            return;
        }
        int index = e->value.bin_search_time(time);  //finding least index with dept time atleast 'time'
        while(true){
            if(index==-1) break;  //error code
            Journey intermediate = e->value.refer(index);  //taking out the corresponding journey
            if(strcmp(intermediate.dest, stn_two)==0){  //if the journey is direct
                cout<<intermediate.dept_time<<endl;
                return;
            }
            else{   //if the journey is via intermediate
                Entry* f = source_stations.get(intermediate.dest);
                if(f!=NULL){
                    if (f->value.direct(stn_two, intermediate.arr_time) != nullptr){
                        Journey* a= f->value.direct(stn_two, intermediate.arr_time);
                        cout<<intermediate.dept_time<<" "<<intermediate.dest<<" "<<a->dept_time<<endl;
                        return;
                    }
                }
            }
            index++;  //if intermediate stn satisfies neither of cases
            if(index >= e->value.len()) break;   //condition of failure
        }
        cout<<"No path between two given stations found"<<endl;
    }
};

int main(){
    Planner p;
    char choice[32];
    while(true){
        cin>>choice;
        if(strcmp(choice, "QUERY_STATION")==0){
            char stn_start[32];
            float start_time;
            cin>>stn_start>>start_time;
            p.qry_stn(stn_start,start_time);
        }
        if(strcmp(choice, "QUERY_JOURNEY")==0){
            char station_one[32], station_two[32];
            float start_time;
            cin>>station_one>>start_time>>station_two;
            p.qry_jrny(station_one, start_time, station_two);
        }
        if(strcmp(choice, "ADD")==0){
            char station_one[32], station_two[32];
            float start_time, end_time;
            cin>>station_one>>start_time>>station_two>>end_time;
            p.add_path(station_one,start_time,station_two,end_time);
        }
        if(strcmp(choice, "EXIT")==0) break;
    }
}
