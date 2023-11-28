#include<iostream>
#include<cmath>
using namespace std;

double golden_ratio = ((sqrt(5)-1)/2.0);
bool Planner::check(char* k1,char* k2)//for checking 2 char arrays
{
    for(int i=0;i<32;i++)
    {
        if(k1[i]=='\0'&& k2[i]!='\0')
        {
           return false;
        }
        if(k1[i]!='\0'&& k2[i]=='\0')
        {
            return false;
        }
        if(k1[i]==k2[i] && k1[i]=='\0')
        {
            return true;
        }
        if(!(k1[i]!='\0' && k2[i]!='\0' && k1[i]==k2[i]))
        {
            return false;
        }
    }
    return true;
}
int Planner::hashValue(char* x)
{
    long double polynomial_value=0;
    long double factor=1;
    for(int i=0;i<32;i++)
    {
        if(x[i]=='\0')
        {
            break;
        }
        polynomial_value += factor*((x[i]+1)-1);
        factor = factor * 5;//chosen some value
    }//hash code is completed
    return floor(64*(polynomial_value*golden_ratio-floor(polynomial_value*golden_ratio)));
}
bool Planner::add_station(Station x)//adding station to check easily in finding queries 
{
    if(Total_Stations==64)
    {
        return false;
    }//max number of stations are fixed due to memory wastage
    for(int i=0;i<Total_Stations;i++)
    {
        if(check(x.Station_Name,All_Stations[i].Station_Name))
        {
            return true;
        }
    }
    All_Stations[Total_Stations]=x;
    Total_Stations++;
    return true;
}
bool Planner::add(Train x)
{//adding train to the array
    int HashVal = hashValue(x.Station_1.Station_Name);
    Station* y = new Station;
    for(int i=0;i<32;i++)
    {
        y->Station_Name[i]=x.Station_1.Station_Name[i];
    }//creating station and copying all the values
    if(!add_station(*y)){return false;}
    for(int i=0;i<32;i++)
    {
        y->Station_Name[i]=x.Station_2.Station_Name[i];
    }
    if(!add_station(*y)){return false;}
    for(int i=HashVal;i<64+HashVal;i++)
    {
        if(Filled_or_not[i%DICT_SIZE])
        {
            continue;
        }
        else
        {//finally adding train to the main array
            All_Trains[i%DICT_SIZE]=x;
            Filled_or_not[i%DICT_SIZE]=true;
            Total_Trains++;
            return true;
        }
    }
    return false;
}

void Planner::Query_Station(Station x,float Start)
{
    bool found=false;
    int HashVal = hashValue(x.Station_Name);
    for(int i=HashVal;i<64+HashVal;i++)
    {
        if(!Filled_or_not[i%DICT_SIZE])
        {
            break;
        }
        if(Filled_or_not[i%64] &&  !check(x.Station_Name,All_Trains[i%DICT_SIZE].Station_1.Station_Name))
        {
            continue;
        }//checking whether that station exists or not
        if(Start <= All_Trains[i%DICT_SIZE].Start_time)
        {//prints all the trains
            cout << All_Trains[i%DICT_SIZE].Start_time <<" "<< All_Trains[i%DICT_SIZE].Station_2.Station_Name<<endl;
            found = true;
        }
    }
    if(!found)
    {//prints error if it soesn't find
        cout << "ERROR\n";
    }
    return;
}
Train* Planner::Query_Direct_Journey(My_Journey x)
{//first finding the direct journey exists or not
    int a=-1;
    int HashVal = hashValue(x.Station_1.Station_Name);
    for(int i=HashVal;i<64+HashVal;i++)
    {
        if(!Filled_or_not[i%DICT_SIZE])
        {
            break;
        }
        if(x.Start_time <= All_Trains[i%DICT_SIZE].Start_time&& check(x.Station_1.Station_Name,All_Trains[i%DICT_SIZE].Station_1.Station_Name)&&check(x.Station_2.Station_Name,All_Trains[i%DICT_SIZE].Station_2.Station_Name))
        {
            if(a==-1 || All_Trains[a].Start_time > All_Trains[i%64].Start_time)
            {
                a=(i%64);
            }
        }
    }
    if(a==-1)
    {
        return NULL;
    }
    Train* T =new Train;//just copying this for safety
    for(int i=0;i<32;i++)
    {
        T->Station_1.Station_Name[i]=All_Trains[a].Station_1.Station_Name[i];
        T->Station_2.Station_Name[i]=All_Trains[a].Station_2.Station_Name[i];
    }
    T->Start_time=All_Trains[a].Start_time;
    T->Finish_time=All_Trains[a].Finish_time;
    return T;
}
Train* Planner::Query_Journey(My_Journey x)
{
    Train* a = Query_Direct_Journey(x);//comparing with the direct journey
    Train* b= NULL;
    Train* c= NULL;
    My_Journey dummy;
    My_Journey dummy2;
    dummy.Start_time=x.Start_time;
    for(int i=0;i<32;i++)
    {
        dummy.Station_1.Station_Name[i]=x.Station_1.Station_Name[i];
        dummy2.Station_2.Station_Name[i]=x.Station_2.Station_Name[i];
    }
    for(int i=0;i<Total_Stations;i++)
    {
        for(int j=0;j<32;j++)
        {
            dummy.Station_2.Station_Name[j]=All_Stations[i].Station_Name[j];
            dummy2.Station_1.Station_Name[j]=All_Stations[i].Station_Name[j];
        }
        b = Query_Direct_Journey(dummy);
        if(b==NULL)
        {
            continue;
        }
        dummy2.Start_time = b->Finish_time;
        c = Query_Direct_Journey(dummy2);
        if(c==NULL)
        {
            b=NULL;
            continue;
        }
        if(a==NULL)
        {
            a=b;
            continue;
        }
        if(b->Start_time < a->Start_time)
        {
            a=b;
        }
    }
    if(a==NULL)
    {
        return NULL;
    }
    Train* T =new Train;//just copying this for safety
    for(int i=0;i<31;i++)
    {
        T->Station_1.Station_Name[i]=a->Station_1.Station_Name[i];
        T->Station_2.Station_Name[i]=a->Station_2.Station_Name[i];
    }
    T->Start_time=a->Start_time;
    T->Finish_time=a->Finish_time;
    return T;
}