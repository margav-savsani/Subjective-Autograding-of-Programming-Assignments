#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<string.h>
#include<cmath>

using namespace std;

struct Journey {
  // define suitable fields here
    float startt,finisht;
    char dest[32];

    Journey(){dest[0]='\0';}
};

struct Station {
  // define suitable fields here
    char name[32];int N=16;
    int store[16];int noOfJour=0;
    struct Journey *j=new Journey[16];

    Station(){name[0]='\0';}

    int hashvalue(char stat[]){
    
      int i=0;double k=(sqrt(5)-1)/2,x=1,sum=0;

      while(stat[i]!='\0'){sum=sum+stat[i]*x;
                          x=x*33;i++;}
                          
      double y=(sum*k)-floor(sum*k);
      y=floor(y*N);
      return y;
    }

    void insertionSort() {
      int size=noOfJour;
      
      float key;int n,k;
      for(int m = 1; m<size; m++) {
      key = j[store[m]].startt;//take value
      k = store[m];
      n = m;
      while(n > 0 && j[store[n-1]].startt>key) {
         store[n] = store[n-1];
         n--;
      }
      store[n] = k;   //insert in right place
      }
    }

    void addjourney(char stat[],float startt,float finisht){
      
      int p;
      for(int i=hashvalue(stat);i<N;i=(++i)%N){
        if(j[i].dest[0]=='\0'){
          p=i;break;
        }
      }

      strcpy(j[p].dest,stat);j[p].startt=startt;j[p].finisht=finisht;
      store[noOfJour]=p;
      noOfJour++;

      cout<<"Jouney added successfully"<<endl;

    }

    void list(float startt){
      for(int i=0;i<noOfJour;i++){
        if(j[store[i]].startt>=startt){cout <<j[store[i]].startt <<" "<<j[store[i]].dest<<endl;}
      }
    }
    

};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
    struct Station *s;int N=16;

  public:

    Planner(){s=new Station[N];}

    int hashvalue(char stat[]){
      
      int i=0;double k=(sqrt(5)-1)/2,x=1,sum=0;

      while(stat[i]!='\0'){sum=sum+stat[i]*x;
                          x=x*33;i++;}
                          
      double y=(sum*k)-floor(sum*k);
      y=floor(y*N);
      return y;
    }

    int findindex(char stat[]){

      for(int i=hashvalue(stat);i<N;i=(++i)%N){

        if(s[i].name[0]=='\0')return (-1);
        
        else if(strcmp(stat,s[i].name) == 0)return i;

        else if(strcmp(stat,s[i].name) != 0) continue;
      }
    }

    struct Station *getstat(char stat[]){
      int i=findindex(stat);

      return &s[i];

    }

    void addstat(char stat[]){
      for(int i=hashvalue(stat);i<N;i=(++i)%N){
        if(s[i].name[0]=='\0'){
          strcpy(s[i].name,stat);break;
        }
        else continue;
      }
      cout<<"Station Added successfully"<<endl;
    }
    
};

#endif
