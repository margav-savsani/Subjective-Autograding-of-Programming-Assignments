#include<iostream>
#include "planner.h"
#include <string>
#include "plannerDict.cpp"
using namespace std;



Planner::Planner() {
 routesDict = new Dictionary();
} 

bool Planner::addRoute(Query *q) {
    Journey* j = new Journey();
    j->station_one = q->station_one;
    j->station_two = q->station_two;
    j->startTime = q->time;
    j->endTime = q->endtime;

    routesDict->put(j);

    //cout << routesDict->get("jammu") << endl;
    return true;
}

void Planner::query_station(Query* q) {
    string s = q->station_one;
    Journey* ptr =  routesDict->get(s)->next;
    int i = 0;
    while (ptr != 0)
    {
        //cout << "running" << endl;
        if (ptr -> startTime >= q -> time)
        {
            ptr -> printStationOne();
            i++;
        }
        
       ptr = ptr -> next;
    }

    if (i == 0)
    {
        cout << "ERROR" << endl;
    }
    
}

void Planner::query_journey(Query* q) {
    Journey* ptr = routesDict->get(q->station_one)->next;
    //cout << ptr <<endl;
    //ptr ->printJourney();
    while (ptr !=  nullptr)
    {
        //ptr -> printJourney();
        if(q->station_two == ptr->station_two && ptr->startTime >= q ->time){
            ptr -> printSoonestJourney();
            return;
        }

        else {
            Journey* ptr2 = routesDict->get(ptr -> station_two)->next;
            while (ptr2 != nullptr)
            {
                //cout << "checked on";
                //ptr2->printJourney(); 
                if (ptr2->station_two == q->station_two && ptr->startTime >= q->time)
                {
                    ptr->printSoonestJourney();
                    //ptr2->printJourney();
                    return;
                }

                ptr2 = ptr2 -> next;
                
            }
        }
        
        ptr = ptr -> next; 
        
            
    }

    cout << "ERROR" << endl;
    return;
    
}

void automatic(){
    Planner *p = new Planner();
    freopen("test.txt","r", stdin);

    string word;
    vector<Query*> queries;
    
    while (cin >> word)
    {
        //cout << word <<endl;
            if (word == "EXIT")
            {
                break;
            }
            
            Query* tempQ = new Query();

            if (word == "QUERY_JOURNEY")
            {            
            
            for (int i = 0; i < 4; i++)
            {  
                if (i == 0)
                {
                    tempQ ->action = word;
                }
                
                else if (i==1)
                {
                    tempQ ->station_one = word;
                }

                else if (i==3)
                {
                    tempQ -> station_two = word;
                    break;
                }

                else if (i == 2)
                {
                    tempQ -> time = stof(word);
                }
                cin >> word;
            }

        }

        else if (word == "ADD")
        {
            for(int i=0; i<5; i++){
                if (i == 0)
                {
                    tempQ ->action = word;
                }
                
                else if (i==1)
                {
                    tempQ ->station_one = word;
                }

                else if (i==3)
                {
                    tempQ -> station_two = word;
                }

                else if (i == 2)
                {
                    tempQ -> time = stof(word);
                }
                
                else if (i == 4)
                {
                    tempQ -> endtime = stof(word);
                    break;
                }
                
                cin >> word;
            }
        }

        else if (word == "QUERY_STATION")
            {
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                    {
                        tempQ ->action = word;
                    }

                    else if (i == 1)
                    {
                        tempQ -> station_one = word;
                    }

                    else if (i == 2)
                    {
                        tempQ -> time = stof(word);
                        break;
                    }
                    
                    
                    cin >> word;
                }
                
            }   

            queries.push_back(tempQ);
    }

/*
    while (cin >> word)
    {
        cout << 3 <<"-" << word << endl;
    }
    
*/
    //cout << "maharashtra" << endl;
    //cout << queries.size();
    //queries[0] ->printQuery();

    for (auto q : queries)
    {
       // q ->printQuery();
       // cout << endl;
        
        if (q ->action == "ADD")
        {
            p->addRoute(q);
        }

        else if (q ->action == "QUERY_JOURNEY")
        {
            p ->query_journey(q);
        }
        
        else if (q -> action == "QUERY_STATION")
        {
           p->query_station(q);
        }
        
           
    }
    
}

void interactive() {
    string word;
    Planner *p = new Planner();

    while (true)
    {
         cin >> word;
         if (word == "EXIT")
            {
                break;
            }
            
            Query* tempQ = new Query();

            if (word == "QUERY_JOURNEY")
            {            
            
            for (int i = 0; i < 4; i++)
            {  
                if (i == 0)
                {
                    tempQ ->action = word;
                }
                
                else if (i==1)
                {
                    tempQ ->station_one = word;
                }

                else if (i==3)
                {
                    tempQ -> station_two = word;
                    break;
                }

                else if (i == 2)
                {
                    tempQ -> time = stof(word);
                }
                cin >> word;
            }

            p->query_journey(tempQ);

        }

        else if (word == "ADD")
        {
            for(int i=0; i<5; i++){
                if (i == 0)
                {
                    tempQ ->action = word;
                }
                
                else if (i==1)
                {
                    tempQ ->station_one = word;
                }

                else if (i==3)
                {
                    tempQ -> station_two = word;
                }

                else if (i == 2)
                {
                    tempQ -> time = stof(word);
                }
                
                else if (i == 4)
                {
                    tempQ -> endtime = stof(word);
                    break;
                }
                
                cin >> word;
            }

            p->addRoute(tempQ);
        }

        else if (word == "QUERY_STATION")
            {
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                    {
                        tempQ ->action = word;
                    }

                    else if (i == 1)
                    {
                        tempQ -> station_one = word;
                    }

                    else if (i == 2)
                    {
                        tempQ -> time = stof(word);
                        break;
                    }
                    
                    
                    cin >> word;
                }

                p->query_station(tempQ);
                
            }
    }
    
}

int main() {
    interactive();
}
/*

int main() {
    Journey j1 = {"jammu","kashmir", 2100, 1600};
    Journey j2 = {"jammu", "kanpur", 1600, 1800};
    Journey j5 = {"jammu","maharashtra",1200};
    p->query_journey(&q);
    //p -> query_station("bandra");
    //Journey* ptr = p->routesDict->get("jammu");

   
   
    

//    Query q = {"jammu","gujrat",1100};

//    p.query_journey(q);

}
*/