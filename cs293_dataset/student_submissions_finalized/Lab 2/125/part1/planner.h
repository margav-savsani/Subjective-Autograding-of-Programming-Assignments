#ifndef PLANNER_H
#define PLANNER_H
const int INITIAL_SIZE = 50;
struct Journey{
    char start[32];
    char end[32];
    float start_time;
    float end_time;
    Journey(){
    }
};
struct journey_list{
    int N;
    Journey* list;
    int elements;
    journey_list(){
        N = INITIAL_SIZE;
        list = new Journey[N];
        elements=0;
    }
    Journey* begin(){
        return list;
    }
    Journey* end(){
        return list+elements;
    }
    void grow(){
        Journey* new_list = new Journey[2*N];
        for(int i = 0; i<elements; i++){
            new_list[i]=list[i];
        }
        delete[] list;
        list = new_list;
        N*=2;
    }
    void insert(Journey* location, Journey journey){
        if(elements==N) grow();
        for(int i = elements; i>location-begin(); i--){
            list[i]=list[i-1];
        }
        list[location-begin()] = journey;
        elements++;
    }
};
bool start_time_comp(Journey x, Journey y){
    return x.start_time<=y.start_time;
}
#endif