#include <bits/stdc++.h>
#include<string.h>
using namespace std;
#include "planner.h"

int Planner::hashValue(char key[]){
    int p=37;
    int i=0;
    for(i ; i< 32 ; i++){                 //to find the hash value and compressing map
        if(key[i] == '\0' ) break;
    }
    int ans=key[0];
    for(int k=1 ; k <i ; k++){
        ans = (ans*p + int(key[i])-int('a')+20)%613; 
    }
    
  
    double a=0.618;
    a*=ans;
    int b=64;
    b= b*(a-(int)a);
    return b;
                                }
int Planner::findFreeIndex(char key[]){
    int freespa;
    freespa=hashValue(key);        //to find free index given the hash value
    int check=0;
    while(journey[freespa].arri!=0){
        freespa=(freespa+1)%N;
        check++;
        if(check==N){return -1;}
    }
    return freespa;
                                    }

int indexofSmallestElement(float array[], int size)
{    int index = 0;
	for (int i = 1; i < size; i++)
        {if (array[i] < array[index])       
     index = i;
	}
	return index;
}


bool Planner::Query_Station(char key[],float time){

    int casenow;
    casenow=hashValue(key);
    int check=0;int present=0;

    while(journey[casenow].arri!=0){
    if(strcmp(key,journey[casenow].from)==0){   //gives time at which train start and the arrival station

    if(journey[casenow].arri>=time){
        cout<<"Starts at "<<journey[casenow].arri<<" destination "<<journey[casenow].to<<endl;present++;}
}
    casenow=(casenow+1)%N;
    check++;
    if(check==N){break;} }

    if(present==0){cout<<"such station doesnot exist ";return false;}
    else return true;
                                }

bool Planner::Query_Journey(char key1[],float time,char key2[]){
    int casenow;
    Journey j[N];
    float time1[N];
    casenow=hashValue(key1);                   //gives the details of soonest time at which journey starts
    int check=0;int present=0;

    while(journey[casenow].arri!=0){
        if(strcmp(key1,journey[casenow].from)==0){
            if(journey[casenow].arri>=time){
                if(strcmp(key2,journey[casenow].to)==0){time1[present]=(journey[casenow].dept-journey[casenow].arri);
                                                    cout<<time1[present]<<endl;j[present]=journey[casenow];present++;}


            else {int casenow1;
                casenow1=hashValue(journey[casenow].to);
                while(journey[casenow1].arri!=0){
                    if(strcmp(journey[casenow].to,journey[casenow1].from)==0){
                        if(journey[casenow1].arri>=journey[casenow].dept){
                            if(strcmp(key2,journey[casenow1].to)==0){time1[present]=(journey[casenow1].dept-journey[casenow].arri);
                                                                    cout<<time1[present]<<endl;j[present]=journey[casenow1];present++;}}}

                casenow1=(casenow1+1)%N;}
                    } }      }
    casenow=(casenow+1)%N;
    check++;
    if(check==N){break;}
        }
    int  x=indexofSmallestElement(time1,present);
    if(strcmp(j[x].from,key1)==0){cout<<"From "<<key1<<" at "<<j[x].arri<<" to "<<key2<<" "<<time1[x]<<" hrs"<<endl;;}
    else{cout<<"From "<<key1<<" to "<<j[x].from<<" to "<<key2<<" "<<time1[x]<<" hrs"<<endl;}


    if(present==0){cout << "no such path present";return false;}
    else return true;
    }


 bool Planner::insert(Journey j){
    if(findFreeIndex(j.from)!=-1){
        int x;
        x=findFreeIndex(j.from);   //storing information about journey
        journey[x]=j;
        return true;}
        else return false;
    }