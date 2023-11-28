#include "planner.h"
#include "dictionary.h"
#include <string.h>

void sortAccTime(Entry l[], int n, int init=0){
    if(init==n) return;
    int min=init;
    for(int i=1+init; i<n; i++){
        if(l[i].value->init_time < l[min].value->init_time)
            min = i;
    }
    Entry var=l[init];
    l[init] = l[min];
    l[min] = var;
    return sortAccTime(l, n, init+1);
}


bool Planner :: queryJourney(char init_station[], float readytime, char dest_station[], int level=1, float prev_init_time=0.0){
    char astr[32];
    strcpy(astr, dest_station);

    if(level>2) return false;
    Entry elelist[DICT_SIZE];
    int *size;
    size = new int;
    if(!plannerDict->get(init_station, readytime, elelist, size)){
        return false;
    }
    sortAccTime(elelist, *size);
    strcpy(dest_station, astr);
    for(int i=0; i<*size; i++){
        if(strcmp(elelist[i].value->dest_station, dest_station)==0){
            if(level==1)
                cout << elelist[i].value->init_time << endl;
            if(level==2)
                cout << prev_init_time << " " << elelist[i].value->init_station << " " << elelist[i].value->init_time << endl;
            return true;
        }
        if(queryJourney(elelist[i].value->dest_station, elelist[i].value->dest_time, dest_station, level+1, elelist[i].value->init_time))
            {return true;}
    }
    return false;
}
void Planner :: planningHandler(){
    while(true){
        char input[32];
        cin>>input;
        if(strcmp(input,"EXIT")==0)
            break;
        
        else if(strcmp(input, "ADD")==0)
            add();
        
        else if(strcmp(input, "QUERY_STATION")==0)
            queryStation();
        
        else if(strcmp(input, "QUERY_JOURNEY")==0){
            char init_station[32]; char dest_station[32];
            float ready_time;
            cin >> init_station >> ready_time >> dest_station;
            if(!queryJourney(init_station, ready_time, dest_station))
                cout << "No journies found!\n";
        }
        else
            cout << "Try Again\n";
    }
}

void Planner :: add(){
    char init_station[32], dest_station[32];
    float init_time, dest_time;
    cin >> init_station >> init_time >> dest_station >> dest_time;
    Entry *element;
    element = new Entry;
    strcpy(element->key, init_station);
    strcpy(element->value->init_station, init_station);
    strcpy(element->value->dest_station, dest_station);
    element->value->init_time = init_time;
    element->value->dest_time = dest_time; 
    if(!plannerDict->put(*element))
        cout << "No space\n";
}


void Planner :: queryStation(){
    char init_station[32];
    float ready_time;
    cin >> init_station >> ready_time;
    Entry elelist[DICT_SIZE];
    int *size;
    size = new int;
    if(!plannerDict->get(init_station, ready_time, elelist, size)){
        cout << "Station doesn't exist!\n";
    }
    for(int i=0; i<*size; i++){
        cout << elelist[i].value->init_time << " " << elelist[i].value->dest_station << endl;
    }
}




int main(){
    Planner a;
    a.planningHandler();

}