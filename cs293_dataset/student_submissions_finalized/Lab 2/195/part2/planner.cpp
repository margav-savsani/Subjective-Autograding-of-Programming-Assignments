#include "planner.h"
#include <fstream>

int main(){
     Planner planner;
     ofstream fout;
     string line;
     /*fout.open("sample-planner.txt");
     while(fout){
           getline(cin,line);
           if(line=="EXIT")
            break;
           fout<< line<<endl;
     }
     fout.close();*/
     string word,filename;
     ifstream fin;
    filename="sample-planner.txt";
     fin.open(filename.c_str());
       int e=0;
      while(fin>>word){
          if(word=="ADD"){
            Journey j;
            int i;
            int a;
             fin>>word;
             j.Station1=word;
             fin>>word;
             j.departure=stof(word);
             i=stof(word)/100;
             a=i;
             fin>>word;
             j.Station2=word;
             fin>>word;
             j.arrival=stof(word);
             if((k[i].departure==-1) ){
               k[i]=j;
               if(e<i){
                e=i;
               }
             }
             else{
                 i=(i+1)%50;
                 while(k[i].departure!=-1 ){
                    i=(i+1)%50;
                  }
                k[i]=j;
                if(e<i){
                    e=i;
                }
             }
          }
          else if(word=="QUERY_STATION"){
             fin>>word;
             string s;
             s=word;
             fin>>word;
             float p=stof(word);
             int a=p/100;
             int i=0;
             while(k[a].departure!=-1 || a<e){
             if(!strcmp(k[a].Station1.c_str(),s.c_str())&&(k[a].departure>=p)){
                   cout<<k[a].departure<<" "<<k[a].Station2<<endl;
                   i=i+1;
             }
             a=(a+1)%50;
             }
            if(i==0){
                  cout<<"ERROR"<<endl;
            }
            }
         else if(word=="QUERY_JOURNEY"){
              string d;
              fin>>word;
              d=word;
              int x,y=0,z=0,i=0;
              fin>>word;
              float t=stof(word);
              x=t/100;
              string c;
              fin>>word;
              c=word;
              float p=0,q=0,o=-1;
              while(k[x].departure!=-1||x<e){
                  if(k[x].departure>=t && !strcmp(k[x].Station1.c_str(),d.c_str())){
                        if(!strcmp(k[x].Station2.c_str(),c.c_str())){
                            if(y==0){
                              p=k[x].departure;
                              y=y+1;
                            }
                            else{
                                 if(p>k[x].departure){
                                    p=k[x].departure;
                                 }
                            }
                           }
                            int f=k[x].arrival/100;
                            while(k[f].departure!=-1 || f<e){
                                  if(!strcmp(k[f].Station1.c_str(),k[x].Station2.c_str())&&k[f].departure>=k[x].arrival){
                                       if(!strcmp(k[f].Station2.c_str(),c.c_str())){
                                         if(z==0){
                                          q=k[f].departure;
                                          o=k[x].departure;
                                          i=x;
                                          z=z+1;
                                         }
                                         else{
                                             if(o>k[x].departure){
                                                o=k[x].departure;
                                                q=k[f].departure;
                                                i=x;
                                             }
                                         }
                                          }
                                    }
                                    f=(f+1)%50; 
                             }
                   }
                 x=(x+1)%50;
              }
                   if(p<o && p>0){
                       cout<<p<<endl;
                   }
                   else if(p>=o && o>=0){
                       cout<<k[i].departure<<" "<<k[i].Station2<<" "<<q<<endl;
                   }
                   else if(p>0){
                      cout<<p<<endl;
                   }
                   else if(o>=0){
                       cout<<k[i].departure<<" "<<k[i].Station2<<" "<<q<<endl;
                   }
                   else{
                      cout<<"ERROR"<<endl;
                   }
                   }
                   }
                   }
                
                        


          
