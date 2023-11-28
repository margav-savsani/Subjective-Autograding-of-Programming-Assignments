#include<iostream>
#include<string.h>

using namespace std; 
 
#include "planner.h"

Planner :: Planner(){
    N=100;
    J=new Journey [N];
    }

int Planner :: hashValue(char key[]){
     int hash;
  int n=0,x=5;
  long int sum=0;
  for(int i=0; key[i]!='\0';i++)    
          n=n+1;
             
  for(int i=n; i>=0; i--)        
      sum=sum*x+int(key[i]);
      
  int m=64;
  double B=(sqrt(5)-1)/2;
   double k=int(sum*B);
   hash=m*((sum*B)-k);    
  return hash;
  }

 int Planner :: findFreeIndex(char key[]){
    int k=hashValue(key);
    
    for(int i=k;i<N;i++){
      if(J[i].stat==0) return i;
        }  
    for(int i=0; i<k; i++){
        if(J[i].stat==0) return i;
        }      
    return -1;  
 }

 bool Planner :: add(struct Journey e){
   int k=findFreeIndex(e.s1.stn);
   if (k==-1) return false;
   else 
     {
       J[k]=e;
       J[k].stat=1;
       }
   return true;
 }  
 
 void Planner :: stnlist(char key[],float t){
   int k=hashValue(key);
   int n=0;
    for(int i=k; J[i].stat!=0; i++)
       {
         
         if(strcmp(J[i].s1.stn,key)==0) 
           {
              if (J[i].t1 >= t)
                  {
                      cout<<J[i].t1<<" "<<J[i].s2.stn<<endl; 
                      n++;
                    }  
            }
        }    
     for(int i=0; J[i].stat!=0; i++)
       {
         if(strcmp(J[i].s1.stn,key)==0) 
           {
              if (J[i].t1 >= t)
                  {  
                    cout<<J[i].t1<<" "<<J[i].s2.stn<<endl; 
                      n++;
                    }
            }
        }
          
   if(n==0) cout<<"ERROR"<<endl;
        
    return;
}



void Planner :: soonest(char key1[],float time,char key2[]){
    
    int u=0;
    int v=0;
    int match1[30];  
     
    int match2[30];        
     
    int k=hashValue(key1);

      for(int i=k; J[i].stat!=0; i++)
       {
         if(strcmp(J[i].s1.stn,key1)==0) 
              if (J[i].t1 >= time) 
               {
                 match1[u]=i;
                 u++;
                 }
        }    
     for(int i=0; J[i].stat!=0; i++)
       {
         if(strcmp(J[i].s1.stn,key1)==0) 
           if(J[i].t1 >= time) 
               {
                 match1[u]=i;
                 u++;               
               }
            }

        for(int p=0;p<u;p++)
        { 
          if(strcmp(J[match1[p]].s2.stn,key2)==0)
             {
               match2[v]=match1[p];
                 v++;
              }   
         else
         {
           for(int i=0;i<N;i++)
            {
             if(J[i].stat==0) continue;
              else
                  if(strcmp(J[i].s2.stn,key2)==0)      
                       {
                          
                          if(strcmp(J[match1[p]].s2.stn,J[i].s1.stn)==0)
                          {
                             match2[v]=match1[p]; 
                             v++;
                          }
                       }                    
                }  
        }
       }   

for(int i=1;i<v;i++)
  {
    int k=match2[i];
    for(int j=i-1;j>=0;j--)
       if(J[match2[i]].t1<J[match2[j]].t1)
         {   
           match2[j+1]=match2[j];     
           match2[j]=k;
         }
   } 
       
   for(int j=0;j<v;j++)
     {
       if(strcmp(J[match2[j]].s2.stn,key2)==0)
         {
           cout<<J[match2[j]].t1<<endl;  
            return;
            }
       else
         {
           for(int i=0;i<N;i++)
            {
             if(J[i].stat==0) continue;
              else
                  if(strcmp(J[i].s2.stn,key2)==0)      
                       {
                          if(strcmp(J[match2[j]].s2.stn,J[i].s1.stn)==0)
                          {
                            cout<<J[match2[j]].t1<<" "<<J[match2[j]].s2.stn<<" "<<J[i].t1<<endl;
                            return;
                          }
                       }                    
                } 
              }                     
 }
 cout<<"ERROR"<<endl;
 return;
 }
