#include "planner.cpp"

int main(){
    cout<<"Welcome to Journey Planner \n";
    cout<<"";
    Planner planner;

    while(1){
    string input;
    cout<<">>>";
    cin>>input;
    
    if(input=="EXIT")break;

    if(input=="ADD"){
        float time1,time2;
        string station1,station2;
        cin>>station1>>time1>>station2>>time2;
        Journey j;
        j.from.name=station1;
        j.from.time=time1;
        j.to.name=station2;
        j.to.time=time2;       
        bool x=planner.addJourney(j);
        if(x==false)cout<<"Error"<<endl;
    }

    if(input=="QUERY_STATION"){
        string station; 
        float time=0;
        cin>>station>>time;
        Station s;
        s.name=station;
        s.time=time;
        planner.printList(s);
    }

    if(input=="QUERY_JOURNEY"){
        string station1,station2;
        float time;
        cin>>station1>>time>>station2;
        Station s;
        s.name=station1;
        s.time=time;
        planner.findJourney(s,station2);
    }

    }
    return 0;

}