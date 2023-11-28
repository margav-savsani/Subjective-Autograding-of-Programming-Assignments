#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<cmath>
using namespace std;

int DICT_SIZE = 64;

struct Entry {
  char station_one[32];
  char station_two[32];
  float start_time;
  float finish_time;
  int state;
  Entry(){
    state=0;
  }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:
    Dictionary(){
        N=64;
        A=new Entry[64];
    }

    int hash_value(char key[]){
        int x=37;
        double a=0;
        double d[strlen(key)];
        for(int i=0; i<strlen(key); i++){
            d[i]=key[i]*((sqrt(5)-1)/2);
        }
        double b=d[strlen(key)-1]*x;
        b=b-int(b);
        for(int i=strlen(key)-1; i>0; i--){
            b=b+d[i-1];
            b=b*x;
            b=b-int(b);
        }
        return(int(b*N));
    }

    void add(char* s1, float st, char* s2,float ft){
        int a=hash_value(s1);
        int sp;
        int b=a;
        while(true){
            if(A[a].state==0) {
                sp=a;
                break;
            }
            a=(a+1)%N;
            if(a==b) return;
        }
        A[sp].finish_time=ft;
        A[sp].start_time=st;   
        A[sp].state=1;
        strcpy(A[sp].station_one,s1);
        strcpy(A[sp].station_two,s2);
    }

    void print_next(char* s1, float st){
        int a=hash_value(s1);
        int b=a;
        bool found=false;
            while(true){
                if(A[a].state==0){
                    break;
                }
                if(strcmp(A[a].station_one,s1)==0){
                    if(A[a].start_time>=st){
                        cout<<A[a].start_time<<" "<<A[a].station_two<<endl;
                        found=true;
                    }
                }
                a=(a+1)%N;
                if(a==b) break;
            }
        if(!(found)){
            cout<<"ERROR"<<endl;
        }
        return;
    }

    void display(char* s1, float st, char* s2){
        float direct=-1;
        float inter=-1;
        float x;
        for(int k=0; k<N ; k++){
            if(A[k].state==1){
                if(strcmp(A[k].station_one,s1)==0){                
                    if(strcmp(A[k].station_two,s2)==0){
                        if(A[k].start_time>=st){
                            direct=A[k].start_time;
                        }
                    }
                    else{
                        for(int j=0; j<N; j++){                   
                            if(strcmp(A[j].station_one,A[k].station_two)==0 && strcmp(A[j].station_two,s2)==0){
                                if(A[k].start_time>=st){
                                    x=A[k].start_time;
                                    if(inter==-1){
                                        inter=x;
                                    }
                                    else{
                                        if(inter>x){
                                            inter=x;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(inter==-1 && direct==-1){
            cout<<"ERROR"<<endl;
            return;
        }
        
        if(inter==-1 && direct!=-1){
            cout<<direct<<endl;
            return;
        }
        if(direct==-1 && inter!=-1){
            cout<<inter<<endl;
            return;
        }
        if(direct!=-1 && inter!=-1){
            if(direct<=inter){
                cout<<direct<<endl;
            }
            else{
                cout<<inter<<endl;
            }
            return;
        }   
    }
};

void input_function(Dictionary d){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cin>>input;
    
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    if(strcmp(input,"ADD") == 0){

      char station_one[32];
      cin >> station_one;
      float start_time;
      cin >> start_time;
      char station_two[32];
      cin >> station_two;
      float finish_time;
      cin >> finish_time;
      
    d.add(station_one,start_time,station_two,finish_time);
    }

    else if(strcmp(input,"QUERY_STATION")==0){
        char s1[32];
        float st;
        cin >> s1;
        cin >> st;
        d.print_next(s1,st);            
    }

    else if(strcmp(input,"QUERY_JOURNEY")==0){
        char s1[32];
        float st;
        char s2[32];
        cin >> s1;
        cin >> st;
        cin >> s2;
        d.display(s1,st,s2);
    }
  }
}

int main()
{
    Dictionary d;
    input_function(d);
}